#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>

using namespace std::chrono_literals;

std::mutex m;

int print_value(int id, int& value)
{
    for(int i=0; i <20; i++)
    {
        {
            std::lock_guard<std::mutex> lock(m);
            std::cout << "Thread " << id << 
                    ": value="<< value << std::endl;
            std::this_thread::sleep_for(500ms);
            value++;
        }
    }
    return 0;
}

int main()
{
    static int gVal = 0;

    std::thread t1(print_value, 1, std::ref(gVal));
    std::thread t2(print_value, 2, std::ref(gVal));

    for(int i=0; i< 20; ++i)
    {
        std::this_thread::sleep_for(1s);
    }
    t1.join();
    t2.join();

    return 0;
}

