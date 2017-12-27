#pragma once
#include "StdHelper.hpp"

namespace SOAnswer02
{
    void resolve()
    {
        AFUN;

        bool isFillFromFile = false;    //true ��� ������ �� �����
        int a[60][60];

        if (isFillFromFile)
        {
            std::ifstream ist("matrix.txt");
            char ch;
            for (int i = 0; i < 60; i++)    // ����������� �� ������� ���������!!!
                for (int j = 0; j < 60; j++)
                    ist >> a[i][j] >> ch;   // �� ��������� ���������� ������!!!
        }
        else
        {
            for (int i = 0; i < 60; i++)
                for (int j = 0; j < 60; j++)
                    a[i][j] = i + j;
        }
        

        std::ofstream ost("matrix.txt", std::ios_base::trunc);
        for (int i = 0; i < 60; i++)
            for (int j = 0; i < 60; i++)
            {
                ost << a[i][j] << " ";      // ������ ������� � ����
                cout << a[i][j] << " ";
            }

        ost.close();
    }

}
