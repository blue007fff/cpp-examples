#include <iostream>

void print_vtable(void *object, int n = 5)
{
    int64_t **pvtable = (int64_t **)object;
    int64_t *vtable = *pvtable;
    std::cout << "vtable : " << pvtable << "->" << vtable << std::endl;

    for (int i = 0; i < n; ++i)
    {
        std::cout << "vtable[" << i << "] : " << vtable + i << " : "
                  << std::hex << vtable[i] << std::endl;
    }
}

void print_memory()
{
    std::cout << __FUNCTION__ << "==========================" << std::endl;

    class Base
    {
    public:
        int32_t i0;
        int8_t i1;
        virtual ~Base() {}
    };

    // virtual function table 을 가지고 있어,
    // memeory align : 8 byte.
    Base object;
    std::cout << "Base: " << sizeof(object) << " : " << &object << std::endl;
    std::cout << "Base::i0 : " << static_cast<void *>(&(object.i0)) << std::endl;
    std::cout << "Base::i1 : " << static_cast<void *>(&(object.i1)) << std::endl;
}

void print_vtable()
{
    std::cout << __FUNCTION__ << "==========================" << std::endl;

    class Base
    {
    public:
        int32_t i0;
        int8_t i1;
        Base()
        {
            std::cout << __FUNCTION__ << std::endl;
            print_vtable(this);
        }
        virtual ~Base() {}
        virtual void func1() { std::cout << __FUNCTION__ << std::endl; }
        virtual void func2() { std::cout << __FUNCTION__ << std::endl; }
    };

    class Child : public Base
    {
    public:
        Child()
        {
            std::cout << __FUNCTION__ << std::endl;
            print_vtable(this);
        }
        virtual ~Child() {}
        virtual void func1() override { std::cout << __FUNCTION__ << std::endl; }
        void func3() {}
    };

    std::cout << "Base b0 : start" << std::endl;
    Base b0;
    std::cout << "Base b0 : end" << std::endl;
    print_vtable(&b0);

    std::cout << "Child c0 : start" << std::endl;
    Child c0;
    std::cout << "Child c0 : end" << std::endl;
    print_vtable(&c0);

// int64_t *base_vtable = *((int64_t **)&b0);
// int64_t *child_vtable = *((int64_t **)&c0);

// TODO: virtual function pointer 값이 1이 나오는데 확인 필요.
// void (Child::*child_func1)() = &Child::func1;
#if 0
auto base_func1 = &Base::func1;
    auto base_func2 = &Base::func1;
    auto child_func1 = &Child::func1;
    auto child_func2 = &Child::func2;
    auto child_func3 = &Child::func3;
    std::cout << "Base::func1 : " << (void *)base_func1 << std::endl;
    std::cout << "Base::func2 : " << (void *)base_func2 << std::endl;
    std::cout << "Child::func1 : " << (void *)child_func1 << std::endl;
    std::cout << "Child::func2 : " << (void *)child_func2 << std::endl;
    std::cout << "Child::func3 : " << (void *)child_func3 << std::endl;
#endif
}

#define BASE_CLASS(ClassName)   \
    struct ClassName            \
    {                           \
        virtual ~ClassName() {} \
        int m_data;             \
    };

void multiple_inheritance_pointer()
{
    std::cout << __FUNCTION__ << "==========================" << std::endl;

    BASE_CLASS(Base1);
    BASE_CLASS(Base2);
    struct Child : public Base1, Base2
    {
        virtual ~Child(){};
    };

    Child c1;
    Base1 *pB1 = &c1;
    Base2 *pB2 = &c1;
    Child *pC1 = &c1;

    // Base1 *pB11 = pB2; // compile error
    Base1 *pB12 = dynamic_cast<Base1 *>(pB2);
    Base2 *pB21 = dynamic_cast<Base2 *>(pB1);

    std::cout << "sizeof(Base1): " << sizeof(Base1) << std::endl;
    std::cout << "sizeof(Base2): " << sizeof(Base2) << std::endl;
    std::cout << "sizeof(Child): " << sizeof(Child) << std::endl;

    std::cout << "pB1 == pC1: " << (pB1 == pC1) << std::endl;
    std::cout << "pB2 == pC1: " << (pB2 == pC1) << std::endl;
    std::cout << "(void*)pB1 == (void*)pB2: " << ((void *)pB1 == (void *)pB2) << std::endl;

    std::cout << "pB1: " << pB1 << std::endl;
    std::cout << "pB2: " << pB2 << std::endl;
    std::cout << "pC1: " << pC1 << std::endl;
    std::cout << "pB12: " << pB12 << std::endl;
    std::cout << "pB21: " << pB21 << std::endl;
}

int main()
{
    print_memory();
    print_vtable();

    multiple_inheritance_pointer();
    // https://dataonair.or.kr/db-tech-reference/d-lounge/technical-data/?mod=document&uid=235880
    return 0;
}