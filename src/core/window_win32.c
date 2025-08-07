#include "core.h"
#include "../debug/debug.h"
#include "../gl/gl.h"

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <wingdi.h>

#define _CRT_SECURE_NO_WARNINGS

typedef struct _window_store
{
    WNDCLASS w32_class;
    HWND w32_window;
    HDC w32_dc;
    HGLRC w32_gl_ctx;

    double time_began;
    double last_frame_time;
    double cur_frame_time;
    double delta_time;
}
window_store;

typedef HGLRC (WINAPI *PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
typedef BOOL (WINAPI *PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC, const int*, const FLOAT*, UINT, int*, UINT*);
typedef unsigned char* (WINAPI *PFNGLGETSTRINGPROC)(unsigned int);

// private source
// ---------------------------------------------------------------- 

static LPCSTR CLASS_NAME = "lx_window";

static LRESULT CALLBACK window_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    switch (umsg)
    {
    case WM_SIZE:
        int width = LOWORD(lparam);
        int height = HIWORD(lparam);
       
        lt_props.width = width;
        lt_props.height = height;

        if (lt_props.on_resize != NULL && gl_is_loaded())
            lt_props.on_resize(width, height);

        break;

    case WM_DESTROY:
        lt_store->alive = 0;
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, umsg, wparam, lparam);
}

static int create_w32_class()
{
    lt_store->window->w32_class = (WNDCLASS)
    {
        .lpfnWndProc = window_proc,
        .hInstance = NULL,
        .lpszClassName = CLASS_NAME
    };

    if (RegisterClass(&lt_store->window->w32_class) == 0)
    {
        emit_error("failed to register win32 class");
        return 0;
    }

    return 1; 
}

static void destroy_w32_class()
{
    UnregisterClass(CLASS_NAME, NULL);
}

static int create_w32_window()
{
    lt_store->window->w32_window = CreateWindowEx(0, CLASS_NAME, lt_props.title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, lt_props.width, lt_props.height, NULL, NULL, NULL, NULL);

    if (lt_store->window->w32_window == NULL)
    {
        emit_error("failed to create win32 window");
        return 0;
    }

    ShowWindow(lt_store->window->w32_window, SW_SHOWNORMAL);

    return 1;
}

static void destroy_w32_window()
{
    if (lt_store->window->w32_window != NULL)
        DestroyWindow(lt_store->window->w32_window);
}

static int create_gl_context()
{
    lt_store->window->w32_dc = GetDC(lt_store->window->w32_window);
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    int pixel_fmt = ChoosePixelFormat(lt_store->window->w32_dc, &pfd);
    SetPixelFormat(lt_store->window->w32_dc, pixel_fmt, &pfd);

    HGLRC temp_ctx = wglCreateContext(lt_store->window->w32_dc);
    if (temp_ctx == NULL)
    {
        emit_error("failed to create temporary opengl context for version querying");
        return 0;
    }

    wglMakeCurrent(lt_store->window->w32_dc, temp_ctx);
    
    PFNGLGETSTRINGPROC glGetString = (PFNGLGETSTRINGPROC) wglGetProcAddress("glGetString");
    const unsigned char* max_version = glGetString(0x1F02);
    int major = 0;
    int minor = 0;

    if (max_version)
        sscanf((const char*)max_version, "%d.%d", &major, &minor);

    if (major == 0)
    {
        emit_error("failed to determine highest supported opengl version");
        return 0;
    }

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
    if (wglCreateContextAttribsARB == NULL)
    {
        emit_error("failed to load wgl arb context creation function");
        return 0;
    }

    int context_attribs[] =
    {
        0x2091, major,
        0x2092, minor,
        0x9126, 0x00000001,
        0
    };

    lt_store->window->w32_gl_ctx = wglCreateContextAttribsARB(lt_store->window->w32_dc, 0, context_attribs);
    if (lt_store->window->w32_gl_ctx == NULL)
    {
        emit_error("failed to create opengl context");
        return 0;
    }

    wglMakeCurrent(lt_store->window->w32_dc, lt_store->window->w32_gl_ctx);
    wglDeleteContext(temp_ctx);

    return 1;
}

static void destroy_gl_context()
{
    wglMakeCurrent(NULL, NULL);

    if (lt_store->window->w32_gl_ctx != NULL)
        wglDeleteContext(lt_store->window->w32_gl_ctx);

    if (lt_store->window->w32_dc != NULL)
        ReleaseDC(lt_store->window->w32_window, lt_store->window->w32_dc);
}

static double get_time()
{
    static LARGE_INTEGER freq;
    static int initialised = 0;
    LARGE_INTEGER counter;

    if (!initialised)
    {
        QueryPerformanceFrequency(&freq);
        initialised = 1;
    }

    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / (double)freq.QuadPart;
}

// private header
// ----------------------------------------------------------------

int window_create()
{
    lt_store->window = malloc(sizeof(window_store));
    if (lt_store->window == NULL)
    {
        emit_error("failed to allocate internal window store");
        return 0;
    }

    if (!create_w32_class() || !create_w32_window() || !create_gl_context())
        return 0;

    double now = get_time();
    lt_store->window->time_began = now;
    lt_store->window->last_frame_time = now;
    lt_store->window->cur_frame_time = now;
    lt_store->window->delta_time = 0.0; 

    return 1;
}

void window_destroy()
{
    destroy_gl_context();
    destroy_w32_window();
    destroy_w32_class();

    free(lt_store->window);
    lt_store->window = NULL;
}

void window_poll_events()
{
    lt_store->window->last_frame_time = lt_store->window->cur_frame_time;
    lt_store->window->cur_frame_time = get_time();
    lt_store->window->delta_time = lt_store->window->cur_frame_time - lt_store->window->last_frame_time;

    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void window_swap_buffers()
{
    SwapBuffers(lt_store->window->w32_dc);
}

double window_get_time()
{
    return get_time() - lt_store->window->time_began;
}

double window_get_fps()
{
    if (lt_store->window->delta_time == 0.0)
        return 0;

    return 1.0 / lt_store->window->delta_time;
}

double window_get_delta()
{
    return lt_store->window->delta_time;
}
