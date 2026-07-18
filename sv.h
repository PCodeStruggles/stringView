#ifndef SV_H
#define SV_H

/**
 * TODO: Add function to convert sv string to int.
 * TODO: Add function to convert sv string to float.
*/

#include <assert.h>
#include <ctype.h>
#include <errno.h>
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
} String_view;

/**
 * @brief create a string view from the cstr passed as argument
 * @param cstr R string
 * @return sv struct with sv.data = cstr and sv.count = strlen(cstr)
 * if cstr == NULL, returns an empty sv.
 */
String_view sv_from_cstr(const char *cstr);

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
bool sv_equal(const String_view sv1, const String_view sv2);

/**
 * @brief check wether the content of the string view is equal to the cstr
 * @param sv1 first string view used in the comparison
 * @param cstr c string to be compared against string_view.data
 * @return true if string_view.data == cstr, false otherwise
*/
bool sv_equal_cstr(const String_view string_view, const char *cstr);

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
String_view sv_remove_prefix(const String_view sv, const char *prefix);

/**
 * @brief if the string view data ends with suffix, reduce the sv.count
 * effectively "removing" the suffix.
 * @param sv string view to be used
 * @prefix cstr to be stripped from sv.data
 * @return a sv with the count reduced in order to strip the suffix if
 * sv.data ends with suffix, returns the same string view passed as argument
 * otherwise.
*/
String_view sv_remove_suffix(const String_view sv, const char *suffix);

/**
 * @brief check whethere the sv.data starts with prefix
 * @param sv string view to be used
 * @param prefix cstr
 * @return return true if sv.data starts with prefix, false otherwise
*/
bool sv_starts_with(const String_view sv, const char *prefix);

/**
 * @brief check whethere the sv.data ends with suffix
 * @param sv string view to be used
 * @param suffix cstr
 * @return return true if sv.data ends with suffix, false otherwise
*/
bool sv_ends_with(const String_view sv, const char *suffix);

/**
 * @brief check whethere the sv.data contains cstr
 * @param sv string view to be used
 * @param cstr
 * @return return true if sv.data contains cstr, false otherwise
*/
bool sv_contains(const String_view sv, const char *cstr);

/**
 * @brief strip any leading space chars by increasing the sv.data pointer accordingly.
 * @param sv string view to be used
 * @return return a new sv with the data pointer increased so that any leading
 * spaces are stripped.
*/
String_view sv_trim_left(const String_view sv);

/**
 * @brief strip any trailing space chars by decreasing the sv.count accordingly.
 * @param sv string view to be used
 * @return return a new sv with the count decreased so that any trailing
 * spaces are stripped.
*/
String_view sv_trim_right(const String_view sv);

/**
 * @brief strip any leading and trailing spaces
 * @param sv string view to be used
 * @return return a new sv with the pointer increased and/or the count decreased
 * so that any leading or trailing spaces get stripped.
*/
String_view sv_trim(const String_view sv);

/**
 * @brief split the sv.data up to the first delimeter passsed as argument.
 * @param *string_view pointer to the string view to be used
 * @param c delimeter
 * @return return a string view containing the sv.data up to the first occurrence
 * of the delimeter passed as argument. If the delimeter is not found, return
 * the string view pointed to by the pointer passed as argument.
*/
String_view sv_split_by_delim(String_view *sv, const char c);

/**
 * @brief split the sv.data up to the first space.
 * @param *string_view pointer to the string view to be used
 * @param c delimeter
 * @return return a string view containing the sv.data up to the first space.
 * If no space is found, the string view pointed to by the pointer passed as argument.
*/
String_view sv_split_by_space(String_view *sv);

/**
 * @brief skip the first n chars in the string.
 * @param string_view to be used as source.
 * @param n number of chars to be skipped.
 * @return return a string view with the data pointer advanced by n chars.
 * if n is greater than string_view.count, return empty sv.
*/
String_view sv_skip_n_chars(String_view sv, size_t n);

/**
 * @brief read the file located at file_path into a sv.
 * @param input file path.
 * @return pointer to sv that contains tha content of the file provided in input.
*/
String_view* sv_read_entire_file(const char* file_path);

#ifdef SV_IMPLEMENTATION

