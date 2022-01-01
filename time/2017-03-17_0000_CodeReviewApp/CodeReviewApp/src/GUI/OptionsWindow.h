#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QDialog>
#include "ui_OptionsWindow.h"
#include "Application/ISettings.h"



class GraphicInterface;


class OptionsWindow : public QDialog
{
    friend GraphicInterface;

    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = 0);
    ~OptionsWindow();
    Ui::OptionsWindow uiOptions;
    
    void setGraphicInterface(GraphicInterface * graphicInterface);

private:  
    GraphicInterface * m_graphicInterface = nullptr;

private slots :
    void onButtonSave();  


};

#endif // OPTIONSWINDOW_H
