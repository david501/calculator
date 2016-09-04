#include "gmock/gmock.h"
#include "calcuator.h"
#include <sstream>

using namespace std;

int main(int ac, char**av)
{
    testing::InitGoogleMock(&ac,av);
    return RUN_ALL_TESTS();
//    ostringstream s;
//    calcuator c("(1+2)",s);
}
