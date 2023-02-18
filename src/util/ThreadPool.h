/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2023-02-17 19:11:20
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2023-02-17 22:59:34
 * @Description:
 */
#pragma once

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

// reference: https://www.zhihu.com/question/27908489/answer/355105668
class ThreadPool {
public:
    explicit ThreadPool(int thread_num = 8) :
        data_(std::make_unique<Data>()) {
        for (int i = 0; i < thread_num; ++i) {
            std::thread([&]() {
                std::unique_lock<std::mutex> lock(data_->mtx_);
                while (true) {
                    if (!data_->tasks_.empty()) {
                        auto task = data_->tasks_.front();
                        data_->tasks_.pop();
                        lock.unlock();
                        task();
                        lock.lock();
                    } else if (data_->is_closed_) {
                        break;
                    } else {
                        data_->cond_.wait(lock);
                    }
                }
            }).detach();
        }
    }

    ThreadPool() = default;

    ThreadPool(ThreadPool &&) = default;

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(data_->mtx_);
            data_->is_closed_ = true;
        }
        data_->cond_.notify_all();
    }

    template <typename F>
    void addTask(F &&task) {
        {
            std::unique_lock<std::mutex> lock(data_->mtx_);
            data_->tasks_.emplace(std::forward<F>(task));
        }
        data_->cond_.notify_one();
    }

private:
    class Data {
    public:
        Data() :
            is_closed_(false) {
        }
        std::mutex mtx_;
        std::condition_variable cond_;
        std::queue<std::function<void()>> tasks_;
        bool is_closed_;
    };
    std::unique_ptr<Data> data_;
};