#include "ISoundex.hpp"
#include "SoundexClient.hpp"

#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class SoundexMock : public ISoundex
{
public:
    MOCK_METHOD(void, getDescription, (), (const, override));
    MOCK_METHOD(int, getVersionID, (), (const, override));
};

class SoundexTest: public ::testing::Test
{
protected:

};

TEST_F(SoundexTest, initialize)
{
    SoundexMock m_mock;
    SoundexClient m_client{&m_mock};
    EXPECT_CALL(m_mock, getDescription()).Times(1);

    m_client.getSoundexDescription();
}

TEST_F(SoundexTest, getVersion)
{
    SoundexMock m_mock;
    SoundexClient m_client{&m_mock};
    EXPECT_CALL(m_mock, getVersionID()).Times(4).WillRepeatedly(testing::Return(4));
    EXPECT_EQ(m_client.getVersionID(), 4);
}

TEST_F(SoundexTest, nullptrcheck)
{
    SoundexMock m_mock;
    SoundexClient m_client{nullptr};
    EXPECT_CALL(m_mock, getVersionID()).Times(0).WillRepeatedly(testing::Return(0));
    EXPECT_EQ(m_client.getVersionID(), 0);
}