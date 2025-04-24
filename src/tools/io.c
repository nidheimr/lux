#include "lux/tools.h"

#include <stdio.h>
#include <stdlib.h>

//
//  public
//

char* lx_read_file_as_str(const char* file_path)
{
    FILE* file = fopen(file_path, "rb");

    if (file == NULL)
    {
        lx_error("failed to open file: %s", file_path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* buffer = malloc(sizeof(char) * (length + 1));
    if (buffer == NULL)
    {
        lx_error("failed to allocate space to read file: %s", file_path);
        fclose(NULL);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);

    lx_debug("obtained file as string: %s", file_path);
    return buffer;
}