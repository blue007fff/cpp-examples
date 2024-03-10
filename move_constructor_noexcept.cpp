#include <iostream>
#include <vector>

struct S
{
    S(int data) : mData(data) { std::cout << "default: " << mData << std::endl; }
    S(const S &s) : mData{s.mData} { std::cout << "copy: " << mData << std::endl; }
    // S(S &&s) : mData{s.mData} { std::cout << "move: " << mData << std::endl; }
    S(S &&s) noexcept : mData{s.mData} { std::cout << "move: " << mData << std::endl; }

    int mData;
};

int main()
{
    // c++ 11 부터??
    // - noexcept : noexcept(true) 와 동일.
    // - strong exception guarantee 를 위해 사용.
    //   - std::move_if_noexcept(r);
    //   - move constructor 에 noexcept 를 붙이지 않으면 stl container 원소 이동 시,
    //     move sematics 가 아닌 copy semantics 로 동작.

    std::vector<S> v1{1, 2, 3};
    std::cout << "start ----------------------" << std::endl;
    v1.push_back(30);
    // v1.emplace_back(30);

#if 0
    // true  (기본적으로 유저 정의 소멸자는 noexcept)
    bool b1 = noexcept(std::declval<S>().~S());
    // true  (T(rvalue t)는 이동생성자가 없으므로 복사생성자가 noexcept)
    bool b2 = noexcept(S(std::declval<S>()));
    std::cout << b1 << std::endl;
    std::cout << b2 << std::endl;
#endif

    return 0;
}