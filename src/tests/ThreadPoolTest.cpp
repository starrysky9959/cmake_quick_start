/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2023-02-17 22:27:52
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2023-02-17 23:22:33
 * @Description:
 */
#include <chrono>
#include <functional>
#include <gtest/gtest.h>
#include <thread>
#include "util/ThreadPool.h"

TEST(ThreadPoolTest, test1) {
    ThreadPool pool(8);
    int x = 0;
    auto bind_foo = std::bind([](int &num) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        num += 1;
        std::cout << std::this_thread::get_id() << " is working" << std::endl;
    },
                            std::ref(x));
    for (int i = 0; i < 10; ++i) {
        pool.addTask(std::move(bind_foo));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << x << std::endl;
}