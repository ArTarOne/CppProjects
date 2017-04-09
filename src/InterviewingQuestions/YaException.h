#pragma once

namespace YaException
{
    void throwExceptionStd()
    {
        throw(std::exception());
    }

    void throwInteger()
    {
        throw(int(10));         // ����������� ����� ����� ������
    }                           // �� ��� �������� ����� �������������
                                // �� std::Exception.
                                // catch(...) ������������� ���!!!

    void resolve()              
    {
        AFUN;

        try
        {
            AMSG("In try");
            //throwExceptionStd();
            throwInteger();
        }
        catch (std::exception &)
        {
            AMSG("In catch (std::exception &)");
        }
        catch (...)
        {
            AMSG("catch (...)");
        }

    }
}