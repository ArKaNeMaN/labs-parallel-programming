//
// Created by arkan on 16.03.2022.
//

#ifndef CPP_FINDMAXGRAPHPART_SHAREDQUEUE_H
#define CPP_FINDMAXGRAPHPART_SHAREDQUEUE_H


#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class SharedQueue {
public:
    void push(T);

    bool try_pop(T&, std::chrono::milliseconds);

    T pop();

    size_t size();

private:
    std::queue<T> q;
    std::mutex qMutex;
    std::condition_variable populatedNotifier;
};

template<typename T>
void SharedQueue<T>::push(T val) {
    {
        std::lock_guard<std::mutex> lock(qMutex);

        q.push(std::move(val));
    }

    populatedNotifier.notify_one();
}

template<typename T>
bool SharedQueue<T>::try_pop(T &val, std::chrono::milliseconds timeout) {
    std::unique_lock<std::mutex> lock(qMutex);

    if (!populatedNotifier.wait_for(lock, timeout, [this] { return !q.empty(); })) {
        return false;
    }

    val = std::move(q.front());
    q.pop();

    return true;
}

template<typename T>
T SharedQueue<T>::pop() {
    T val = q.front();
    q.pop();
    return val;
}

template<typename T>
size_t SharedQueue<T>::size() {
    return q.size();
}

#endif //CPP_FINDMAXGRAPHPART_SHAREDQUEUE_H
