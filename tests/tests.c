#include <stdio.h>
#include <string.h>

#include "../unity/unity.h"
#define SV_IMPLEMENTATION
#include "../sv.h"

void setUp(void) { return; }
void tearDown(void) { return; }

/* sv_from_cstr Tests */

void sv_from_cstr_passingString(void) {
  const char *cstr = "name";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(4, actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_from_cstr_passingEmptyString(void) {
  const char *cstr = "";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(0, actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_from_cstr_passingStringWithLeadingSpaces(void) {
  const char *cstr =
      "             The quick brown fox jumps over the lazy dog. ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_from_cstr_passingLongString1(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog. ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_from_cstr_passingLongString2(void) {
  const char *cstr = "How valiantly did Beowulf fight the grim night-stalker! ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

/* sv_equal Tests */

void sv_equal_passingIdenticalSvs(void) {
  const char *cstr = "Hello World!";
  sv sv1 = sv_from_cstr(cstr);
  sv sv2 = sv_from_cstr(cstr);
  bool ret = sv_equal(sv1, sv2);
  TEST_ASSERT_TRUE_MESSAGE(ret, "bool ret = sv_equal(sv1, sv2) should return true");
}

void sv_equal_passingDifferentSvs(void) {
  const char *cstr1 = "Hello World!";
  const char *cstr2 = "hello world!";
  sv sv1 = sv_from_cstr(cstr1);
  sv sv2 = sv_from_cstr(cstr2);
  bool ret = sv_equal(sv1, sv2);
  TEST_ASSERT_FALSE_MESSAGE(ret, "bool ret = sv_equal(sv1, sv2) should return false"); }

void sv_equal_passingDifferentSvsInSize(void) {
  const char *cstr1 = "Hello World!";
  const char *cstr2 = "The quick brown fox jumps over the lazy dog.";
  sv sv1 = sv_from_cstr(cstr1);
  sv sv2 = sv_from_cstr(cstr2);
  bool ret = sv_equal(sv1, sv2);
  TEST_ASSERT_FALSE_MESSAGE(ret, "bool ret = sv_equal(sv1, sv2) should return false");
}

void sv_equal_passingOneEmptySV(void) {
  const char *cstr1 = "Hello World!";
  const char *cstr2 = "";
  sv sv1 = sv_from_cstr(cstr1);
  sv sv2 = sv_from_cstr(cstr2);
  bool ret = sv_equal(sv1, sv2);
  TEST_ASSERT_FALSE_MESSAGE(ret, "bool ret = sv_equal(sv1, sv2) should return false");
}

void sv_equal_passingTwoEmptySvs(void) {
  const char *cstr1 = "";
  const char *cstr2 = "";
  sv sv1 = sv_from_cstr(cstr1);
  sv sv2 = sv_from_cstr(cstr2);
  bool ret = sv_equal(sv1, sv2);
  TEST_ASSERT_TRUE_MESSAGE(ret, "bool ret = sv_equal(sv1, sv2) should return true");
}

/* sv_equal_cstr test */

void sv_equal_cstr_passingSameString(void) {
  const char *cstr = "Hello World!";
  sv sv1 = sv_from_cstr(cstr);
  bool ret = sv_equal_cstr(sv1, cstr);
  TEST_ASSERT_TRUE_MESSAGE(ret, "bool ret = sv_equal_cstr(sv1, cstr) should return true");
}

void sv_equal_cstr_passingDifferentString(void) {
  const char *cstr = "Hello World!";
  sv sv1 = sv_from_cstr("Hello Mundo!");
  bool ret = sv_equal_cstr(sv1, cstr);
  TEST_ASSERT_FALSE_MESSAGE(ret, "bool ret = sv_equal_cstr(sv1, cstr) should return false");
}

void sv_equal_cstr_passingNULLAsCstr(void) {
  sv sv1 = sv_from_cstr("Hello World!");
  bool ret = sv_equal_cstr(sv1, NULL);
  TEST_ASSERT_FALSE_MESSAGE(ret, "bool ret = sv_equal_cstr(sv1, NULL) should return false");
}

void sv_equal_cstr_passingEmptyStringInBothSvAndCstr(void) {
  const char *cstr = "";
  sv sv1 = sv_from_cstr(cstr);
  bool ret = sv_equal_cstr(sv1, cstr);
  TEST_ASSERT_TRUE_MESSAGE(ret, "bool ret = sv_equal_cstr(sv1, cstr) should return true");
}

void sv_equal_cstr_passingSameEscapeSequence(void) {
  const char *cstr = "\t";
  sv sv1 = sv_from_cstr(cstr);
  bool ret = sv_equal_cstr(sv1, cstr);
  TEST_ASSERT_TRUE_MESSAGE(ret, "bool ret = sv_equal_cstr(sv1, cstr) should return true");
}

/* sv_at Tests */

void sv_at_passingString(void) {
  const char *cstr = "name";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(4, actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  char c = sv_at(actual, 0);
  TEST_ASSERT_EQUAL_CHAR(cstr[0], c);
}

void sv_at_passingString2(void) {
  const char *cstr = "name";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(4, actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  char c = sv_at(actual, 2);
  TEST_ASSERT_EQUAL_CHAR(cstr[2], c);
}

void sv_at_passingLongString1(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog. ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  char c = sv_at(actual, 10);
  TEST_ASSERT_EQUAL_CHAR(cstr[10], c);
}

void sv_at_passingLongString2(void) {
  const char *cstr = "How valiantly did Beowulf fight the grim night-stalker! ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  char c = sv_at(actual, 17);
  TEST_ASSERT_EQUAL_CHAR(cstr[17], c);
}

/* sv_front Tests */

void sv_front_passingString(void) {
  const char *cstr = "name";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(4, actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  char c = sv_front(actual);
  TEST_ASSERT_EQUAL_CHAR(cstr[0], c);
}

void sv_front_passingLongString1(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog. ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  char c = sv_front(actual);
  TEST_ASSERT_EQUAL_CHAR(cstr[0], c);
}

void sv_front_passingLongString2(void) {
  const char *cstr = "How valiantly did Beowulf fight the grim night-stalker! ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  char c = sv_front(actual);
  TEST_ASSERT_EQUAL_CHAR(cstr[0], c);
}

/* sv_back Tests */

void sv_back_passingString(void) {
  const char *cstr = "name";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(4, actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  char c = sv_back(actual);
  TEST_ASSERT_EQUAL_CHAR('e', c);
}

void sv_back_passingLongString1(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog. ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  char c = sv_back(actual);
  TEST_ASSERT_EQUAL_CHAR(' ', c);
}

void sv_back_passingLongString2(void) {
  const char *cstr = "How valiantly did Beowulf fight the grim night-stalker!";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  char c = sv_back(actual);
  TEST_ASSERT_EQUAL_CHAR('!', c);
}

/* sv_len Tests */

void sv_len_passingString(void) {
  const char *cstr = "name";
  sv actual = sv_from_cstr(cstr);
  size_t len = sv_len(actual);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), len);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_len_passingEmptyString(void) {
  const char *cstr = "";
  sv actual = sv_from_cstr(cstr);
  size_t len = sv_len(actual);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), len);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_len_passingStringWithLeadingSpaces(void) {
  const char *cstr =
      "             The quick brown fox jumps over the lazy dog. ";
  sv actual = sv_from_cstr(cstr);
  size_t len = sv_len(actual);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), len);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_len_passingLongString1(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog. ";
  sv actual = sv_from_cstr(cstr);
  size_t len = sv_len(actual);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), len);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_len_passingLongString2(void) {
  const char *cstr = "How valiantly did Beowulf fight the grim night-stalker! ";
  sv actual = sv_from_cstr(cstr);
  size_t len = sv_len(actual);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), len);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

/* sv_emtpy Tests */

void sv_empty_passingString(void) {
  const char *cstr = "name";
  sv actual = sv_from_cstr(cstr);
  bool ret = sv_empty(actual);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
  TEST_ASSERT_FALSE(ret);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_empty_passingEmptyString(void) {
  const char *cstr = "";
  sv actual = sv_from_cstr(cstr);
  bool ret = sv_empty(actual);
  TEST_ASSERT_TRUE(ret);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_empty_passingStringWithSpacesOnly(void) {
  const char *cstr = "        ";
  sv actual = sv_from_cstr(cstr);
  bool ret = sv_empty(actual);
  TEST_ASSERT_FALSE(ret);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_empty_passingStringWithLeadingSpaces(void) {
  const char *cstr =
      "             The quick brown fox jumps over the lazy dog. ";
  sv actual = sv_from_cstr(cstr);
  bool ret = sv_empty(actual);
  TEST_ASSERT_FALSE(ret);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_empty_passingLongString1(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog. ";
  sv actual = sv_from_cstr(cstr);
  bool ret = sv_empty(actual);
  TEST_ASSERT_FALSE(ret);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

void sv_empty_passingLongString2(void) {
  const char *cstr = "How valiantly did Beowulf fight the grim night-stalker! ";
  sv actual = sv_from_cstr(cstr);
  bool ret = sv_empty(actual);
  TEST_ASSERT_FALSE(ret);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), sv_len(actual));
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}

/* sv_remove_prefix Tests */

void sv_remove_prefix_passingString(void) {
  const char *cstr = "name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_prefix = sv_remove_prefix(actual, "name_");
  TEST_ASSERT_EQUAL_STRING_LEN("surname", actual_no_prefix.data,
                               sv_len(actual_no_prefix));
}

void sv_remove_prefix_passingString2(void) {
  const char *cstr = "name__surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_prefix = sv_remove_prefix(actual, "name_");
  TEST_ASSERT_EQUAL_STRING_LEN("_surname", actual_no_prefix.data,
                               sv_len(actual_no_prefix));
}

void sv_remove_prefix_passingString3(void) {
  const char *cstr = "name_name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_prefix = sv_remove_prefix(actual, "name_");
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", actual_no_prefix.data,
                               sv_len(actual_no_prefix));
}

void sv_remove_prefix_passingStringWithUnmatchingPrefix(void) {
  const char *cstr = "nome_name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_prefix = sv_remove_prefix(actual, "name_");
  TEST_ASSERT_EQUAL_STRING_LEN("nome_name_surname", actual_no_prefix.data,
                               sv_len(actual_no_prefix));
}

void sv_remove_prefix_passingStringWithUnmatchingPrefix2(void) {
  const char *cstr = "nam_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_prefix = sv_remove_prefix(actual, "name_");
  TEST_ASSERT_EQUAL_STRING_LEN("nam_surname", actual_no_prefix.data,
                               sv_len(actual_no_prefix));
}

void sv_remove_prefix_passingEmptrySv(void) {
  const char *cstr = "";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_prefix = sv_remove_prefix(actual, "name_");
  TEST_ASSERT_EQUAL_STRING_LEN("", actual_no_prefix.data,
                               sv_len(actual_no_prefix));
}

/* sv_remove_suffix Tests */

void sv_remove_suffix_passingString(void) {
  const char *cstr = "name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_suffix = sv_remove_suffix(actual, "surname");
  TEST_ASSERT_EQUAL_STRING_LEN("name_", actual_no_suffix.data,
                               sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingString2(void) {
  const char *cstr = "name__surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_suffix = sv_remove_suffix(actual, "surname");
  TEST_ASSERT_EQUAL_STRING_LEN("name__", actual_no_suffix.data,
                               sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingString3(void) {
  const char *cstr = "name_name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_suffix = sv_remove_suffix(actual, "surname");
  TEST_ASSERT_EQUAL_STRING_LEN("name_name_", actual_no_suffix.data,
                               sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingString4(void) {
  const char *cstr = "_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_suffix = sv_remove_suffix(actual, "surname");
  TEST_ASSERT_EQUAL_STRING_LEN("_", actual_no_suffix.data,
                               sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingString5(void) {
  const char *cstr = "surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_suffix = sv_remove_suffix(actual, "surname");
  TEST_ASSERT_EQUAL_STRING_LEN("", actual_no_suffix.data,
                               sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingStringWithUnmatchingSuffix(void) {
  const char *cstr = "name_name_surnome";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_suffix = sv_remove_suffix(actual, "surnome");
  TEST_ASSERT_EQUAL_STRING_LEN("name_name_surnome", actual_no_suffix.data,
                               sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingStringWithUnmatchingSuffix2(void) {
  const char *cstr = "name_name_surname_";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_suffix = sv_remove_suffix(actual, "surname");
  TEST_ASSERT_EQUAL_STRING_LEN("name_name_surname_", actual_no_suffix.data,
                               sv_len(actual_no_suffix));
}

void sv_remove_suffix_passingEmptrySv(void) {
  const char *cstr = "";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_suffix = sv_remove_suffix(actual, "surname");
  TEST_ASSERT_EQUAL_STRING_LEN("", actual_no_suffix.data,
                               sv_len(actual_no_suffix));
}

void sv_remove_suffixprefix_combined(void) {
  const char *cstr = "sv_remove_suffix";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv actual_no_prefix = sv_remove_prefix(actual, "sv_");
  sv actual_no_suffix = sv_remove_suffix(actual_no_prefix, "_suffix");
  TEST_ASSERT_EQUAL_STRING_LEN("remove", actual_no_suffix.data,
                               sv_len(actual_no_suffix));
}

/* sv_starts_with Tests */

void sv_starts_with_passingString(void) {
  const char *cstr = "name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_starts_with(actual, "name_");
  TEST_ASSERT_TRUE(ret);
}

void sv_starts_with_passingString2(void) {
  const char *cstr = "name__surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_starts_with(actual, "name_");
  TEST_ASSERT_TRUE(ret);
}

void sv_starts_with_passingString3(void) {
  const char *cstr = "name_name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_starts_with(actual, "name_");
  TEST_ASSERT_TRUE(ret);
}

void sv_starts_with_passingStringWithUnmatchingPrefix(void) {
  const char *cstr = "nome_name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_starts_with(actual, "name_");
  TEST_ASSERT_FALSE(ret);
}

void sv_starts_with_passingStringWithUnmatchingPrefix2(void) {
  const char *cstr = "nam_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_starts_with(actual, "name_");
  TEST_ASSERT_FALSE(ret);
}

void sv_starts_with_passingEmptrySv(void) {
  const char *cstr = "";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_starts_with(actual, "name_");
  TEST_ASSERT_FALSE(ret);
}

/* sv_ends_with Tests */

void sv_ends_with_passingString(void) {
  const char *cstr = "name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_ends_with(actual, "surname");
  TEST_ASSERT_TRUE(ret);
}

void sv_ends_with_passingString2(void) {
  const char *cstr = "name__surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_ends_with(actual, "surname");
  TEST_ASSERT_TRUE(ret);
}

void sv_ends_with_passingString3(void) {
  const char *cstr = "name_name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_ends_with(actual, "surname");
  TEST_ASSERT_TRUE(ret);
}

void sv_ends_with_passingString4(void) {
  const char *cstr = "_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_ends_with(actual, "surname");
  TEST_ASSERT_TRUE(ret);
}

void sv_ends_with_passingString5(void) {
  const char *cstr = "surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_ends_with(actual, "surname");
  TEST_ASSERT_TRUE(ret);
}

void sv_ends_with_passingStringWithUnmatchingSuffix(void) {
  const char *cstr = "name_name_surnome";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_ends_with(actual, "surname");
  TEST_ASSERT_FALSE(ret);
}

void sv_ends_with_passingEmptrySv(void) {
  const char *cstr = "";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  bool ret = sv_ends_with(actual, "surname");
  TEST_ASSERT_FALSE(ret);
}

/* sv_contains tests */

void sv_contains_svContainsCstr(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  const char *needle = "fox";
  sv haystack = sv_from_cstr(cstr);
  bool ret = sv_contains(haystack, needle);
  TEST_ASSERT_TRUE_MESSAGE(
      ret, "bool ret = sv_contains(haystack, needle) should return true");
}

void sv_contains_svContainsCstr2(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  const char *needle = "dog";
  sv haystack = sv_from_cstr(cstr);
  bool ret = sv_contains(haystack, needle);
  TEST_ASSERT_TRUE_MESSAGE(
      ret, "bool ret = sv_contains(haystack, needle) should return true");
}

void sv_contains_svContainsCstr3(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  const char *needle = ".";
  sv haystack = sv_from_cstr(cstr);
  bool ret = sv_contains(haystack, needle);
  TEST_ASSERT_TRUE_MESSAGE(
      ret, "bool ret = sv_contains(haystack, needle) should return true");
}

void sv_contains_svAndCstrAreEqual(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  const char *needle = "The quick brown fox jumps over the lazy dog.";
  sv haystack = sv_from_cstr(cstr);
  bool ret = sv_contains(haystack, needle);
  TEST_ASSERT_TRUE_MESSAGE(
      ret, "bool ret = sv_contains(haystack, needle) should return true");
}

void sv_contains_svDoesNotContainsCstr(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  const char *needle = "Turtle";
  sv haystack = sv_from_cstr(cstr);
  bool ret = sv_contains(haystack, needle);
  TEST_ASSERT_FALSE_MESSAGE(
      ret, "bool ret = sv_contains(haystack, needle) should return false");
}

void sv_contains_svDoesNotContainsCstr2(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  const char *needle = "  ";
  sv haystack = sv_from_cstr(cstr);
  bool ret = sv_contains(haystack, needle);
  TEST_ASSERT_FALSE_MESSAGE(
      ret, "bool ret = sv_contains(haystack, needle) should return false");
}

void sv_contains_emptySv(void) {
  const char *cstr = "";
  const char *needle = "brown fox";
  sv haystack = sv_from_cstr(cstr);
  bool ret = sv_contains(haystack, needle);
  TEST_ASSERT_FALSE_MESSAGE(
      ret, "bool ret = sv_contains(haystack, needle) should return false");
}

void sv_contains_passingNULLasCstr(void) {
  const char *cstr = "Hello World!";
  const char *needle = NULL;
  sv haystack = sv_from_cstr(cstr);
  bool ret = sv_contains(haystack, needle);
  TEST_ASSERT_FALSE_MESSAGE(
      ret, "bool ret = sv_contains(haystack, needle) should return false");
}

/* sv_trim_left tests */

void sv_trim_left_passingString(void) {
  const char *cstr = "    name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_left(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

void sv_trim_left_passingString2(void) {
  const char *cstr = "\tname_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_left(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

void sv_trim_left_passingString3(void) {
  const char *cstr = "\nname_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_left(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

void sv_trim_left_passingString4(void) {
  const char *cstr =
      "             The quick brown fox jumps over the lazy dog. ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_left(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("The quick brown fox jumps over the lazy dog. ",
                               trimmed.data, trimmed.count);
}

void sv_trim_left_passingEmptySv(void) {
  const char *cstr = "";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_left(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_left_passingSvMadeOfSpaces(void) {
  const char *cstr = "    ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_left(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_left_passingSvMadeOfSpaces2(void) {
  const char *cstr = "\n    ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_left(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_left_passingSvMadeOfSpaces3(void) {
  const char *cstr = "\t    ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_left(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_left_passingStringWithNoLeadingSpaces(void) {
  const char *cstr = "name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_left(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

/* sv_trim_right tests */

void sv_trim_right_passingString(void) {
  const char *cstr = "name_surname   ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_right(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

void sv_trim_right_passingString2(void) {
  const char *cstr = "name_surname\t";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_right(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

void sv_trim_right_passingString3(void) {
  const char *cstr = "name_surname\n";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_right(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

void sv_trim_right_passingStringWithNoLeadingSpaces(void) {
  const char *cstr = "name_surname";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_right(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

void sv_trim_right_passingEmptySv(void) {
  const char *cstr = "";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_right(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_right_passingSvMadeOfSpaces(void) {
  const char *cstr = "    ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_right(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_right_passingSvMadeOfSpaces2(void) {
  const char *cstr = "    \t";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_right(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_right_passingSvMadeOfSpaces3(void) {
  const char *cstr = "    \n";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim_right(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

/* sv_trim tests */

void sv_trim_passingSv(void) {
  const char *cstr = "    name_surname     ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

void sv_trim_passingSv2(void) {
  const char *cstr = "\nname_surname     ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

void sv_trim_passingSv3(void) {
  const char *cstr = "\tname_surname\n";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("name_surname", trimmed.data, trimmed.count);
}

void sv_trim_passingEmptySV(void) {
  const char *cstr = "";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_passingSvMadeOfSpaces(void) {
  const char *cstr = "    ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_passingSvMadeOfSpaces2(void) {
  const char *cstr = "\n    ";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_passingSvMadeOfSpaces3(void) {
  const char *cstr = "\n\t";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

void sv_trim_passingNULLTerminatedStringSv(void) {
  const char *cstr = "\0";
  sv actual = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), actual.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
  sv trimmed = sv_trim(actual);
  TEST_ASSERT_EQUAL_STRING_LEN("", trimmed.data, trimmed.count);
}

/* sv_split_by_space tests */

void sv_split_by_space_case1(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("The", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("quick", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("brown", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("fox", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("jumps", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("over", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("the", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("lazy", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("dog.", token.data, token.count);
}

void sv_split_by_space_case2(void) {
  const char *cstr = "   ";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("", token.data, token.count);
}

void sv_split_by_space_case3(void) {
  const char *cstr =
      "The quick          brown fox   jumps over    the lazy dog.";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("The", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("quick", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("brown", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("fox", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("jumps", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("over", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("the", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("lazy", token.data, token.count);
  token = sv_split_by_space(&string_view);
  TEST_ASSERT_EQUAL_STRING_LEN("dog.", token.data, token.count);
}

void sv_split_by_space_passingNULL(void) {
  sv token = sv_split_by_space(NULL);
  TEST_ASSERT_EQUAL_STRING_LEN("", token.data, token.count);
}

/* sv_split_by_space tests */

void sv_split_by_delim_case1(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_split_by_delim(&string_view, ' ');
  TEST_ASSERT_EQUAL_STRING_LEN("The", token.data, token.count);
  token = sv_split_by_delim(&string_view, ' ');
  TEST_ASSERT_EQUAL_STRING_LEN("quick", token.data, token.count);
  token = sv_split_by_delim(&string_view, ' ');
  TEST_ASSERT_EQUAL_STRING_LEN("brown", token.data, token.count);
  token = sv_split_by_delim(&string_view, ' ');
  TEST_ASSERT_EQUAL_STRING_LEN("fox", token.data, token.count);
  token = sv_split_by_delim(&string_view, ' ');
  TEST_ASSERT_EQUAL_STRING_LEN("jumps", token.data, token.count);
  token = sv_split_by_delim(&string_view, ' ');
  TEST_ASSERT_EQUAL_STRING_LEN("over", token.data, token.count);
  token = sv_split_by_delim(&string_view, ' ');
  TEST_ASSERT_EQUAL_STRING_LEN("the", token.data, token.count);
  token = sv_split_by_delim(&string_view, ' ');
  TEST_ASSERT_EQUAL_STRING_LEN("lazy", token.data, token.count);
  token = sv_split_by_delim(&string_view, ' ');
  TEST_ASSERT_EQUAL_STRING_LEN("dog.", token.data, token.count);
}

void sv_split_by_delim_case2(void) {
  const char *cstr = "The,quick,brown,fox,jumps,over,the,lazy,dog";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_split_by_delim(&string_view, ',');
  TEST_ASSERT_EQUAL_STRING_LEN("The", token.data, token.count);
  token = sv_split_by_delim(&string_view, ',');
  TEST_ASSERT_EQUAL_STRING_LEN("quick", token.data, token.count);
  token = sv_split_by_delim(&string_view, ',');
  TEST_ASSERT_EQUAL_STRING_LEN("brown", token.data, token.count);
  token = sv_split_by_delim(&string_view, ',');
  TEST_ASSERT_EQUAL_STRING_LEN("fox", token.data, token.count);
  token = sv_split_by_delim(&string_view, ',');
  TEST_ASSERT_EQUAL_STRING_LEN("jumps", token.data, token.count);
  token = sv_split_by_delim(&string_view, ',');
  TEST_ASSERT_EQUAL_STRING_LEN("over", token.data, token.count);
  token = sv_split_by_delim(&string_view, ',');
  TEST_ASSERT_EQUAL_STRING_LEN("the", token.data, token.count);
  token = sv_split_by_delim(&string_view, ',');
  TEST_ASSERT_EQUAL_STRING_LEN("lazy", token.data, token.count);
  token = sv_split_by_delim(&string_view, ',');
  TEST_ASSERT_EQUAL_STRING_LEN("dog.", token.data, token.count);
}

void sv_split_by_delim_case3(void) {
  const char *cstr = "The/quick/brown/fox/jumps/over/the/lazy/dog";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("The", token.data, token.count);
  token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("quick", token.data, token.count);
  token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("brown", token.data, token.count);
  token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("fox", token.data, token.count);
  token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("jumps", token.data, token.count);
  token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("over", token.data, token.count);
  token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("the", token.data, token.count);
  token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("lazy", token.data, token.count);
  token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("dog.", token.data, token.count);
}

void sv_split_by_delim_passingNULLPointer(void) {
  sv token = sv_split_by_delim(NULL, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("", token.data, token.count);
}

void sv_split_by_delim_passingEmptySv(void) {
  sv string_view = sv_from_cstr("");
  sv token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("", token.data, token.count);
}

void sv_split_by_delim_passingEmptyNULLTerminatedStringSv(void) {
  sv string_view = sv_from_cstr("\0");
  sv token = sv_split_by_delim(&string_view, '/');
  TEST_ASSERT_EQUAL_STRING_LEN("", token.data, token.count);
}

void sv_split_by_delim_delimNotInString(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_split_by_delim(&string_view, ',');
  TEST_ASSERT_EQUAL_STRING_LEN("The quick brown fox jumps over the lazy dog.",
                               token.data, token.count);
}

/* sv_skip_n_chars tests */

void sv_skip_n_chars_normalCase(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_skip_n_chars(string_view, 3);
  TEST_ASSERT_EQUAL_STRING_LEN(" quick brown fox jumps over the lazy dog.",
                               token.data, token.count);
}

void sv_skip_n_chars_skippingEntireString(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_skip_n_chars(string_view, string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN("",
                               token.data, 
                               token.count);
}

void sv_skip_n_chars_skippingUpToLastChar(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_skip_n_chars(string_view, string_view.count - 1);
  TEST_ASSERT_EQUAL_STRING_LEN(".",
                               token.data, 
                               token.count);
}

void sv_skip_n_chars_passingEmptySV(void) {
  const char *cstr = "";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_skip_n_chars(string_view, 0);
  TEST_ASSERT_EQUAL_STRING_LEN("",
                               token.data, token.count);
}

void sv_skip_n_chars_passingNGreaterThanSvCount(void) {
  const char *cstr = "The quick brown fox jumps over the lazy dog.";
  sv string_view = sv_from_cstr(cstr);
  TEST_ASSERT_EQUAL_size_t(strlen(cstr), string_view.count);
  TEST_ASSERT_EQUAL_STRING_LEN(cstr, string_view.data, strlen(cstr));
  sv token = sv_skip_n_chars(string_view, string_view.count + 10);
  TEST_ASSERT_EQUAL_STRING_LEN(".",
                               token.data, 
                               token.count);
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(sv_from_cstr_passingString);
  RUN_TEST(sv_from_cstr_passingEmptyString);
  RUN_TEST(sv_from_cstr_passingStringWithLeadingSpaces);
  RUN_TEST(sv_from_cstr_passingLongString1);
  RUN_TEST(sv_from_cstr_passingLongString2);
  RUN_TEST(sv_equal_passingIdenticalSvs);
  RUN_TEST(sv_equal_passingDifferentSvs);
  RUN_TEST(sv_equal_passingDifferentSvsInSize);
  RUN_TEST(sv_equal_passingOneEmptySV);
  RUN_TEST(sv_equal_passingTwoEmptySvs);
  RUN_TEST(sv_equal_cstr_passingSameString);
  RUN_TEST(sv_equal_cstr_passingDifferentString);
  RUN_TEST(sv_equal_cstr_passingNULLAsCstr);
  RUN_TEST(sv_equal_cstr_passingEmptyStringInBothSvAndCstr);
  RUN_TEST(sv_equal_cstr_passingSameEscapeSequence);
  RUN_TEST(sv_at_passingString);
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
  RUN_TEST(sv_remove_suffix_passingStringWithUnmatchingSuffix);
  RUN_TEST(sv_remove_suffix_passingStringWithUnmatchingSuffix2);
  RUN_TEST(sv_remove_suffix_passingEmptrySv);
  RUN_TEST(sv_remove_suffixprefix_combined);
  RUN_TEST(sv_starts_with_passingString);
  RUN_TEST(sv_starts_with_passingString2);
  RUN_TEST(sv_starts_with_passingString3);
  RUN_TEST(sv_starts_with_passingStringWithUnmatchingPrefix);
  RUN_TEST(sv_starts_with_passingStringWithUnmatchingPrefix2);
  RUN_TEST(sv_starts_with_passingEmptrySv);
  RUN_TEST(sv_ends_with_passingString);
  RUN_TEST(sv_ends_with_passingString2);
  RUN_TEST(sv_ends_with_passingString3);
  RUN_TEST(sv_ends_with_passingString4);
  RUN_TEST(sv_ends_with_passingString5);
  RUN_TEST(sv_ends_with_passingStringWithUnmatchingSuffix);
  RUN_TEST(sv_ends_with_passingEmptrySv);
  RUN_TEST(sv_contains_svContainsCstr);
  RUN_TEST(sv_contains_svContainsCstr2);
  RUN_TEST(sv_contains_svContainsCstr3);
  RUN_TEST(sv_contains_svAndCstrAreEqual);
  RUN_TEST(sv_contains_svDoesNotContainsCstr);
  RUN_TEST(sv_contains_svDoesNotContainsCstr2);
  RUN_TEST(sv_contains_emptySv);
  RUN_TEST(sv_contains_passingNULLasCstr);
  RUN_TEST(sv_trim_left_passingString);
  RUN_TEST(sv_trim_left_passingStringWithNoLeadingSpaces);
  RUN_TEST(sv_trim_left_passingString2);
  RUN_TEST(sv_trim_left_passingString3);
  RUN_TEST(sv_trim_left_passingString4);
  RUN_TEST(sv_trim_left_passingEmptySv);
  RUN_TEST(sv_trim_left_passingSvMadeOfSpaces);
  RUN_TEST(sv_trim_left_passingSvMadeOfSpaces2);
  RUN_TEST(sv_trim_left_passingSvMadeOfSpaces3);
  RUN_TEST(sv_trim_right_passingString);
  RUN_TEST(sv_trim_right_passingString2);
  RUN_TEST(sv_trim_right_passingString3);
  RUN_TEST(sv_trim_right_passingStringWithNoLeadingSpaces);
  RUN_TEST(sv_trim_right_passingEmptySv);
  RUN_TEST(sv_trim_right_passingSvMadeOfSpaces);
  RUN_TEST(sv_trim_right_passingSvMadeOfSpaces2);
  RUN_TEST(sv_trim_right_passingSvMadeOfSpaces3);
  RUN_TEST(sv_trim_passingSv);
  RUN_TEST(sv_trim_passingSv2);
  RUN_TEST(sv_trim_passingSv3);
  RUN_TEST(sv_trim_passingEmptySV);
  RUN_TEST(sv_trim_passingSvMadeOfSpaces);
  RUN_TEST(sv_trim_passingSvMadeOfSpaces2);
  RUN_TEST(sv_trim_passingSvMadeOfSpaces3);
  RUN_TEST(sv_trim_passingNULLTerminatedStringSv);
  RUN_TEST(sv_split_by_space_case1);
  RUN_TEST(sv_split_by_space_case2);
  RUN_TEST(sv_split_by_space_case3);
  RUN_TEST(sv_split_by_space_passingNULL);
  RUN_TEST(sv_split_by_delim_case1);
  RUN_TEST(sv_split_by_delim_case2);
  RUN_TEST(sv_split_by_delim_case3);
  RUN_TEST(sv_split_by_delim_passingNULLPointer);
  RUN_TEST(sv_split_by_delim_passingEmptySv);
  RUN_TEST(sv_split_by_delim_passingEmptyNULLTerminatedStringSv);
  RUN_TEST(sv_split_by_delim_delimNotInString);
  RUN_TEST(sv_skip_n_chars_normalCase);
  RUN_TEST(sv_skip_n_chars_skippingEntireString);
  RUN_TEST(sv_skip_n_chars_skippingUpToLastChar);
  RUN_TEST(sv_skip_n_chars_passingEmptySV);
  RUN_TEST(sv_skip_n_chars_passingNGreaterThanSvCount);
  UNITY_END();
  return 0;
}
