#include <gtest/gtest.h>
#include "tdoa.h" // 包含你的头文件

TEST(TdoaCalcTest, ValidInput) {
    const int num_bs = 5; // 基站数量
    tdoa_pos_t bs_vec[num_bs] = {
        {45.2, 35.6, 0.0},   // 基站1
        {150.8, 20.3, 5.0}, // 基站2
        {180.0, 10.0, 2.0}, // 基站3
        {220.5, 15.0, 180.0}, // 基站4
        {50.0, 90.5, 0.0}  // 基站5
    };

    tdoa_time_t time_vec[num_bs] = {
        0.0001651234, // 从基站1接收到的时间
        0.0003356789, // 从基站2接收到的时间
        0.0004001234, // 从基站3接收到的时间
        0.0005009876, // 从基站4接收到的时间
        0.0002004567  // 从基站5接收到的时间
    };

    tdoa_pos_t ms; // 结果位置

    int result = tdoa_calc_1(bs_vec, time_vec, num_bs, &ms);

    EXPECT_EQ(result, 0); // 期望返回值为0
    EXPECT_NEAR(ms.x, 115.0, 1.0); // 期望的x坐标
    EXPECT_NEAR(ms.y, 76.0, 1.0); // 期望的y坐标
    EXPECT_NEAR(ms.z, 91.0, 1.0);   // 期望的z坐标
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

