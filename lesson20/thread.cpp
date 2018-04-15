#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <mutex>
#include <future>

std::mutex cout_mutex;
std::mutex cerr_mutex;

using dict_t = std::map<std::string, std::string>;

std::string foo(dict_t &)
{
    std::thread::id this_id = std::this_thread::get_id();

    cout_mutex.lock();
    std::cout << "foo " << this_id << std::endl;
    cout_mutex.unlock();

    cerr_mutex.lock();
    std::cerr << "foo " << this_id << std::endl;
    cerr_mutex.unlock();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    return std::string{"ok"};
}

int main()
{
    dict_t d;
    std::thread t1(foo, std::ref(d));
    std::thread t2(foo, std::ref(d));

    t1.join();
    t2.join();

    auto r1 = std::async(std::launch::async,
        foo, std::ref(d));
    std::cout << r1.get() << std::endl;

    auto r2 = std::async(std::launch::deferred,
        foo, std::ref(d));
    std::cout << r2.get() << std::endl;
}
