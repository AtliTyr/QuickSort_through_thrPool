#pragma once
#include <future>
#include <mutex>
#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <chrono>
#include <condition_variable>
#include <random>
#include <iomanip>

using namespace std;

typedef void (*Func) (int*, long, long, bool);
typedef function<void()> task_type;

template<class T>
class BlockedQueue {
public:
    void push(T& item) {
        lock_guard<mutex> l(m_locker);
        // ������� ���������������� push
        m_task_queue.push(item);
        // ������ ����������, ����� �����, ���������
        // pop ��������� � ������ ������� �� �������
        m_notifier.notify_one();
    }
    // ����������� ����� ��������� �������� �� �������
    void pop(T& item) {
        unique_lock<mutex> l(m_locker);
        if (m_task_queue.empty())
            // ����, ���� ������� push
            m_notifier.wait(l, [this] {return !m_task_queue.empty(); });
        item = m_task_queue.front();
        m_task_queue.pop();
    }
    // ������������� ����� ��������� �������� �� �������
    // ���������� false, ���� ������� �����
    bool fast_pop(T& item) {
        lock_guard<mutex> l(m_locker);
        if (m_task_queue.empty())
            // ������ �������
            return false;
        // �������� �������
        item = m_task_queue.front();
        m_task_queue.pop();
        return true;
    }
private:
    mutex m_locker;
    // ������� �����
    queue<T> m_task_queue;
    // �����������
    condition_variable m_notifier;
};

class ThreadPool {
public:
    ThreadPool();
    // ������:
    void start();
    // ���������:
    void stop();
    // ������� �����
    std::future<void> push_task(Func f, int* arr, long l, long r, bool make_thread);
    // ������� ����� ��� ������
    void threadFunc(int qindex);
private:
    // ���������� �������
    int m_thread_count;
    // ������
    vector<thread> m_threads;
    // ������� ����� ��� �������
    vector<BlockedQueue<task_type>> m_thread_queues;
    // ��� ������������ ������������� �����
    int m_index;
};