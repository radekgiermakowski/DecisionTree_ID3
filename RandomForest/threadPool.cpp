#include "threadPool.h"

ThreadPool::ThreadPool(size_t size):work_(new boost::asio::io_service::work(ioService_))
{
    if(size > DEFAULT_POOL_SIZE)
        size = DEFAULT_POOL_SIZE;

    for(size_t i=0; i<size;++i)
    {
        workers_.create_thread(boost::bind(&boost::asio::io_service::run, &ioService_));
    }
}

ThreadPool::~ThreadPool()
{
    workers_.interrupt_all();
    shutdown_();
    workers_.join_all();
}


void ThreadPool::shutdown_()
{
    ioService_.reset();
    ioService_.stop();
}


