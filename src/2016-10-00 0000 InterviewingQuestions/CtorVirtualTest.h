#pragma once

#include "SpeakingClass.h"


namespace CtorVirtualTest
{
    class A
    {
    public:
        A()
        {
            AFUN;
            init();         // ���������� init �������� ������
        }                   // ��������, ��� � C# �������� �����!

        virtual ~A()        // virtual, ����� ��������� ������� 
        {                   // �� ��������� �� ������� �����
            AFUN;
        }       

        virtual void init()
        {
            AFUN;
        }

    private:

        SpeakingClass sc;
    };

    class B : public A      // public ������������, ����� 
    {                       // � �������� ������������ ������ ��� 
    public:                 // ������ � �������� �������������� 
        B()                 // ��������� �� ����������� ����� 
        {                   // � ��������� �� ������� �����. 
            AFUN;
        }

        ~B()
        {
            AFUN;
        }

        virtual void init()
        {
            AFUN;
        }

    private:

        SpeakingClass sc;
    };

    void resolve()
    {
        AFUN;
        A * a = new B();
        a->init();
        delete a;
    }
}

// SpeakingClass::SpeakingClass(int)
// CtorVirtualTest::A::A(void)
// void CtorVirtualTest::A::init(void)      // ���������� ����������� ������ 
                                            // �������� ������!!!
// SpeakingClass::SpeakingClass(int)        
// CtorVirtualTest::B::B(void)

// CtorVirtualTest::B::~B(void)
// SpeakingClass::~SpeakingClass(void)

// CtorVirtualTest::A::~A(void)
// SpeakingClass::~SpeakingClass(void)