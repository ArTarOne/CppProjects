#include "AboutWindow.h"
#include "ui_AboutWindow.h"
#include "GraphicInterface.h"
#include "StdPlus/StdPlus.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent)
   
{
    uiAbout.setupUi(this);
   
    uiAbout.lblWeb->setText("<A HREF='https://github.com/marleeeeeey/CodeReview'>https://github.com/marleeeeeey/CodeReview</A>");
    uiAbout.lblWeb->setOpenExternalLinks(true);
  
}

AboutWindow::~AboutWindow()
{
  
}
void AboutWindow::setGraphicInterface(GraphicInterface * graphicInterface)
{
    m_graphicInterface = graphicInterface;
}