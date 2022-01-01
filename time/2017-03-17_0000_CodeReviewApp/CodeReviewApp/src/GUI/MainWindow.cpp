#include "MainWindow.h"
#include <QFileDialog>
#include <QLineEdit>
#include <QProcess>
#include "StdPlus/StdPlus.h"
#include "GraphicInterface.h"
#include "QTWItemInfo.h"
#include "QtPlus/QtPlus.h"
 

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    ui.setupUi(this);      

    QObject::connect(ui.bPathBrowse, SIGNAL(clicked()),	this, SLOT(setCorePath()));    
    QObject::connect(ui.bStart, SIGNAL(clicked()), this, SLOT(startParse()));    
    QObject::connect(ui.tOutView, 
        SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openSelectedFile(QModelIndex)));

    QObject::connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

//     pprb = new QProgressBar;
//     ui.statusBar->addWidget(pprb);
}

void MainWindow::setGraphicInterface(GraphicInterface * graphicInterface)
{
    m_graphicInterface = graphicInterface;
    
    std::string path = m_graphicInterface->m_settings->get("path");
    ui.labelCurrentPath->setText(QString::fromStdString(path));

}

void MainWindow::setCorePath()
{
	QString strPath =
		QFileDialog::getExistingDirectory(0, "Directory", "");

    std::string path = strPath.toStdString();

    Commands & cmds = *(m_graphicInterface->m_ptrCommands);
//     ICommand * cmd = getCommand(e_idCommand_setPathCommmand, cmds);
//     cmd->execute(&path);
    executeCommand(e_idCommand_setPathCommmand, cmds, &path);

    m_graphicInterface->m_settings->set("path", path);

    ui.labelCurrentPath->setText(strPath);
    ui.labelCurrentPath->adjustSize();
}

void MainWindow::startParse()
{     
    //initProgressBar();



    Commands & cmds = *(m_graphicInterface->m_ptrCommands);
    executeCommand(e_idCommand_startParseCommand, cmds);

    
}

void MainWindow::openSelectedFile(QModelIndex index)
{    
	QProcess* proc = new QProcess;
    
    QTableWidgetItem* p = ui.tOutView->item(ui.tOutView->currentRow()
        ,(ui.tOutView->currentColumn())); // get current item

    QTWItemInfo* fptr = dynamic_cast<QTWItemInfo*>(p);

    QString file = QString::fromStdString(fptr->func().filePath());

    QString line = QString::fromStdString(std::to_string(fptr->func().startLine()));

    QString qCmd = QString("notepad++ ") + "\"" + file + "\"" + " -n" + line;
    
    proc->start(qCmd);
}

void MainWindow::makeTableWidgetForFuncInfo(const FuncInfoContainer & v)
{
    using namespace stdplus;

 
     ui.tOutView->setSortingEnabled(true);
     ui.tOutView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // запрет редактировани€
     ui.tOutView->setSelectionMode(QAbstractItemView::SingleSelection); // одиночное выделение
 
     ui.tOutView->setRowCount(v.size());
     ui.tOutView->setColumnCount(4);
 
     QStringList columnLst;
     columnLst << "Function name" << "Function size" << "File name" << "Status";
     ui.tOutView->setHorizontalHeaderLabels(columnLst);
 
     QStringList rowLst;
     for (int i = 0; i < v.size(); i++)
     {
         rowLst << QString::fromStdString(std::to_string(i+1));
     }
     ui.tOutView->setVerticalHeaderLabels(rowLst);
 
 	for (int row = 0; row < ui.tOutView->rowCount(); row++)
 	{
         for (int column = 0; column < ui.tOutView->columnCount(); column++)
         {
             if (column == 0)
             {
                 QTableWidgetItem* ptwi = new QTWItemInfo(v[row]);
                 ptwi->setText(QString::fromStdString(v[row].prototype().name()));
                 ui.tOutView->setItem(row, column, ptwi);
                // ptwi->setFlags(Qt::NoItemFlags); // неактивные €чейки
             }
             else if (column == 1)
             {
                 QTableWidgetItem* ptwi = new QTWItemInfo(v[row]);
                 ptwi->setData(Qt::DisplayRole, v[row].funcSize()); // в числовом формате дл€ сортировки
                 ui.tOutView->setItem(row, column, ptwi);
              //   ptwi->setFlags(Qt::NoItemFlags);//неактивные €чейки
             }
             else if (column == 2)
             {
                 QTableWidgetItem* ptwi = new QTWItemInfo(v[row]);
                
                 std::string fullFilePath = v[row].filePath();
                 std::string path = ui.labelCurrentPath->text().toStdString();
                
                 std::string::size_type pos = fullFilePath.find(path);
                 fullFilePath.erase(pos, path.size());

                 ptwi->setText( QString::fromStdString(fullFilePath));
                 ui.tOutView->setItem(row, column, ptwi);   
             }
             else if (column == 3)
             {
                 QTableWidgetItem* ptwi = new QTWItemInfo(v[row]);

                 if (v[row].funcSize() < to_int(m_graphicInterface->m_settings->get("warningFuncSize")))  // TODO ???
                     ptwi->setText("OK");
                 else
                     ptwi->setText("WARNING");

                 ui.tOutView->setItem(row, column, ptwi);
                // ptwi->setFlags(Qt::NoItemFlags); // неактивные €чейки
             }
         }
 	}
 
     ui.tOutView->resizeColumnsToContents();
     ui.tOutView->resizeRowsToContents();
   
}

// void MainWindow::initProgressBar(unsigned lastValue)
// {
//     pprb->setRange(0, lastValue);
//     pprb->setAlignment(Qt::AlignCenter);
// 
// 
// }


