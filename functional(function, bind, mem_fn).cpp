// https://en.cppreference.com/w/cpp/utility/functional/function
#include <functional>
#include <iostream>

void print_num(int i) { std::cout << i << '\n'; }
struct PrintNum
{
    void operator()(int i) const { std::cout << i << '\n'; }
};
struct Foo
{
    /*explicit*/ Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << "num_ + i: " << num_ + i << '\n'; }
    int num_;
};

void sizeof_function()
{
    std::cout << __FUNCTION__ << " ===========================" << std::endl;

    auto func = [](int a, int b) -> int
    { return a + b; };

    std::function<int(int, int)> fn1 = func;
    int (*pfunc)(int, int) = func;

    std::cout << "sizeof(std::function) : " << sizeof(fn1) << std::endl;
    std::cout << "sizeof(int (*)(int, int)) : " << sizeof(pfunc) << std::endl;
}

void print_function_type()
{
    std::cout << __FUNCTION__ << " ===========================" << std::endl;

    // fn1 : PFviE
    // fn2 : St8functionIFviEE
    // fn3 : Z19print_function_typevEUliE_
    // fn4 : St8functionIFviEE
    auto fn1 = print_num;
    std::function<void(int)> fn2 = print_num;
    auto fn3 = [](int) {};
    std::function<void(int)> fn4 = fn3;
    auto fn5 = PrintNum();
    std::cout << "auto fn1 = print_num: " << typeid(fn1).name() << std::endl;
    std::cout << "std::function<void(int)> fn2 = print_num: " << typeid(fn2).name() << std::endl;
    std::cout << "auto fn3 = [](int) {}: " << typeid(fn3).name() << std::endl;
    std::cout << "std::function<void(int)> fn4 = fn3: " << typeid(fn4).name() << std::endl;
    std::cout << "auto fn5 = PrintNum(): " << typeid(fn5).name() << std::endl;
    // std::cout << "float (*)(int, char): " << typeid(float (*)(int, char)).name() << std::endl;

    // store the result of a call to std::bind
    std::function<void()> fn6 = std::bind(print_num, 314);
    std::cout << "std::function<void()> fn6 = std::bind(print_num, 314): "
              << typeid(fn6).name() << std::endl;

    auto fn7 = std::mem_fn(Foo::print_add);
    std::cout << "auto fn7 = std::mem_fn(Foo::print_add): "
              << typeid(fn7).name() << std::endl;

    auto fn8 = &Foo::print_add;
    std::cout << "auto fn8 = &Foo::print_add: "
              << typeid(fn8).name() << std::endl;

    std::function<void(const Foo &, int)> fn9 = &Foo::print_add;
    std::cout << "std::function<void(const Foo &, int)> fn9 = &Foo::print_add: "
              << typeid(fn9).name() << std::endl;

    std::cout << std::endl;
    std::cout << "std::function<void()>: " << typeid(std::function<void()>).name() << std::endl;
    std::cout << "std::function<void(int)>: " << typeid(std::function<void(int)>).name() << std::endl;
    std::cout << "std::function<void(int, float)>: " << typeid(std::function<void(int, float)>).name() << std::endl;
    std::cout << "std::function<double(int, float)>: " << typeid(std::function<double(int, float)>).name() << std::endl;
}

void function_examples()
{
    std::cout << __FUNCTION__ << " ===========================" << std::endl;

    std::cout << "store functions ----" << std::endl;
    std::function<void(int)> f_display = print_num;
    std::function<void()> f_display_3141 = []()
    { print_num(3141); };
    std::function<void()> f_display_31337 = std::bind(print_num, 31337);
    f_display(314);
    f_display_3141();  // store a lambda
    f_display_31337(); // store the result of a call to std::bind

    std::cout << "store member functions ----" << std::endl;
    // 멤버 함수는 반드시 & 연산자를 사용하여 주소값을 연결.
    std::function<void(const Foo &, int)> f_add_display = &Foo::print_add;
    const Foo foo(314159);
    f_add_display(foo, 1);
    f_add_display(314159, 1); // 314159 -> Foo(314159)

    // 멤버 변수도, 멤버 함수와 같이 연결 가능.
    std::function<int(Foo const &)> f_num = &Foo::num_;
    std::cout << "f_num = &Foo::num_: " << f_num(foo) << '\n';

    // store a call to a member function and object or object ptr
    // - bind()를 사용하여, 첫번째 파리미터에 foo 객체 연결.
    // - bind()를 사용하여, 첫번째 파리미터에 foo 객체 포인터 연결.
    // - store 함수의 인자를 원본함수의 2번째 인자로 연결.
    using std::placeholders::_1;
    std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
    std::function<void(int)> f_add_display3 = std::bind(&Foo::print_add, &foo, _1);
    f_add_display2(2);
    f_add_display3(3);

    // store a call to a function object
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(18);

    auto factorial = [](int n)
    {
        // store a lambda object to emulate "recursive lambda"; aware of extra overhead
        std::function<int(int)> fac = [&](int n)
        { return (n < 2) ? 1 : n * fac(n - 1); };
        // note that "auto fac = [&](int n) {...};" does not work in recursive calls
        return fac(n);
    };
    for (int i{5}; i != 8; ++i)
        std::cout << i << "! = " << factorial(i) << ";  ";
    std::cout << '\n';
}

