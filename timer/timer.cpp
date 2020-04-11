#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>

/* NOTE: Does not work with array types. */
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

enum timer_state_t
{
    STATE_INIT = 0,
    STATE_RUNNING,
    STATE_COMPLETE
};

class timer
{
    using time_stamp = std::chrono::steady_clock::time_point;

    timer_state_t                m_state = STATE_INIT;
    int                          m_duration = 0;
    time_stamp                   m_start_time = std::chrono::steady_clock::now();
    std::unique_ptr<std::thread> m_thread{};
    bool                         m_quit = false; /* Protected by lock. */
    std::condition_variable      m_condvar;
    std::mutex                   m_mtx;

    public:
        timer(int d);
        ~timer(void);
        void start(void);
        void stop(void);
        int elapsed(void);
        int remaining(void);
        void timer_thread_func(void);
        timer_state_t state(void);
};

timer::timer(int d) : m_duration(d)
{
    std::cout << "Created timer object with " << m_duration << "s duration"
              << std::endl;
}

timer::~timer(void)
{
    std::cout << "Destroying timer object with " << m_duration << "s duration"
              << std::endl;
    m_thread->join();
}

void timer::start(void)
{
    std::cout << "Starting timer..." << std::endl;
    m_thread = make_unique<std::thread>(&timer::timer_thread_func, this);
    std::unique_lock<std::mutex> lk{m_mtx};
    m_start_time = std::chrono::steady_clock::now();
    m_state = STATE_RUNNING;
}

void timer::stop(void)
{
    {
        /* Reduce scope of lock so that timer thread can proceed and join. */
        std::unique_lock<std::mutex> lk{m_mtx};
        m_quit = true;
        m_condvar.notify_one();
        auto curr = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(curr - m_start_time).count();
        std::cout << "Force stopped the timer after "<< elapsed << "s..."
                  << std::endl;
    }
    m_thread->join();
}

int timer::elapsed(void)
{
    auto curr = std::chrono::steady_clock::now();
    std::unique_lock<std::mutex> lk{m_mtx};

    return std::chrono::duration_cast<std::chrono::seconds>(curr - m_start_time).count();
}

int timer::remaining(void)
{
    std::unique_lock<std::mutex> lk{m_mtx};

    if (STATE_RUNNING == m_state) {
        auto curr = std::chrono::steady_clock::now();
        int elapsed = std::chrono::duration_cast<std::chrono::seconds>(curr - m_start_time).count();
        return (m_duration - elapsed);
    }
    
    return 0;
}

void timer::timer_thread_func(void)
{
    std::unique_lock<std::mutex> lk{m_mtx};
    auto timeout = std::chrono::steady_clock::now()
                   + std::chrono::seconds(m_duration);
    if (m_condvar.wait_until(lk, timeout,
                             [this]()->bool { return m_quit; })) {
        /* Timer force stopped. */
        std::cout<< "Timer force stopped" << std::endl;
    } else {
        /* Timeout reached. */
        std::cout << "Timeout " << std::chrono::seconds(m_duration).count()
                  << "s reached. Do some work." << std::endl;
    }
    m_quit  = false;
    m_state = STATE_COMPLETE;
}

timer_state_t timer::state(void)
{
    std::unique_lock<std::mutex> lk{m_mtx};
    return m_state;
}

int main(int argc, char *argv[])
{
    timer t1(10);

    std::cout << "FIRST RUN" << std::endl;
    t1.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "State           : " << t1.state() << std::endl;
    std::cout << "Time elapsed    : " << t1.elapsed() << std::endl;
    std::cout << "Time remaining  : " << t1.remaining() << std::endl;
    std::cout << "--------------------------" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "State           : " << t1.state() << std::endl;
    std::cout << "Time elapsed    : " << t1.elapsed() << std::endl;
    std::cout << "Time remaining  : " << t1.remaining() << std::endl;
    std::cout << "--------------------------" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "State           : " << t1.state() << std::endl;
    std::cout << "Time elapsed    : " << t1.elapsed() << std::endl;
    std::cout << "Time remaining  : " << t1.remaining() << std::endl;
    std::cout << "--------------------------" << std::endl;

    std::cout << "Force stop the timer!" << std::endl;
    t1.stop();

    std::cout << "SECOND RUN" << std::endl;
    t1.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "State           : " << t1.state() << std::endl;
    std::cout << "Time elapsed    : " << t1.elapsed() << std::endl;
    std::cout << "Time remaining  : " << t1.remaining() << std::endl;
    std::cout << "--------------------------" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "State           : " << t1.state() << std::endl;
    std::cout << "Time elapsed    : " << t1.elapsed() << std::endl;
    std::cout << "Time remaining  : " << t1.remaining() << std::endl;
    std::cout << "--------------------------" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "State           : " << t1.state() << std::endl;
    std::cout << "Time elapsed    : " << t1.elapsed() << std::endl;
    std::cout << "Time remaining  : " << t1.remaining() << std::endl;
    std::cout << "--------------------------" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "State           : " << t1.state() << std::endl;
    std::cout << "==========================" << std::endl;

    return 0;
}
