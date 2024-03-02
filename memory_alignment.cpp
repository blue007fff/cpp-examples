#include <iostream>
#include <cxxabi.h>

std::string get_demangle_name(const char *mangle_name)
{
    std::string demangle_name;
    int status;
    char *realname = abi::__cxa_demangle(mangle_name, 0, 0, &status);
    demangle_name = realname;
    free(realname);
    return demangle_name;
}

template <typename T>
void print_type_info()
{
    std::cout << get_demangle_name(typeid(T).name());
    std::cout << "(" << sizeof(T) << ":";
    std::cout << alignof(T) << "a)";
    std::cout << " : ";
}

#define print_member_info(TYPE, MEMBER) \
    std::cout << offsetof(TYPE, MEMBER) << "(" << sizeof(TYPE::MEMBER) << ") ";

void test1()
{
    std::cout << __FUNCTION__ << std::endl;
    struct A1
    {
        int16_t i0;
        int8_t i1;
    };
    struct A2
    {
        int64_t i0;
        // int128_t i0;
        int8_t i1;
    };

    print_type_info<A1>();
    print_member_info(A1, i0);
    print_member_info(A1, i1);
    std::cout << std::endl;

    print_type_info<A2>();
    print_member_info(A2, i0);
    print_member_info(A2, i1);
    std::cout << std::endl;
}

void test2()
{
    std::cout << __FUNCTION__ << std::endl;
    struct A1
    {
        int32_t i0;
        int64_t i1;
        int8_t i2;
    };
    struct A2
    {
        int64_t i0;
        int8_t i1;
        int32_t i2;
    };

    print_type_info<A1>();
    print_member_info(A1, i0);
    print_member_info(A1, i1);
    print_member_info(A1, i2);
    std::cout << std::endl;

    print_type_info<A2>();
    print_member_info(A2, i0);
    print_member_info(A2, i1);
    print_member_info(A2, i2);
    std::cout << std::endl;
}

void test3()
{
    std::cout << __FUNCTION__ << std::endl;

    struct alignas(32) A1
    {
        int32_t i0;
    };

    struct A2
    {
        int8_t i0[5];
    };

    struct A3
    {
        alignas(8) int8_t i0[5];
    };

    print_type_info<A1>();
    print_member_info(A1, i0);
    std::cout << std::endl;

    print_type_info<A2>();
    print_member_info(A2, i0);
    std::cout << std::endl;

    print_type_info<A3>();
    print_member_info(A3, i0);
    std::cout << std::endl;
}

int main()
{
    // https://learn.microsoft.com/ko-kr/cpp/cpp/alignment-cpp-declarations?view=msvc-170#alignof-and-alignas
    // 1. 멤버 변수는 해당 변수의 자료형 크기 배수 위치에서 시작.
    // 2. 객체 크기는 가장 큰 멤버 변수 크기 배수 크기를 가짐.

    test1();
    test2();
    test3();
    return 0;
}