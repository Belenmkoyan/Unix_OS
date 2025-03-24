#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cxxabi.h>
#include <iostream>

char* demangle(const char* mangled_name) {
    int status;
    return abi::__cxa_demangle(mangled_name, NULL, NULL, &status);
}

void myfunc3(int size)
{
    int nptrs;
    void *buffer[size];  
    char **strings;
    // char* ch = "artash slvksvkvs;vs; ksfksfkssl;"
    // char** str = { "ARTASH AGFJKAJA AGKJ AL",}

   nptrs = backtrace(buffer, size);
    printf("backtrace() returned %d addresses\n", nptrs);

   strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nptrs; i++) {
        char* line = strings[i];
        char* underscore = strchr(line, '_');
        char* plus = strchr(line, '+');
        // _funcii+0x1402
        if (underscore && plus && plus > underscore) {
            size_t len = plus - underscore - 1;
            char func_name[len + 1];
            strncpy(func_name, underscore, len);
            func_name[len] = '\0';

            char* demangled = demangle(func_name);

            if (demangled) {
                printf("%s\n", demangled);
            }
            else {
                std::cout << "Cant demangle the function: " << func_name << std::endl;
            }

            free(demangled);
        }
    }

    free(strings);
}

void myfunc(int ncalls,int size)
{
    if (ncalls > 1)
        myfunc(ncalls - 1,size);
    else
        myfunc3(size);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {  
        fprintf(stderr, "%s num-calls buffer-size\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int calls = atoi(argv[1]);
    int size = atoi(argv[2]);

    myfunc(calls, size);
    exit(EXIT_SUCCESS);
}