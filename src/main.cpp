/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2023-02-09 18:53:27
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2023-02-17 23:10:11
 * @Description:
 */
#include <array>
#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <utility>
#include <vector>
#include <functional>
#include <future>

// #include <gtest/gtest.h>

// TEST(HelloTest, BasicAssertions) {
//     EXPECT_STRNE("hello", "world");
//     EXPECT_EQ(7 * 6, 42);
// }

void f(int &n1, int& n2)
{
    n1++;
    n2++;
}
int main()
{
    int n1 = 1, n2 = 2;
    auto bound1 = std::bind(&f, n1, std::ref(n2));
    bound1();    // 1 3
    std::cout << n1  << n2 << std::endl;
    auto bound2 = std::bind(&f, std::placeholders::_1, std::ref(n2)); // 2 4
    bound2(n1);
    std::cout << n1  << n2 << std::endl;
}

// int main() {
//     std::packaged_task<int()> task([]() { return 7; });
//     std::future<int> result = task.get_future();
//     std::thread(std::move(task)).detach();
//     std::cout << "waiting...";
//     result.wait();
//     std::cout << "done!" << std::endl
//               << "future result is " << result.get() << std::endl;
// }