#include <iostream>

struct Foo
{
    std::string m_str;
    Foo(std::string str) : m_str(str) { std::cout << "Default-ctor: " << m_str << std::endl; }
    // Foo(const Foo &) = delete;
    // Foo(Foo &&) = delete;
    Foo(const Foo &rhs) : m_str{rhs.m_str} { std::cout << "Copy-ctor: " << m_str << std::endl; }
    Foo(Foo &&rhs) noexcept : m_str(std::move(rhs.m_str)) { std::cout << "Move-ctor: " << m_str << std::endl; }
    ~Foo() { std::cout << "Destructor: " << m_str << std::endl; }
};

void PrintFoo(Foo foo) { std::cout << "PrintFoo: " << foo.m_str << std::endl; }
Foo MakeFoo1() { return Foo("MakeFoo1"); }

Foo MakeFoo2()
{
    Foo foo("MakeFoo2");
    return foo;
}

Foo MakeFoo3(bool flag)
{
    Foo foo("MakeFoo3:true");
    return flag ? foo : Foo("false");

    // foo.m_str += flag ? "true" : "false";
    // return foo;
}

int main()
{
    // Guaranteed copy elision : pvalue
    // gvalue(NRVO,...) : not guaranteed

    // guaranteed
    {
        std::cout << "guaranteed copy elision " << std::string(20, '*') << std::endl;
        Foo foo1 = MakeFoo1();
        PrintFoo(Foo("Foo1"));
    }

    // not guaranteed
    {
        std::cout << "copy elision " << std::string(20, '*') << std::endl;
        Foo foo2 = MakeFoo2();
    }

    {
        std::cout << "can't copy elision " << std::string(20, '*') << std::endl;
        Foo foo3 = MakeFoo3(false);
    }

    return 0;
}