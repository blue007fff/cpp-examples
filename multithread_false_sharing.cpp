#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

// #define myalign alignas(64)
#define myalign // false sharing
myalign double mt_num1 = 0;
myalign double mt_num2 = 0;
myalign double mt_num3 = 0;
myalign double mt_num4 = 0;
double st_num = 0;
constexpr int default_iteration_count = 100000000;
constexpr double default_sum_value = 0.001;

void mt_fun1(int64_t n)
{
    for (int64_t i = 0; i < n; i++)
        mt_num1 += default_sum_value;
}

void mt_fun2(int64_t n)
{
    for (int64_t i = 0; i < n; i++)
        mt_num2 += default_sum_value;
}

void mt_fun3(int64_t n)
{
    for (int64_t i = 0; i < n; i++)
        mt_num3 += default_sum_value;
}

void mt_fun4(int64_t n)
{
    for (int64_t i = 0; i < n; i++)
        mt_num4 += default_sum_value;
}

void st_fun(int64_t n)
{
    for (int64_t i = 0; i < n; i++)
    {
        st_num += default_sum_value;
    }
}

int main()
{
    std::cout << "cache-line: " << std::hardware_constructive_interference_size << std::endl;
    std::cout << "mt_num1: " << &mt_num1 << std::endl;
    std::cout << "mt_num2: " << &mt_num2 << std::endl;
    std::cout << "mt_num3: " << &mt_num3 << std::endl;
    std::cout << "mt_num4: " << &mt_num4 << std::endl;
    std::cout << "st_num: " << &st_num << std::endl;

    int n = default_iteration_count;
    std::cout << "iter: ";
    std::cout << n << std::endl;
    // std::cin >> n;

    auto beginTime = std::chrono::high_resolution_clock::now();
    {
        std::thread t1(mt_fun1, n / 4); // Multi Thread 실행
        std::thread t2(mt_fun2, n / 4); // Multi Thread 실행
        std::thread t3(mt_fun3, n / 4); // Multi Thread 실행
        std::thread t4(mt_fun4, n / 4); // Multi Thread 실행
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> resultTime = endTime - beginTime;
    std::cout << "mt: " << resultTime.count() << " : "
              << mt_num1 + mt_num2 + mt_num3 + mt_num4 << std::endl;

    beginTime = std::chrono::high_resolution_clock::now();
    {
        st_fun(n); // Single Thread 실행
    }
    endTime = std::chrono::high_resolution_clock::now();
    resultTime = endTime - beginTime;
    std::cout << "st: " << resultTime.count() << " : "
              << st_num << std::endl;
}