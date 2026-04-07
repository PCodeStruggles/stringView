#ifndef SV_H
#define SV_H

#include <assert.h>
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
 * Returns the char at position pos, if pos out of bounds or sv.count == 0 returns 0 'NULL' char
 */
char sv_at(const sv sv, const size_t pos);

/*
 * Returns the first char of the string, returns 0 'NULL' char if string is empty
 */
#define sv_front(sv) (sv).data[assert((sv).count > 0), 0]

/*
 * Returns the last char of the string, returns 0 'NULL' if string is empty
 */
char sv_back(const sv sv);

/*
 * Returns the lenght of the string
 */
size_t sv_len(const sv sv);

/*
 * Returns whether the string is empty or not
 */
bool sv_empty(const sv sv);

/*
 * Returns a sv without the prefix if such prefix is found, otherwise return original sv
 */
sv sv_remove_prefix(const sv sv, const char* prefix);

/*
 * Returns a sv without the suffix if such suffix is found, otherwise return original sv
 */
sv sv_remove_suffix(const sv sv, const char* suffix);

#ifdef SV_IMPLEMENTATION

sv sv_from_cstr(const char* cstr)
{
    if(cstr == NULL) SV_PANIC("sv_from_cstr: cstr argument cannot be NULL");
    return (sv) { .data = cstr, .count = strlen(cstr) };
}

char sv_at(const sv sv, const size_t pos)
{
    if(sv.count == 0 || pos >= sv.count) return 0;
    return sv.data[pos];
}

char sv_back(const sv sv)
{
    if(sv.count == 0) return 0;
    return sv.data[sv.count - 1];
}

size_t sv_len(const sv sv) { return sv.count; }

bool sv_empty(const sv sv) { return sv.count == 0; }

sv sv_remove_prefix(const sv sv, const char* prefix)
{
    if(prefix == NULL) SV_PANIC("sv_remove_prefix: prefix argument cannot be NULL");
    size_t prefix_len = strlen(prefix);
    size_t i = 0;
    while(i < prefix_len && sv.data[i] == prefix[i]) i++;
    if(i == prefix_len) {
        return (struct string_view) { .data = sv.data + i, .count = sv.count - i };
    } else {
        return sv;
    }
}

sv sv_remove_suffix(const sv sv, const char* suffix)
{
    if(suffix == NULL) SV_PANIC("sv_remove_suffix: suffix argument cannot be NULL");
    int suffix_len = strlen(suffix);
    int i = suffix_len - 1;
    int j = 0;
    while(i >= 0 && sv.data[(sv.count - 1) - j] == suffix[i]) {
        i--;
        j++;
    }
    if(i < 0) {
        return (struct string_view) { 
            .data = sv.data, 
            .count = sv.count - suffix_len };
    } else {
        return sv;
    }
}

#endif // SV_IMPLEMENTATION

#endif // SV_H
