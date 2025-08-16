#include "lux/utils.h"
#include "lux/debug.h"
#include "../debug/debug.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// public header
// ---------------------------------------------------------------- 

char* lx_read_file(const char* file)
{
    GUARD(file == NULL, ("could not open NULL file for reading"), NULL);

    FILE* fp = fopen(file, "rb");
    if (!fp)
    {
        lx_error("failed to open file %s", file); 
        return NULL;
    }

    if (fseek(fp, 0, SEEK_END) != 0)
    {
        lx_error("failed to navigate file %s", file);
        fclose(fp);
        return NULL;
    }
    
    long size = ftell(fp);
    if (size < 0)
    {
        lx_error("failed to determine size of file %s", file);
        fclose(fp);
        return NULL;
    }

    rewind(fp);

    char* buf = malloc(size + 1);
    if (!buf)
    {
        lx_error("failed to allocate space for file %s", file);
        fclose(fp);
        return NULL;
    }

    size_t bytes_read = fread(buf, 1, size, fp);
    if (bytes_read != (size_t)size)
    {
        lx_error("failed to read file %s", file);
        free(buf);
        fclose(fp);
        return NULL;
    }

    buf[size] = '\0';

    fclose(fp);
    return buf;
}
