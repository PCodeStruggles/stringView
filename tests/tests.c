#include <stdio.h>
#include <string.h>

#include "../unity/unity.h"
#define SV_IMPLEMENTATION
#include "../sv.h"

void setUp(void) {return;}
void tearDown(void) {return;}

/* sv_from_cstr Tests */

void sv_from_cstr_createSv(void)
{
    const char* cstr = "name";
    sv actual = sv_from_cstr(cstr);
    TEST_ASSERT_EQUAL_size_t(4, actual.count);
    TEST_ASSERT_EQUAL_STRING_LEN(cstr, actual.data, strlen(cstr));
}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(sv_from_cstr_createSv);
    UNITY_END();
    return 0;
}
