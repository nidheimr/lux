#include "lux/render.h"
#include "lux/tools.h"
#include "lux/bindings.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>

//
//  private
//

typedef HGLRC (WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

struct _lx_window
{
    int has_received_quit_signal;

    HWND win32_handle;
    HDC device_context;
    HGLRC wgl_context;
};

LRESULT CALLBACK std_window_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

    case WM_SIZE:
        if (glViewport != NULL)
            glViewport(0, 0, LOWORD(lparam), HIWORD(lparam));
        return 0;
	}

	return DefWindowProcA(hwnd, umsg, wparam, lparam);
}

HWND create_win32_window(const char* title, int width, int height)
{
    const char* win32_class_name = "lx_window";

    WNDCLASSEXA win32_class =
    {
        .cbSize = sizeof(WNDCLASSEX),
        .style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = std_window_proc,
        .hInstance = GetModuleHandle(NULL),
        .lpszClassName = win32_class_name
    };

    RegisterClassExA(&win32_class);

    HWND handle = CreateWindowExA(0, win32_class_name, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);
    if (handle == NULL)
        return NULL;

    ShowWindow(handle, SW_NORMAL);
    return handle;
}

HDC get_device_context(HWND handle)
{
    return GetDC(handle);
}

HGLRC create_wgl_context(HDC device_context)
{
    PIXELFORMATDESCRIPTOR format_descriptor =
    {
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = 32,
        .cDepthBits = 24,
        .cStencilBits = 8,
        .iLayerType = PFD_MAIN_PLANE
    };

    int pixel_format = ChoosePixelFormat(device_context, &format_descriptor);
    SetPixelFormat(device_context, pixel_format, &format_descriptor);

    HGLRC pre_ctx = wglCreateContext(device_context);
    if (pre_ctx == NULL)
        return NULL;

    wglMakeCurrent(device_context, pre_ctx);

    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    if (wglCreateContextAttribsARB == NULL)
        return NULL;

    int attribs[] =
    {
        0x2091, 3,          // WGL_CONTEXT_MAJOR_VERSION_ARB = 3
        0x2092, 3,          // WGL_CONTEXT_MINOR_VERSION_ARB = 3
        0x9126, 0x00000001, // WGL_CONTEXT_PROFILE_MASK_ARB = core
        0                   // end of attribs list
    };

    HGLRC final_ctx = wglCreateContextAttribsARB(device_context, 0, attribs);
    if (final_ctx == NULL)
        return NULL;

    wglMakeCurrent(device_context, final_ctx);
    wglDeleteContext(pre_ctx);

    return final_ctx;
}

//
//  public
//

lx_window* lx_window_new(const char* title, int width, int height)
{
    lx_window* window = malloc(sizeof(lx_window));
    if (window == NULL)
    {
        lx_error("failed to allocate lux window");
        return NULL;
    }
    lx_debug("allocated lux window");

    window->has_received_quit_signal = 0;
    window->win32_handle = NULL;
    window->device_context = NULL;
    window->wgl_context = NULL;

    window->win32_handle = create_win32_window(title, width, height);
    if (window->win32_handle == NULL)
    {
        lx_error("failed to create win32 window (win error code: %lu)", GetLastError());
        lx_window_delete(window);
        return NULL;
    }
    lx_debug("created win32 window");

    window->device_context = get_device_context(window->win32_handle);
    if (window->device_context == NULL)
    {
        lx_error("failed to get the window device context (win error code: %lu)", GetLastError());
        lx_window_delete(window);
        return NULL;
    }
    lx_debug("obtained window device context");

    window->wgl_context = create_wgl_context(window->device_context);
    if (window->wgl_context == NULL)
    {
        lx_error("failed to create wgl context (win error code: %lu)", GetLastError());
        lx_window_delete(window);
        return NULL;
    }
    lx_debug("created wgl context");

    __lx_load_gl_procs();
    lx_debug("loaded gl procedures");

    const char* gl_version = glGetString(GL_VERSION);
    lx_debug("context version: %s", gl_version);

    return window;
}

void lx_window_delete(lx_window* window)
{
    if (window == NULL)
        return;

    if (window->wgl_context != NULL)
    {
        wglMakeCurrent(window->device_context, NULL);
        wglDeleteContext(window->wgl_context);
        lx_debug("destroyed wgl context");
    }

    if (window->win32_handle != NULL)
    {
        DestroyWindow(window->win32_handle);
        lx_debug("destroyed win32 window");
    }

    free(window);
    lx_debug("deallocated lux window");
}

void lx_window_update(lx_window* window)
{
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);

        if (msg.message == WM_QUIT)
            window->has_received_quit_signal = 1;

        DispatchMessageA(&msg);
    }

    if (glClear != NULL)
        glClear(GL_COLOR_BUFFER_BIT);
}

void lx_window_render(lx_window* window)
{
    SwapBuffers(window->device_context);
}

int lx_window_has_received_quit_signal(lx_window* window)
{
    return window->has_received_quit_signal;
}