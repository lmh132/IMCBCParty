//thread-safe queue
#pragma once
#include "net_common.h"

template<typename T>
class tsqueue {
public:
    tsqueue() = default;
    tsqueue(const tsqueue<T>&) = delete;

    virtual ~tsqueue() { clear(); }

    const T& front() {
        std::scoped_lock lock(muxQueue);
        return deqQueue.front();
    }

    const T& back() {
        std::scoped_lock lock(muxQueue);
        return deqQueue.back();
    }

    void push_front(T item) {
        std::scoped_lock lock(muxQueue);
        deqQueue.emplace_front(std::move(item));
    }

    void push_back(T item) {
        std::scoped_lock lock(muxQueue);
        deqQueue.emplace_back(std::move(item));
    }

    size_t count() {
        std::scoped_lock lock(muxQueue);
        return deqQueue.size();
    }

    bool empty() {
        std::scoped_lock lock(muxQueue);
        return deqQueue.empty();
    }

    void clear() {
        std::scoped_lock lock(muxQueue);
        deqQueue.clear();
    }

    T& popfront() {
        std::scoped_lock lock(muxQueue);
        auto t = std::move(deqQueue.front());
        deqQueue.pop_front();
        return t;
    }

    T& popback() {
        std::scoped_lock lock(muxQueue);
        auto t = std::move(deqQueue.back());
        deqQueue.pop_back();
        return t;
    }

protected:
    std::mutex muxQueue;
    stf::deque<T> deqQueue;

};