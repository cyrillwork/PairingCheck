#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../rsinterface.h"
#include "../paramsrs.h"

using namespace std;

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::InSequence;

//class MockRSInterface: public RSInterface
//{
//public:
//    MockRSInterface(TypeParams _params, PtrSerial _serial):
//        RSInterface(_params, _serial) {}

//    virtual ~MockRSInterface(){}

//    MOCK_METHOD0(name, const std::string(void));
//    MOCK_METHOD0(open, bool (void));
//    MOCK_METHOD0(close, bool (void));
//    MOCK_METHOD2(write, int (const char *data, int size));
//    MOCK_METHOD3(read, int (char *data, int size, int timeout));
//};

class MockSerial: public LinuxSerial
{
public:

    virtual ~MockSerial() {}

    MOCK_METHOD2(open, int (const char*, int));
    MOCK_METHOD0(close, int(void));
    MOCK_METHOD2(write, size_t(const char*, size_t));
    MOCK_METHOD2(read, size_t(char *, size_t size));
    MOCK_METHOD1(select, int (size_t));
};


class TestRsInterface: public ::testing::Test
{
protected:

    std::shared_ptr<RSInterface>        realRs = nullptr;
    std::shared_ptr<MockSerial>         moskSerial = nullptr;

    virtual void SetUp() override
    {       
        moskSerial  = std::make_shared<MockSerial>();
        realRs      = std::make_shared<RSInterface>(std::make_shared<ParamsRS232>(), moskSerial);
    }

    virtual void TearDown() override
    {
    }

};

TEST_F(TestRsInterface, defaultSettings)
{
    ASSERT_EQ(realRs->name(), "RS");
    ASSERT_EQ(realRs->getDevName(), "/dev/ttyS0");
}

TEST_F(TestRsInterface, read)
{
    int     timeout = 1;
    char    buff[32];
    int     size = 10;

    EXPECT_CALL(*moskSerial, select(timeout))
        .Times(AtLeast(1));

    realRs->read(buff, size, timeout);
}

TEST_F(TestRsInterface, write)
{
    char    buff[32];
    int     size = 10;

    EXPECT_CALL(*moskSerial, write(buff, size))
        .Times(AtLeast(1));

    realRs->write(buff, size);
}



int main(int argc, char *argv[])
{
    cout << "Mock test for Pairing RS" << endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

