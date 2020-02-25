#include <gtest/gtest.h>

// Local function to test
static double myAdd(double x, double y){
    return x + y;
}

// Google test simple test
TEST(testmyAdd, simpleTest){
    EXPECT_EQ(2, myAdd(0, 2));
    EXPECT_EQ(0, myAdd(0, 0));
    EXPECT_EQ(5, myAdd(3, 2));
}

// Google test complex test
TEST(testmyAdd, complexTest){
    EXPECT_EQ(60, myAdd(50, 10));
    EXPECT_EQ(30, myAdd(10, 20));
    EXPECT_EQ(53, myAdd(30, 23));
}

int main(int argc, char* argv[]){
    std::cout << "Google test" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