String_view sv_from_cstr(const char *cstr)
{
    if (cstr == NULL) SV_PANIC("sv_from_cstr: cstr argument cannot be NULL");
    return (String_view) {
        .data  = cstr,
        .count = strlen(cstr)
    };
}

bool sv_equal(const String_view sv1, const String_view sv2)
{
    if (sv1.count != sv2.count) return false;
    return memcmp(sv1.data, sv2.data, sv1.count) == 0;
}

// TODO: use memcmp for the comparison
bool sv_equal_cstr(const String_view sv, const char *cstr)
{
    if (cstr == NULL) {
        return false;
    }
    if (strlen(cstr) != sv.count) {
        return false;
    }
    for (size_t i = 0; i < sv.count; i++) {
        if (cstr[i] != sv.data[i]) {
            return false;
        }
    }
    return true;
}

String_view sv_remove_prefix(const String_view sv, const char *prefix)
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

String_view sv_remove_suffix(const String_view sv, const char *suffix)
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

bool sv_contains(const String_view sv, const char *cstr)
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

bool sv_starts_with(const String_view sv, const char *prefix)
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

bool sv_ends_with(const String_view sv, const char *suffix)
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

String_view sv_trim_left(const String_view sv)
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

String_view sv_trim_right(const String_view sv)
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

String_view sv_trim(const String_view sv)
{
    if (sv.count <= 0)
        return (struct string_view) {
        .data = "",
        .count = 0
    };
    return sv_trim_right(sv_trim_left(sv));
}

String_view sv_split_by_delim(String_view *sv, const char c)
{
    if (sv == NULL || sv->count <= 0) {
        return sv_from_cstr("");
    }

    for (;
            sv->count > 0 && isspace(sv->data[0]);
            sv->data  += 1,
            sv->count -= 1)
        ;

    size_t i = 0;
    while (i < sv->count && sv->data[i] != c) i++;

    String_view ret = {
        .data  = sv->data,
        .count = i
    };

    sv->data  = sv->data  + i;
    sv->count = sv->count - i;

    return ret;
}

String_view sv_split_by_space(String_view *sv)
{
    if (sv == NULL || sv->count <= 0) {
        return sv_from_cstr("");
    } else {
        return sv_split_by_delim(sv, ' ');
    }
}

String_view sv_skip_n_chars(String_view sv, size_t n)
{
    if(sv.count <= 0 || n >= sv.count) {
        return (String_view) {
            .data  = "",
            .count = 0,
        };
    } else {
        return (String_view) {
            .data  = sv.data  + n,
            .count = sv.count - n,
        };
    }
}

String_view* sv_read_entire_file(const char* file_path)
{
    if(file_path == NULL) SV_PANIC("File path cannot be NULL.");
    FILE *input_file = fopen(file_path, "r");
    if(input_file == NULL) {
        fprintf(stderr, "ERROR %s:%d : %d - %s\n", __FILE__, __LINE__,
                errno, strerror(errno));
        goto cleanup;
    }
    fseek(input_file, 0, SEEK_END);
    long num_bytes = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    String_view* content_sv = malloc(sizeof(struct string_view));
    if(content_sv == NULL) {
        fprintf(stderr, "ERROR %s:%d : %s\n",
                __FILE__,
                __LINE__,
                "Could not allocate enough memory for struct string_view");
        goto cleanup;
    }

    content_sv->data = malloc(sizeof(char) * num_bytes);
    if(content_sv->data == NULL) {
        fprintf(stderr, "ERROR %s:%d : %s\n",
                __FILE__,
                __LINE__,
                "Could not allocate enough buffer to store input file content");
        goto cleanup;
    }

    size_t num_bytes_read = fread(content_sv->data, sizeof(char), num_bytes, input_file);
    if(num_bytes != (long) num_bytes_read) {
        fprintf(stderr, "ERROR %s:%d : %s\n",
                __FILE__,
                __LINE__,
                "Could not read entire input file content into buffer");
        goto cleanup;
    }
    content_sv->count = num_bytes_read;

    fclose(input_file);

    return content_sv;

cleanup:
    if(content_sv) {
        if(content_sv->data) {
            free(content_sv->data);
            content_sv->data = NULL;
        }
        free(content_sv);
        content_sv = NULL;
    }
    fclose(input_file);
    return NULL;
}

#endif // SV_IMPLEMENTATION

#endif // SV_H
