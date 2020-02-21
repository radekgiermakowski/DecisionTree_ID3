#ifndef FOREST_THREADPOOL_H
#define FOREST_THREADPOOL_H

#include <iostream>
#include <thread>
#include <future>
#include <utility>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

/**
 * Klasa ThreadPool
 * Odpowiada za generowanie puli wątków
 */
class ThreadPool
{
public:
    /**
     * Konstruktor klasy ThreadPool
     * @param size liczba wygenerowanych wątków, maksymalnie 8
     */
    explicit ThreadPool(size_t size);
    /**
     * Destruktor klasy ThreadPool
     * Kończy działanie uruchomionych wątków
     */
    ~ThreadPool();

    /**
     * Funkcja odpowiedzialna za przydział zadań wykonywanych przez wątki
     * @tparam F Typ zadania przekazywanego do wątku
     */
    template<class F>
    void enqueue(F f){
        ioService_.post(f);
    }

private:
    /**
     * Funkcja resetująca kolejkę zadań dla wątków
     */
    void shutdown_();


private:
    boost::thread_group workers_;
    boost::asio::io_service ioService_;
    boost::asio::io_service::work *work_;
    static const int DEFAULT_POOL_SIZE = 8;
};


#endif //FOREST_THREADPOOL_H
