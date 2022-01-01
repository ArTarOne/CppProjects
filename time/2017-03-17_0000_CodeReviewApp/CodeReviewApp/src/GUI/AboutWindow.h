#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include "ui_AboutWindow.h"

class GraphicInterface;

class AboutWindow : public QDialog
{
    friend GraphicInterface;

    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();
     Ui::AboutWindow uiAbout;

     void setGraphicInterface(GraphicInterface * graphicInterface);
private:
     GraphicInterface * m_graphicInterface = nullptr;
   
};

#endif // ABOUTWINDOW_H
