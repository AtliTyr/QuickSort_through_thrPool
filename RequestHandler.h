#pragma once
#include "ThreadPool.h"

class RequestHandler {
public:
    RequestHandler();
    ~RequestHandler();
    // �������� ������� �� ����������
    std::future<void> pushRequest(Func f, int* arr, long l, long r, bool make_thread);
private:
    // ��� �������
    ThreadPool m_tpool;
};