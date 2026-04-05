#ifndef SV_H
#define SV_H

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define SV_FMT "%.*s"
#define SV_ARG(sv) (int) (sv).count, (sv).data

#define SV_PANIC(msg) do { fprintf(stderr, "PANIC: %s\n", (msg)); abort(); } while(0)

struct string_view {
    const char* data;
    size_t count;
};

typedef struct string_view sv;

// DECLARATION

sv sv_from_cstr(const char* cstr);

#ifdef SV_IMPLEMENTATION

// IMPLEMENTATION

sv sv_from_cstr(const char* cstr)
{
    if(cstr == NULL) SV_PANIC("sv_from_cstr: cstr argument cannot be NULL");
    return (sv) { .data = cstr, .count = strlen(cstr) };
}

#endif // SV_IMPLEMENTATION

#endif // SV_H
