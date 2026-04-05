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

/*
 * Create a sv from cstr and returns it
 */
sv sv_from_cstr(const char* cstr);

/*
 * Return the char at position pos, if pos out of bounds or sv.count == 0 returns -1
 */
char sv_at(const sv sv, const size_t pos);

#ifdef SV_IMPLEMENTATION

// IMPLEMENTATION

sv sv_from_cstr(const char* cstr)
{
    if(cstr == NULL) SV_PANIC("sv_from_cstr: cstr argument cannot be NULL");
    return (sv) { .data = cstr, .count = strlen(cstr) };
}

char sv_at(const sv sv, const size_t pos)
{
    if(sv.count == 0 || pos >= sv.count) return -1;
    return sv.data[pos];
}

#endif // SV_IMPLEMENTATION

#endif // SV_H
