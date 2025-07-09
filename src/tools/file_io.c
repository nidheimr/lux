#include "lux/tools.h"

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>

//
//  public
//

const char* lx_read_file(const char* file)
{
    PARAM_GUARD(file == NULL, ("cannot read null file"), NULL);

    FILE* f = fopen(file, "rb");

    if (f == NULL)
    {
        lx_produce_error("failed to open file: %s", file);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    rewind(f);

    char* buffer = malloc(sizeof(char) * (length + 1));
    if (buffer == NULL)
    {
        lx_produce_error("failed to allocate space to read file: %s", file);
        fclose(NULL);
        return NULL;
    }

    fread(buffer, 1, length, f);
    buffer[length] = '\0';

    fclose(f);

    lx_produce_debug("obtained file as string: %s", file);
    return buffer;
}
