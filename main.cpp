#include "gmock/gmock.h"

using namespace std;

int main(int ac, char**av)
{
    testing::InitGoogleMock(&ac,av);
    return RUN_ALL_TESTS();
}
