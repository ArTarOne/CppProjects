#pragma once

#include "MainWindow.h"

class QTWItemInfo : public QTableWidgetItem
{
public:
    QTWItemInfo(const FuncInfo & startLine)
        : m_func(startLine)
    {
    }
   
    ~QTWItemInfo(){}
   
    FuncInfo func() const { return m_func; }
    void setfunc(FuncInfo val) { m_func = val; }

private:
    FuncInfo m_func;

};

