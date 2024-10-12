#pragma once

#include <coroutine>

#include <future>

template <typename T>
class StdFutureCoroPromise
{
public:
    std::promise<T> m_promise;

    auto getReturnObject()
    {
        return m_promise.get_future();
    }

    std::suspend_never initial_suspend() noexcept
    {
        return {};
    }

    std::suspend_never final_suspend() noexcept
    {
        return {};
    }

    void set_exception(std::exception& ex)
    {
        m_promise.set_exception(std::move(ex));
    }

    void unhandled_exception()
    {
        m_promise.set_exception(std::current_exception());
    }

    template<typename U>
    void return_value(U&& u)
    {
        m_promise.set_value(Ok(std::forward<U>(u)));
    }
};

template<typename R, typename... Args>
class std::coroutine_traits<std::future<R>, Args...>
{
public:
    using promise_type = StdFutureCoroPromise<R>;
};

/////////////////////////////////////////////////////////

template <>
class StdFutureCoroPromise<void>
{
public:
    std::promise<void> promise_;

    auto get_return_object() {
        return promise_.get_future();
    }

    std::suspend_never initial_suspend() noexcept {
        return {};
    }

    std::suspend_never final_suspend() noexcept {
        return {};
    }

    void set_exception(const std::exception_ptr& e) {
        promise_.set_exception(std::move(e));
    }

    void unhandled_exception() {
        promise_.set_exception(std::current_exception());
    }

    void return_void() {
        promise_.set_value();
    }
};

template <typename... Args>
class std::coroutine_traits<std::future<void>, Args...>
{
public:
    using promise_type = StdFutureCoroPromise<void>;
};