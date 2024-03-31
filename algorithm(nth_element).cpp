#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

template <typename T>
void print(const std::vector<T> &list)
{
    // for (T i : list)
    //     std::cout << i << " ";
    // std::cout << std::endl;

    std::copy(list.begin(), list.end(),
              std::ostream_iterator<T>(std::cout, ", "));
    std::cout << '\n';
}

void example_nth_element()
{
    std::cout << __FUNCTION__ << "==========================" << std::endl;
    std::vector v{5, 6, 4, 3, 2, 6, 7, 9, 3};
    print(v);

    auto print_element = [&v](size_t idx)
    {
        std::cout << "[" << idx << "]"
                  << "=" << v[idx] << " : ";
    };

    size_t mididx = v.size() / 2;
    std::nth_element(v.begin(), v.begin() + mididx, v.end());
    print_element(mididx);
    print(v);

    std::nth_element(v.begin(), v.begin() + 1, v.end(), std::greater<int>());
    print_element(1);
    print(v);

    std::nth_element(v.begin(), v.begin(), v.end()); //, std::greater<int>());
    print_element(0);
    print(v);

    std::nth_element(v.begin(), v.end() - 1, v.end(), std::greater<int>());
    print_element(v.size() - 1);
    print(v);

    std::nth_element(v.begin(), v.end() - 2, v.end(), std::greater<int>());
    print_element(v.size() - 2);
    print(v);
}

int main()
{
    example_nth_element();
    return 0;
}