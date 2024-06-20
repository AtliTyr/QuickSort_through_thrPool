#pragma once
#include "ThreadPool.h"

class RequestHandler {
public:
    RequestHandler();
    ~RequestHandler();
    // отправка запроса на выполнение
    std::future<void> pushRequest(Func f, int* arr, long l, long r, bool make_thread);
private:
    // пул потоков
    ThreadPool m_tpool;
};