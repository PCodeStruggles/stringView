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

typedef struct string_view {
    const char *data;
    size_t     count;
} sv;

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

// Return whether sv1 and sv2 are equal
bool sv_equal(const sv sv1, const sv sv2);

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

// Retursn true if sv contains cstr, false otherwise
bool sv_contains(const sv sv, const char* cstr);

// Returns a new sv with leading spaces trimmed
sv sv_trim_left(const sv sv);

// Returns a new sv with trailing spaces trimmed
sv sv_trim_right(const sv sv);

// Return a new sv with both leading and trailing spaces trimmed
sv sv_trim(const sv sv);

// Return the content of the sv passed as argument up to the delimeter passed as argument.
// Increment the count of the sv passed as argument in order to point to
// the next token.
sv sv_split_by_delim(sv* string_view, const char c);

// Return the content of the sv passed as argument up to the first space.
// Increment the count of the sv passed as argument in order to point to
// the next token.
sv sv_split_by_space(sv* string_view);

#ifdef SV_IMPLEMENTATION

sv sv_from_cstr(const char *cstr)
{
    if (cstr == NULL) SV_PANIC("sv_from_cstr: cstr argument cannot be NULL");
    return (sv) {
        .data = cstr,
        .count = strlen(cstr)
    };
}

bool sv_equal(const sv sv1, const sv sv2)
{
    if(sv1.count != sv2.count) return false;
    for(size_t i = 0; i < sv1.count; i++) {
        if(sv1.data[i] != sv2.data[i]) return false;
    }
    return true;
}

sv sv_remove_prefix(const sv sv, const char *prefix)
{
    if (prefix == NULL) SV_PANIC("sv_remove_prefix: prefix argument cannot be NULL");
    if (sv_starts_with(sv, prefix)) {
        size_t prefix_len = strlen(prefix);
        return (struct string_view) {
            .data  = sv.data  + prefix_len,
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
            .data  = sv.data,
            .count = sv.count - suffix_len
        };
    } else {
        return sv;
    }
}

bool sv_contains(const sv sv, const char* cstr)
{
    if(cstr == NULL || strlen(cstr) > sv.count) return false;
    size_t cstr_len = strlen(cstr);
    size_t i = 0;
    while(i < sv.count) {
        for (size_t k = i, j = 0;
                j < cstr_len && sv.data[k] == cstr[j];
                k++, j++) {
            if(j == (cstr_len - 1)) return true;
        }
        i++;
    }
    return false;
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

sv sv_split_by_delim(sv* string_view, const char c)
{
    if(string_view == NULL || string_view->count <= 0) {
        return sv_from_cstr("");
    }

    for(; string_view->count > 0 && isspace(string_view->data[0]);
            string_view->data  += 1,
            string_view->count -= 1)
        ;

    size_t i = 0;
    while(i < string_view->count && string_view->data[i] != c) i++;

    sv ret = { .data = string_view->data, .count = i };

    string_view->data  = string_view->data  + i;
    string_view->count = string_view->count - i;

    return ret;
}

sv sv_split_by_space(sv* string_view)
{
    if(string_view == NULL || string_view->count <= 0) {
        return sv_from_cstr("");
    } else {
        return sv_split_by_delim(string_view, ' ');
    }
}

#endif // SV_IMPLEMENTATION

#endif // SV_H
