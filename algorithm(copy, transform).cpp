#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template <typename T>
void print(const std::vector<T> &list)
{
    for (T i : list)
        std::cout << i << " ";
    std::cout << std::endl;
}

void example_copy1()
{
    std::vector<double> a{1.1, 2.1, 3.1, 4.1, 5.1};
    std::vector<double> b;

    b.resize(a.size());
    std::copy(a.begin(), a.end(), b.begin());
    print(b);

    std::copy(a.begin(), a.end(), std::back_inserter(b));
    print(b);

    std::vector<int> d0;
    std::copy(a.begin(), a.end(), std::back_inserter(d0));
    print(d0);

    b.clear();
    std::copy_if(a.begin(), a.end(), std::back_inserter(b), [](double d)
                 { return d < 3.0; });
    print(b);
}

void example_transform1()
{
    std::vector<double> a{1.1, 2.1, 3.1, 4.1, 5.1};
    std::vector<double> b;
    std::transform(a.begin(), a.end(), std::back_inserter(b), [](double d)
                   { return d * 2; });
    print(b);

    struct Ax3
    {
        double operator()(double d0) { return d0 * 3; }
    };
    b.clear();
    std::transform(a.begin(), a.end(), std::back_inserter(b), Ax3());
    print(b);

    struct AxB
    {
        double operator()(double d0, double d1) { return d0 * d1; }
    };
    auto Ax4 = std::bind(AxB(), std::placeholders::_1, 4.0);

    b.clear();
    std::transform(a.begin(), a.end(), std::back_inserter(b), Ax4);
    print(b);
}

int main()
{
    example_copy1();
    example_transform1();
    return 0;
}