void add(int x, int y) { std::cout << x << " + " << y << " = " << x + y << std::endl; }
void sub(int x, int y) { std::cout << x << " - " << y << " = " << x - y << std::endl; }

struct S
{
    int data;
    S(int data) : data(data) { std::cout << "S: 일반 생성자!" << std::endl; }
    S(const S &s) : data{s.data} { std::cout << "S: 복사 생성자!" << std::endl; }
    S(S &&s) : data{s.data} { std::cout << "S: 이동 생성자!" << std::endl; }
    void func1(const S &s2)
    {
        data += s2.data + 3;
        std::cout << "S::data: " << data << std::endl;
    }
};
void do_something(S &s1, const S &s2)
{
    s1.data += s2.data + 3;
    std::cout << "s1.data: " << s1.data << std::endl;
}
void bind_memfn_examples()
{
    std::cout << __FUNCTION__ << " ===========================" << std::endl;

    auto add_2_y = std::bind(add, 2, std::placeholders::_1);
    add_2_y(3);
    add_2_y(3, 4, 5); // 두 번째 인자 부터는 무시된다.

    auto sub_x_2 = std::bind(sub, std::placeholders::_1, 2);
    auto sub_y_x = std::bind(sub, std::placeholders::_2, std::placeholders::_1);
    sub_x_2(3);    // 3 - 2 를 계산한다.
    sub_y_x(4, 2); // 2 - 4 를 계산한다

    S s1(1), s2(2);
    std::cout << "Before : " << s1.data << std::endl;
    // s1 이 그대로 전달된 것이 아니라 s1 의 복사본이 전달되고, 유지됨!
    // auto do_something_with_s1 = std::bind(do_something, s1, std::placeholders::_1);
    auto do_something_with_s1 = std::bind(do_something, std::ref(s1), std::placeholders::_1);
    // auto do_something_with_s1 = std::bind(do_something, &s1, std::placeholders::_1); // error

    do_something_with_s1(s2);
    do_something_with_s1(s2);
    std::cout << "After :: " << s1.data << std::endl;

    std::cout << "Before : " << s1.data << std::endl;
    // auto s_func1 = std::bind(&S::func1, s1, std::placeholders::_1);
    auto s_func1 = std::bind(&S::func1, &s1, std::placeholders::_1);
    // - 멤버함수에서는 &s1 이 동작함, 위의 함수에서는 안됨.
    s_func1(s2);
    s_func1(s2);
    std::cout << "After :: " << s1.data << std::endl;

    int num10 = 10;
    auto fn_print_num_num10 = std::bind(print_num, num10);               // 이미 복사.
    auto fn_print_num_ref_num10 = std::bind(print_num, std::ref(num10)); // 계속 참조.
    num10 = 20;
    fn_print_num_num10();     // 10
    fn_print_num_ref_num10(); // 20
}
int main()
{
    // std::function 데이터 크기 : 32(gcc), 64(vc++)
    // * 멤버 함수는 구현 상 자신을 호출한 객체를 인자로 암묵적으로 받고 있음.
    // * 멤버 함수는 함수 이름이 주소값으로 암시적 변환이 불가.
    //   - & 연산자를 사용하여 명시적으로 주소값을 전달해야 함.
    // * 멤버 함수를 제외 한 모든 함수는 함수 이름이 주소값으로 암시적으로 변환 가능.
    // * std::bind(fn, obj,...) 객체 전달 시, 복사본이 전달 됨.
    //   - std::ref(obj) 를 사용해야 참조본 전달 가능.
    // * https://modoocode.com/254

    sizeof_function();
    std::cout << std::endl;

    print_function_type();
    std::cout << std::endl;

    function_examples();
    std::cout << std::endl;

    bind_memfn_examples();
}