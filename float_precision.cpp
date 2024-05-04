#include <iostream>
#include <cxxabi.h>
#include <iomanip> // setprecision

void test1()
{
    std::cout << __FUNCTION__ << std::endl;
}

template <typename T>
auto accum(T v, int count)
{
    T sum = 0;
    for (int i = 0; i < count; ++i)
        sum += v;
    return sum;
};

int main()
{
    float f00 = accum(0.01f, 1000);
    float f01 = 0.01 * 1000;

    float f10 = accum(0.001f, 10000);
    float f11 = 0.001 * 10000;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "f00, f01 : " << f00 << ", " << f01 << std::endl;
    std::cout << "f10, f11 : " << f10 << ", " << f11 << std::endl;

    float f20 = 77777776;
    float f21 = f20 + 1.0f;
    std::cout << "f20, f21 : " << f20 << ", " << f21 << std::endl;

    f20 = 77777.773;
    f21 = f20 + 0.001f;
    std::cout << "f20, f21 : " << f20 << ", " << f21 << std::endl;

    // f20 = 7777.773;
    // f21 = f20 + 0.001f;
    // std::cout << "f20, f21 : " << f20 << ", " << f21 << std::endl;

    return 0;
}