#ifndef SV_H
#define SV_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SV_FMT "%.*s"
#define SV_ARG(sv) (int)(sv).count, (sv).data

#define SV_PANIC(msg)                                                          \
  do {                                                                         \
    fprintf(stderr, "PANIC: %s\n", (msg));                                     \
    abort();                                                                   \
  } while (0)

struct string_view {
    const char *data;
    size_t count;
};

typedef struct string_view sv;

// DECLARATION

// Create a sv from cstr and returns it
sv sv_from_cstr(const char *cstr);

// Returns the char at position pos with boundary check
#define sv_at(sv, pos) (sv).data[assert((pos) >= 0 && (pos) < (sv).count), (pos)]

// Returns the first char of the string with boundary check
#define sv_front(sv) (sv).data[assert((sv).count > 0), 0]

// Returns the last char of the string with boundary check
#define sv_back(sv) (sv).data[assert((sv).count > 0), (sv).count - 1]

// Returns the lenght of the string
#define sv_len(sv) (sv).count

// Returns whether the string is empty or not
#define sv_empty(sv) ((sv).count == 0)

// Returns a sv without the prefix if such prefix is found, otherwise return
// original sv
sv sv_remove_prefix(const sv sv, const char *prefix);

// Returns a sv without the suffix if such suffix is found, otherwise return
// original sv
sv sv_remove_suffix(const sv sv, const char *suffix);

// Returns true if sv starts with prefix, false otherwise
bool sv_starts_with(const sv sv, const char *prefix);

// Returns true if sv ends with suffix, false otherwise
bool sv_ends_with(const sv sv, const char *suffix);

// Returns a new sv with leading spaces trimmed
sv sv_trim_left(const sv sv);

// Returns a new sv with trailing spaces trimmed
sv sv_trim_right(const sv sv);

// Return a new sv with both leading and trailing spaces trimmed
sv sv_trim(const sv sv);

#ifdef SV_IMPLEMENTATION

sv sv_from_cstr(const char *cstr)
{
    if (cstr == NULL) SV_PANIC("sv_from_cstr: cstr argument cannot be NULL");
    return (sv) {
        .data = cstr,
        .count = strlen(cstr)
    };
}

sv sv_remove_prefix(const sv sv, const char *prefix)
{
    if (prefix == NULL) SV_PANIC("sv_remove_prefix: prefix argument cannot be NULL");
    if (sv_starts_with(sv, prefix)) {
        size_t prefix_len = strlen(prefix);
        return (struct string_view) {
            .data = sv.data + prefix_len,
            .count = sv.count - prefix_len
        };
    } else {
        return sv;
    }
}

sv sv_remove_suffix(const sv sv, const char *suffix)
{
    if (suffix == NULL) SV_PANIC("sv_remove_suffix: suffix argument cannot be NULL");
    if (sv_ends_with(sv, suffix)) {
        size_t suffix_len = strlen(suffix);
        return (struct string_view) {
            .data = sv.data,
            .count = sv.count - suffix_len
        };
    } else {
        return sv;
    }
}

bool sv_starts_with(const sv sv, const char *prefix)
{
    if (prefix == NULL) SV_PANIC("sv_starts_with: prefix argument cannot be NULL");
    size_t prefix_len = strlen(prefix);
    size_t i = 0;
    while (i < prefix_len && sv.data[i] == prefix[i]) i++;
    if (i == prefix_len) {
        return true;
    } else {
        return false;
    }
}

bool sv_ends_with(const sv sv, const char *suffix)
{
    if (suffix == NULL) SV_PANIC("sv_remove_suffix: suffix argument cannot be NULL");
    int suffix_len = strlen(suffix);
    int i = suffix_len - 1;
    int j = 0;
    while (i >= 0 && sv.data[(sv.count - 1) - j] == suffix[i]) {
        i--;
        j++;
    }
    if (i < 0) {
        return true;
    } else {
        return false;
    }
}

sv sv_trim_left(const sv sv)
{
    if(sv.count <= 0) return (struct string_view) {
        .data  = "",
        .count = 0
    };
    size_t i = 0;
    while(isspace(sv.data[i]) && i < sv.count) {
        i++;
    }
    return (struct string_view) {
        .data  = sv.data  + i,
        .count = sv.count - i
    };
}

sv sv_trim_right(const sv sv)
{
    if(sv.count <= 0) return (struct string_view) {
        .data  = "",
        .count = 0
    };
    size_t i = 0;
    while(isspace(sv.data[(sv.count - 1) - i]) &&
             ((sv.count - 1) - i) >= 0) {
        i++;
    }
    return (struct string_view) {
        .data  = sv.data,
        .count = sv.count - i
    };
}

sv sv_trim(const sv sv)
{
    if(sv.count <= 0 ) return (struct string_view) {
        .data = "",
        .count = 0
    };
    return sv_trim_right(sv_trim_left(sv));
}

#endif // SV_IMPLEMENTATION

#endif // SV_H
