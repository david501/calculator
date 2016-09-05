#include "gmock/gmock.h"
#include <sstream>
#include "calcuator.h"
#include "CalcN.h"

#define UNIT_TEST

using namespace std;

int main(int ac, char**av)
{
#ifdef UNIT_TEST
    testing::InitGoogleMock(&ac,av);
    return RUN_ALL_TESTS();
#else
    CalcN c;
    c();
#endif
}
