#include <thread>
#include <condition_variable>
#include <memory>
#include <iostream>
#include <chrono>
#include <vector>
#include <list>

using namespace std;

class IThreadPool {
public:
    virtual void enqueue(std::function<void()> func) = 0;
};

template<typename T>
class Future {
public:
    void set(T v) {
        vector<function<void(T)> > tmpContinuations;
        {
            unique_lock<mutex> lck(mtx);
            value = v;
            hasValue = true;
            cv.notify_all();
            swap(continuations, tmpContinuations);
        }
        for(function<void(T)>& cont : tmpContinuations) {
            cont(v);
        }
    }
    
    void wait() {
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, [this](){return this->hasValue;});
    }
    T get() {
        wait();
        return value;
    }
    
    template<typename V, typename Func>
    shared_ptr<Future<V> > continueWithNoThread(Func f) {
        shared_ptr<Future<V> > ret = make_shared<Future<V> > ();
        unique_lock<mutex> lck(mtx);
        if(hasValue) {
            ret-> set(f(value));
        } else {
            continuations.push_back([ret,f](T srcVal){
                ret->set(f(srcVal));
            });
        }
        return ret;
    }
    
    template<typename V, typename Func>
    shared_ptr<Future<V> > continueWith(Func f, IThreadPool* tp) {
        shared_ptr<Future<V> > ret = make_shared<Future<V> > ();
        unique_lock<mutex> lck(mtx);
        if(hasValue) {
            tp->enqueue([ret, f, this](){ret-> set(f(this->value));});
        } else {
            continuations.push_back([ret,f,tp](T srcVal){
                tp->enqueue([ret,f,srcVal](){ret->set(f(srcVal));});
            });
        }
        return ret;
    }
    
private:
    mutex mtx;
    condition_variable cv;
    bool hasValue;
    T value;
    vector<function<void(T)> > continuations;
};

template<typename R, typename Func, typename... Args>
shared_ptr<Future<R> > continueWhenAll(Func f, IThreadPool* tp, Future<Args>*... input)
{
    cout << f(input->get()...) << '\n';
}

class ThreadPool : public IThreadPool {
public:
    explicit ThreadPool(size_t nrThreads)
        :m_end(false),
        m_liveThreads(nrThreads)
    {
        m_threads.reserve(nrThreads);
        for(size_t i=0 ; i<nrThreads ; ++i) {
            m_threads.emplace_back([this](){this->run();});
        }
    }
    
    ~ThreadPool() {
        close();
        for(std::thread& t : m_threads) {
            t.join();
        }
    }
    
    void close() {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_end = true;
        m_cond.notify_all();
        while(m_liveThreads > 0) {
            m_condEnd.wait(lck);
        }
    }
    
    void enqueue(std::function<void()> func) {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_queue.push_back(std::move(func));
        m_cond.notify_one();
    }
    
//    template<typename Func, typename... Args>
//    void enqueue(Func func, Args&&... args) {
//        std::function<void()> f = [=](){func(args...);};
//        enqueue(std::move(f));
//    }
private:
    void run() {
        while(true) {
            std::function<void()> toExec;
            {
                std::unique_lock<std::mutex> lck(m_mutex);
                while(m_queue.empty() && !m_end) {
                    m_cond.wait(lck);
                }
                if(m_queue.empty()) {
                    --m_liveThreads;
                    if(0 == m_liveThreads) {
                        m_condEnd.notify_all();
                    }
                    return;
                }
                toExec = std::move(m_queue.front());
                m_queue.pop_front();
            }
            toExec();
        }
    }

    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::condition_variable m_condEnd;
    std::list<std::function<void()> > m_queue;
    bool m_end;
    size_t m_liveThreads;
    std::vector<std::thread> m_threads;
};


int main()
{
    shared_ptr<Future<int> > f1 = make_shared<Future<int> > ();
    
    ThreadPool tp(10);
    
    shared_ptr<Future<int> > f2 = f1->continueWith<int>([](int x){return x+1;}, &tp);
    
    tp.enqueue([f1](){f1->set(1);});
    
    //this_thread::sleep_for(chrono::milliseconds(1000));
    shared_ptr<Future<int> > f3 = continueWhenAll<int>([](int x, int y){return x+y;}, &tp, f1.get(), f2.get());
    cout << "Val=" << f2->get() << endl;
    try{
    cout << "ELL = " << f3->get() << '\n';
    }catch(const std::system_error& e) {
        cout << e.what() << '\n';
        cout << e.code() << '\n';
    }
    return 0;
}