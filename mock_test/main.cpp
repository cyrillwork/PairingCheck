#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../rsinterface.h"
#include "../paramsrs.h"

using namespace std;

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::InSequence;

class MockRSInterface: public RSInterface
        //IInterface
{
public:

    MockRSInterface(TypeParams _params, PtrSerial _serial):
        RSInterface(_params, _serial) {}

    virtual ~MockRSInterface(){}

    MOCK_METHOD0(name, const std::string(void));
    MOCK_METHOD0(open, bool (void));
    MOCK_METHOD0(close, bool (void));
    MOCK_METHOD2(write, int (const char *data, int size));
    MOCK_METHOD3(read, int (char *data, int size, int timeout));
};

class TestRsInterface: public ::testing::Test
{
protected:

    std::shared_ptr<MockRSInterface> moskRs = nullptr;
    std::shared_ptr<RSInterface> rs = nullptr;

    virtual void SetUp() override
    {       
        auto param = std::make_shared<ParamsRS232>("/dev/ttyS0", Parity::None, B9600, ByteSize::_CS8);
        auto serial = getSerial();


        rs = std::make_shared<RSInterface>(param, serial);

        moskRs = std::make_shared<MockRSInterface>(param, serial);

    }

    virtual void TearDown() override
    {

    }

};

TEST_F(TestRsInterface, defaultSettings)
{
    ASSERT_EQ(rs->name(), "RS");
    ASSERT_EQ(rs->getDevName(), "/dev/ttyS0");
}

TEST_F(TestRsInterface, read)
{
    EXPECT_CALL(*moskRs, open())
                .Times(AtLeast(1));

    moskRs->open();
}



int main(int argc, char *argv[])
{
    cout << "Mock test for Pairing RS" << endl;

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

