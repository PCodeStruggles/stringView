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
    TEST_ASSERT_EQUAL_INT(-1, c);
}

void sv_at_passingOutOfBoundPos(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(4, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_at(actual, 4);
    TEST_ASSERT_EQUAL_INT(-1, c);
}

void sv_at_passingOutOfBoundPos2(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(4, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
    char c = sv_at(actual, 5);
    TEST_ASSERT_EQUAL_INT(-1, c);
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
    UNITY_END();
    return 0;
}
