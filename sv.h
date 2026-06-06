#ifndef SV_H
#define SV_H

/**
 * TODO: Add function to convert sv string to int.
 * TODO: Add function to convert sv string to float.
*/

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define SV_FMT "%.*s"
#define SV_ARG(sv) (int)(sv).count, (sv).data

#define SV_PANIC(msg)                                                          \
  do {                                                                         \
    fprintf(stderr, "PANIC %s:%d : %s\n", __FILE__, __LINE__, (msg));          \
    abort();                                                                   \
  } while (0)

typedef struct string_view {
    const char *data;
    size_t     count;
} sv;

/**
 * @brief create a string view from the cstr passed as argument
 * @param cstr R string
 * @return sv struct with sv.data = cstr and sv.count = strlen(cstr)
 * if cstr == NULL, returns an empty sv.
 */
sv sv_from_cstr(const char *cstr);

/**
 * @brief get the character sv.data[pos]
 * @param sv string view to be used
 * @param pos index of the char
*/
#define sv_at(sv, pos) (sv).data[assert((pos) >= 0 && (pos) < (sv).count), (pos)]

/**
 * @brief get the character at the beginnin of sv.data
 * @param sv string view to be used
*/
#define sv_front(sv) (sv).data[assert((sv).count > 0), 0]

/**
 * @brief get the character at the end of sv.data
 * @param sv string view to be used
*/
#define sv_back(sv) (sv).data[assert((sv).count > 0), (sv).count - 1]

/**
 * @brief get the string view lenght
 * @param sv string view to be used
*/
#define sv_len(sv) (sv).count

/**
 * @brief check whether the string view is empty (sv.data == "")
 * @param sv string view to be used
*/
#define sv_empty(sv) ((sv).count == 0)

/**
 * @brief check wether two string views are equal
 * @param sv1 first string view used in the comparison
 * @param sv2 second string view used in the comparison
 * @return true if sv1 == sv2, false otherwise
*/
bool sv_equal(const sv sv1, const sv sv2);

/**
 * @brief check wether the content of the string view is equal to the cstr
 * @param sv1 first string view used in the comparison
 * @param cstr c string to be compared against string_view.data
 * @return true if string_view.data == cstr, false otherwise
*/
bool sv_equal_cstr(const sv string_view, const char *cstr);

/**
 * @brief if the string view data begins with prefix, advance the pointer
 * to pointer to the first char in the sv.data after the prefix effectively
 * "removing" the prefix.
 * @param sv string view to be used
 * @prefix cstr to be stripped from sv.data
 * @return string view which point at the first char after the prefix if
 * sv.data starts with prefix, returns the same string view passed as
 * argument otherwise.
*/
sv sv_remove_prefix(const sv sv, const char *prefix);

/**
 * @brief if the string view data ends with suffix, reduce the sv.count
 * effectively "removing" the suffix.
 * @param sv string view to be used
 * @prefix cstr to be stripped from sv.data
 * @return a sv with the count reduced in order to strip the suffix if
 * sv.data ends with suffix, returns the same string view passed as argument
 * otherwise.
*/
sv sv_remove_suffix(const sv sv, const char *suffix);

/**
 * @brief check whethere the sv.data starts with prefix
 * @param sv string view to be used
 * @param prefix cstr
 * @return return true if sv.data starts with prefix, false otherwise
*/
bool sv_starts_with(const sv sv, const char *prefix);

/**
 * @brief check whethere the sv.data ends with suffix
 * @param sv string view to be used
 * @param suffix cstr
 * @return return true if sv.data ends with suffix, false otherwise
*/
bool sv_ends_with(const sv sv, const char *suffix);

/**
 * @brief check whethere the sv.data contains cstr
 * @param sv string view to be used
 * @param cstr
 * @return return true if sv.data contains cstr, false otherwise
*/
bool sv_contains(const sv sv, const char *cstr);

/**
 * @brief strip any leading space chars by increasing the sv.data pointer accordingly.
 * @param sv string view to be used
 * @return return a new sv with the data pointer increased so that any leading
 * spaces are stripped.
*/
sv sv_trim_left(const sv sv);

/**
 * @brief strip any trailing space chars by decreasing the sv.count accordingly.
 * @param sv string view to be used
 * @return return a new sv with the count decreased so that any trailing
 * spaces are stripped.
*/
sv sv_trim_right(const sv sv);

/**
 * @brief strip any leading and trailing spaces
 * @param sv string view to be used
 * @return return a new sv with the pointer increased and/or the count decreased
 * so that any leading or trailing spaces get stripped.
*/
sv sv_trim(const sv sv);

