#include <stdio.h>
#include <string.h>

#include "../unity/unity.h"
#define SV_IMPLEMENTATION
#include "../sv.h"

void setUp(void) {return;}
void tearDown(void) {return;}

/* sv_from_cstr Tests */

void sv_from_cstr_passingString(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(4, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_from_cstr_passingEmptyString(void)
{
    const char* cstr = "";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(0, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_from_cstr_passingStringWithLeadingSpaces(void)
{
    const char* cstr = "             The quick brown fox jumps over the lazy dog. ";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_from_cstr_passingLongString1(void)
{
    const char* cstr = "The quick brown fox jumps over the lazy dog. ";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_from_cstr_passingLongString2(void)
{
    const char* cstr = "How valiantly did Beowulf fight the grim night-stalker! ";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

/* sv_at Tests */

void sv_at_passingEmptyString(void)
{
    const char* cstr = "";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(0, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_at(actual, 0);
    TEST_ASSERT_EQUAL_INT(0, c);
}

void sv_at_passingOutOfBoundPos(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(4, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_at(actual, 4);
    TEST_ASSERT_EQUAL_INT(0, c);
}

void sv_at_passingOutOfBoundPos2(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(4, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_at(actual, 5);
    TEST_ASSERT_EQUAL_INT(0, c);
}

void sv_at_passingString(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(4, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_at(actual, 0);
    TEST_ASSERT_EQUAL_CHAR(cstr[0], c);
}

void sv_at_passingString2(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(4, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_at(actual, 2);
    TEST_ASSERT_EQUAL_CHAR(cstr[2], c);
}

void sv_at_passingLongString1(void)
{
    const char* cstr = "The quick brown fox jumps over the lazy dog. ";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_at(actual, 10);
    TEST_ASSERT_EQUAL_CHAR(cstr[10], c);
}

void sv_at_passingLongString2(void)
{
    const char* cstr = "How valiantly did Beowulf fight the grim night-stalker! ";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_at(actual, 17);
    TEST_ASSERT_EQUAL_CHAR(cstr[17], c);
}


/* sv_front Tests */
// TODO: Add tests to verify correct behaviour 
// when we shift forward the data pointer

void sv_front_passingString(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(4, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_front(actual);
    TEST_ASSERT_EQUAL_CHAR(cstr[0], c);
}

void sv_front_passingLongString1(void)
{
    const char* cstr = "The quick brown fox jumps over the lazy dog. ";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_front(actual);
    TEST_ASSERT_EQUAL_CHAR(cstr[0], c);
}

void sv_front_passingLongString2(void)
{
    const char* cstr = "How valiantly did Beowulf fight the grim night-stalker! ";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_front(actual);
    TEST_ASSERT_EQUAL_CHAR(cstr[0], c);
}

/* sv_back Tests */

void sv_back_passingString(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(4, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_back(actual);
    TEST_ASSERT_EQUAL_CHAR('e', c);
}

void sv_back_passingLongString1(void)
{
    const char* cstr = "The quick brown fox jumps over the lazy dog. ";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_back(actual);
    TEST_ASSERT_EQUAL_CHAR(' ', c);
}

void sv_back_passingLongString2(void)
{
    const char* cstr = "How valiantly did Beowulf fight the grim night-stalker!";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_back(actual);
    TEST_ASSERT_EQUAL_CHAR('!', c);
}

/* sv_len Tests */

void sv_len_passingString(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    size_t len = sv_len(actual);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), len);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_len_passingEmptyString(void)
{
    const char* cstr = "";
    sv actual = sv_from_cstr(cstr);
    size_t len = sv_len(actual);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), len);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_len_passingStringWithLeadingSpaces(void)
{
    const char* cstr = "             The quick brown fox jumps over the lazy dog. ";
    sv actual = sv_from_cstr(cstr);
    size_t len = sv_len(actual);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), len);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_len_passingLongString1(void)
{
    const char* cstr = "The quick brown fox jumps over the lazy dog. ";
    sv actual = sv_from_cstr(cstr);
    size_t len = sv_len(actual);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), len);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_len_passingLongString2(void)
{
    const char* cstr = "How valiantly did Beowulf fight the grim night-stalker! ";
    sv actual = sv_from_cstr(cstr);
    size_t len = sv_len(actual);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), len);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

/* sv_emtpy Tests */

void sv_empty_passingString(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    bool ret = sv_empty(actual);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_empty_passingEmptyString(void)
{
    const char* cstr = "";
    sv actual = sv_from_cstr(cstr);
    bool ret = sv_empty(actual);
    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_empty_passingStringWithSpacesOnly(void)
{
    const char* cstr = "        ";
    sv actual = sv_from_cstr(cstr);
    bool ret = sv_empty(actual);
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_empty_passingStringWithLeadingSpaces(void)
{
    const char* cstr = "             The quick brown fox jumps over the lazy dog. ";
    sv actual = sv_from_cstr(cstr);
    bool ret = sv_empty(actual);
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_empty_passingLongString1(void)
{
    const char* cstr = "The quick brown fox jumps over the lazy dog. ";
    sv actual = sv_from_cstr(cstr);
    bool ret = sv_empty(actual);
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_empty_passingLongString2(void)
{
    const char* cstr = "How valiantly did Beowulf fight the grim night-stalker! ";
    sv actual = sv_from_cstr(cstr);
    bool ret = sv_empty(actual);
    TEST_ASSERT_FALSE(ret);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

/* sv_remove_prefix Tests */

void sv_remove_prefix_passingString(void)
{
    const char* cstr = "name_surname";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_prefix = sv_remove_prefix(actual, "name_");
    TEST_ASSERT_EQUAL_STRING_LEN("surname", 
            actual_no_prefix.data, sv_len(actual_no_prefix));
}

void sv_remove_prefix_passingString2(void)
{
    const char* cstr = "name__surname";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_prefix = sv_remove_prefix(actual, "name_");
    TEST_ASSERT_EQUAL_STRING_LEN("_surname", 
            actual_no_prefix.data, sv_len(actual_no_prefix));
}

void sv_remove_prefix_passingString3(void)
{
    const char* cstr = "name_name_surname";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_prefix = sv_remove_prefix(actual, "name_");
    TEST_ASSERT_EQUAL_STRING_LEN("name_surname", 
            actual_no_prefix.data, sv_len(actual_no_prefix));
}

void sv_remove_prefix_passingStringWithUnmatchingPrefix(void)
{
    const char* cstr = "nome_name_surname";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_prefix = sv_remove_prefix(actual, "name_");
    TEST_ASSERT_EQUAL_STRING_LEN("nome_name_surname", 
            actual_no_prefix.data, sv_len(actual_no_prefix));
}

void sv_remove_prefix_passingStringWithUnmatchingPrefix2(void)
{
    const char* cstr = "nam_surname";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_prefix = sv_remove_prefix(actual, "name_");
    TEST_ASSERT_EQUAL_STRING_LEN("nam_surname", 
            actual_no_prefix.data, sv_len(actual_no_prefix));
}

void sv_remove_prefix_passingEmptrySv(void)
{
    const char* cstr = "";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_prefix = sv_remove_prefix(actual, "name_");
    TEST_ASSERT_EQUAL_STRING_LEN("", 
            actual_no_prefix.data, sv_len(actual_no_prefix));
}

/* sv_remove_suffix Tests */

void sv_remove_suffix_passingString(void)
{
    const char* cstr = "name_surname";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_suffix = sv_remove_suffix(actual, "surname");
    TEST_ASSERT_EQUAL_STRING_LEN("name_", 
            actual_no_suffix.data, sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingString2(void)
{
    const char* cstr = "name__surname";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_suffix = sv_remove_suffix(actual, "surname");
    TEST_ASSERT_EQUAL_STRING_LEN("name__", 
            actual_no_suffix.data, sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingString3(void)
{
    const char* cstr = "name_name_surname";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_suffix = sv_remove_suffix(actual, "surname");
    TEST_ASSERT_EQUAL_STRING_LEN("name_name_", 
            actual_no_suffix.data, sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingString4(void)
{
    const char* cstr = "_surname";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_suffix = sv_remove_suffix(actual, "surname");
    TEST_ASSERT_EQUAL_STRING_LEN("_", 
            actual_no_suffix.data, sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingString5(void)
{
    const char* cstr = "surname";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_suffix = sv_remove_suffix(actual, "surname");
    TEST_ASSERT_EQUAL_STRING_LEN("", 
            actual_no_suffix.data, sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingStringWithUnmatchingPrefix(void)
{
    const char* cstr = "name_name_surnome";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_suffix = sv_remove_suffix(actual, "surnome");
    TEST_ASSERT_EQUAL_STRING_LEN("name_name_surnome", 
            actual_no_suffix.data, sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingStringWithUnmatchingPrefix2(void)
{
    const char* cstr = "name_name_surname_";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_suffix = sv_remove_suffix(actual, "surname");
    TEST_ASSERT_EQUAL_STRING_LEN("name_name_surname_", 
            actual_no_suffix.data, sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingEmptrySv(void)
{
    const char* cstr = "";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_suffix = sv_remove_suffix(actual, "surname");
    TEST_ASSERT_EQUAL_STRING_LEN("", 
            actual_no_suffix.data, sv_len(actual_no_suffix));
}

void sv_remove_suffixprefix_combined(void)
{
    const char* cstr = "sv_remove_suffix";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    sv actual_no_prefix = sv_remove_prefix(actual, "sv_");
    sv actual_no_suffix = sv_remove_suffix(actual_no_prefix, "_suffix");
    TEST_ASSERT_EQUAL_STRING_LEN("remove", 
            actual_no_suffix.data, sv_len(actual_no_suffix));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(sv_from_cstr_passingString);
    RUN_TEST(sv_from_cstr_passingEmptyString);
    RUN_TEST(sv_from_cstr_passingStringWithLeadingSpaces);
    RUN_TEST(sv_from_cstr_passingLongString1);
    RUN_TEST(sv_from_cstr_passingLongString2);
    RUN_TEST(sv_at_passingEmptyString);
    RUN_TEST(sv_at_passingString);
    RUN_TEST(sv_at_passingOutOfBoundPos);
    RUN_TEST(sv_at_passingOutOfBoundPos2);
    RUN_TEST(sv_at_passingString2);
    RUN_TEST(sv_at_passingLongString1);
    RUN_TEST(sv_at_passingLongString2);
    RUN_TEST(sv_front_passingString);
    RUN_TEST(sv_front_passingLongString1);
    RUN_TEST(sv_front_passingLongString2);
    RUN_TEST(sv_back_passingString);
    RUN_TEST(sv_back_passingLongString1);
    RUN_TEST(sv_back_passingLongString2);
    RUN_TEST(sv_len_passingString);
    RUN_TEST(sv_len_passingEmptyString);
    RUN_TEST(sv_len_passingStringWithLeadingSpaces);
    RUN_TEST(sv_len_passingLongString1);
    RUN_TEST(sv_len_passingLongString2);
    RUN_TEST(sv_empty_passingString);
    RUN_TEST(sv_empty_passingEmptyString);
    RUN_TEST(sv_empty_passingStringWithSpacesOnly);
    RUN_TEST(sv_empty_passingStringWithLeadingSpaces);
    RUN_TEST(sv_empty_passingLongString1);
    RUN_TEST(sv_empty_passingLongString2);
    RUN_TEST(sv_remove_prefix_passingString);
    RUN_TEST(sv_remove_prefix_passingString2);
    RUN_TEST(sv_remove_prefix_passingString3);
    RUN_TEST(sv_remove_prefix_passingStringWithUnmatchingPrefix);
    RUN_TEST(sv_remove_prefix_passingStringWithUnmatchingPrefix2);
    RUN_TEST(sv_remove_prefix_passingEmptrySv);
    RUN_TEST(sv_remove_suffix_passingString);
    RUN_TEST(sv_remove_suffix_passingString2);
    RUN_TEST(sv_remove_suffix_passingString3);
    RUN_TEST(sv_remove_suffix_passingString4);
    RUN_TEST(sv_remove_suffix_passingString5);
    RUN_TEST(sv_remove_suffix_passingStringWithUnmatchingPrefix);
    RUN_TEST(sv_remove_suffix_passingStringWithUnmatchingPrefix2);
    RUN_TEST(sv_remove_suffix_passingEmptrySv);
    RUN_TEST(sv_remove_suffixprefix_combined);
    UNITY_END();
    return 0;
}
