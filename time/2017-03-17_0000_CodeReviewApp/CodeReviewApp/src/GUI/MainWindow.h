#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Core/FuncInfo.h"
#include "OptionsWindow.h"
#include <QProgressBar>

class GraphicInterface;

class MainWindow : public QMainWindow
{
    friend GraphicInterface;
    Q_OBJECT
        
public:
    MainWindow(QWidget *parent = Q_NULLPTR);

    void setGraphicInterface(GraphicInterface * graphicInterface);
    void makeTableWidgetForFuncInfo(const FuncInfoContainer &v);
   // void initProgressBar(unsigned lastValue);

private:
    Ui::MainWindowClass ui;
    GraphicInterface * m_graphicInterface = nullptr;
    QProgressBar * pprb = nullptr;

private slots:
    void setCorePath();
    void startParse();
    void openSelectedFile(QModelIndex index);

   
};
