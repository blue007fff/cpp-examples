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

void example_partition()
{
    std::cout << __FUNCTION__ << "==========================" << std::endl;
    // pred 가 참인 원소들을 거짓인 원소 앞에 배치.
    // - pred 에서 당연히 v 값을 수정하면 안됨.

    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto itr = std::partition(v.begin(), v.end(), [](int i)
                              { return i % 2 == 0; });

    std::copy(std::begin(v), itr, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " - ";
    std::copy(itr, std::end(v), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout.setf(std::ios_base::boolalpha);
    std::cout << std::is_partitioned(v.begin(), v.end(), [](int i)
                                     { return i % 2 == 0; });
}

int main()
{
    example_partition();
    return 0;
}