/**
 * @brief split the sv.data up to the first delimeter passsed as argument.
 * @param *string_view pointer to the string view to be used
 * @param c delimeter
 * @return return a string view containing the sv.data up to the first occurrence
 * of the delimeter passed as argument. If the delimeter is not found, return
 * the string view pointed to by the pointer passed as argument.
*/
sv sv_split_by_delim(sv *string_view, const char c);

/**
 * @brief split the sv.data up to the first space.
 * @param *string_view pointer to the string view to be used
 * @param c delimeter
 * @return return a string view containing the sv.data up to the first space.
 * If no space is found, the string view pointed to by the pointer passed as argument.
*/
sv sv_split_by_space(sv *string_view);

/**
 * @brief skip the first n chars in the string.
 * @param string_view to be used as source.
 * @param n number of chars to be skipped.
 * @return return a string view with the data pointer advanced by n chars.
 * if n is greater than string_view.count, return empty sv.
*/
sv sv_skip_n_chars(sv string_view, size_t n);

#ifdef SV_IMPLEMENTATION

sv sv_from_cstr(const char *cstr)
{
    if (cstr == NULL) SV_PANIC("sv_from_cstr: cstr argument cannot be NULL");
    return (sv) {
        .data  = cstr,
        .count = strlen(cstr)
    };
}

bool sv_equal(const sv sv1, const sv sv2)
{
    if (sv1.count != sv2.count) return false;
    for (size_t i = 0; i < sv1.count; i++) {
        if (sv1.data[i] != sv2.data[i]) return false;
    }
    return true;
}

bool sv_equal_cstr(const sv string_view, const char *cstr)
{
    if (cstr == NULL) {
        return false;
    }
    if (strlen(cstr) != string_view.count) {
        return false;
    }
    for (size_t i = 0; i < string_view.count; i++) {
        if (cstr[i] != string_view.data[i]) {
            return false;
        }
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

bool sv_contains(const sv sv, const char *cstr)
{
    if (cstr == NULL || strlen(cstr) > sv.count) return false;
    size_t cstr_len = strlen(cstr);
    size_t i = 0;
    while (i < sv.count) {
        for (size_t k = i, j = 0;
                j < cstr_len && sv.data[k] == cstr[j];
                k++, j++) {
            if (j == (cstr_len - 1)) return true;
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
    if (sv.count <= 0)
        return (struct string_view) {
        .data = "", .count = 0
    };
    size_t i = 0;
    while (isspace(sv.data[i]) && i < sv.count) {
        i++;
    }
    return (struct string_view) {
        .data = sv.data   + i,
        .count = sv.count - i
    };
}

sv sv_trim_right(const sv sv)
{
    if (sv.count <= 0)
        return (struct string_view) {
        .data = "",
        .count = 0
    };
    size_t i = 0;
    while (isspace(sv.data[(sv.count - 1) - i]) && ((sv.count - 1) - i) >= 0) {
        i++;
    }
    return (struct string_view) {
        .data  = sv.data,
        .count = sv.count - i
    };
}

sv sv_trim(const sv sv)
{
    if (sv.count <= 0)
        return (struct string_view) {
        .data = "",
        .count = 0
    };
    return sv_trim_right(sv_trim_left(sv));
}

sv sv_split_by_delim(sv *string_view, const char c)
{
    if (string_view == NULL || string_view->count <= 0) {
        return sv_from_cstr("");
    }

    for (;
            string_view->count > 0 && isspace(string_view->data[0]);
            string_view->data  += 1,
            string_view->count -= 1)
        ;

    size_t i = 0;
    while (i < string_view->count && string_view->data[i] != c) i++;

    sv ret = {
        .data  = string_view->data,
        .count = i
    };

    string_view->data  = string_view->data  + i;
    string_view->count = string_view->count - i;

    return ret;
}

sv sv_split_by_space(sv *string_view)
{
    if (string_view == NULL || string_view->count <= 0) {
        return sv_from_cstr("");
    } else {
        return sv_split_by_delim(string_view, ' ');
    }
}

sv sv_skip_n_chars(sv string_view, size_t n)
{
    if(string_view.count <= 0 || n >= string_view.count) {
        return (struct string_view) {
            .data  = "",
            .count = 0,
        };
    } else {
        return (struct string_view) {
            .data  = string_view.data  + n,
            .count = string_view.count - n,
        };
    }
}

#endif // SV_IMPLEMENTATION

#endif // SV_H
