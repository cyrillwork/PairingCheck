#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../rs_interface.h"

using namespace std;

using ::testing::AtLeast;
using ::testing::_;

class MockRSInterface: public AbstractInterface
{
public:
    MOCK_METHOD0(name, const std::string(void));
    MOCK_METHOD0(open, bool (void));
    MOCK_METHOD0(close, bool (void));
    MOCK_METHOD2(write, int (const char *data, int size));
    MOCK_METHOD3(read, int (char *data, int size, int timeout));
};

TEST(RsInterface, name)
{
    ParamsRS pr;
    RSInterface rs = {pr};

    ASSERT_EQ(rs.name(), "RS");
}

int main(int argc, char *argv[])
{
    cout << "Mock test for Pairing RS" << endl;

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

