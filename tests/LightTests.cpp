#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "Light.h"

TEST(LightTests, MemberVariablesTest)
{
    {
        Point pos{0,0,0};
        Color col{1,1,1};
        Light light{pos,col};
        EXPECT_EQ(light.position, pos);
        EXPECT_EQ(light.intensity, col);
    }
}
