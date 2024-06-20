#include "RequestHandler.h"

RequestHandler::RequestHandler() {
    m_tpool.start();
}
RequestHandler::~RequestHandler() {
    m_tpool.stop();
}
std::future<void> RequestHandler::pushRequest(Func f, int* arr, long l, long r, bool make_thread) {
    return m_tpool.push_task(f, arr, l, r, make_thread);
}