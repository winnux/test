#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QTableView>
#include "setdialog.h"
#include <QSettings>

double A ;
double B ;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    uchar buf[100] ;
//    for(int i = 0; i< 100 ;i++)
//    {
//        if(i%2)
//            buf[i] = 1;
//        else
//            buf[i] = 0 ;
//    }
//    QFile file("1#2010-01-06 08-33-11.dat",this);
//    file.open(QIODevice::WriteOnly);
//    for(int i= 0 ;i<500 ;i++)
//        file.write((const char*)buf,100);
//    file.flush();
//     file.close();
    QSettings set ;
    A = set.value("A").toDouble();
    B = set.value("B").toDouble();

    ui->setupUi(this);
    dataTabs = new QTabWidget(this);
    setCentralWidget(dataTabs);
    dataTabs->setTabsClosable(true);

}

MainWindow::~MainWindow()
{
    dataTabs->clear();
    delete ui;
}
bool MainWindow::loadData(QString filePath)
{
    return true ;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void MainWindow::addNewTab(QString fileName)
{
    MyWidget *pNew = new MyWidget(fileName,dataTabs);
    dataTabs->addTab(pNew,fileName);
    connect(dataTabs, SIGNAL(tabCloseRequested(int)), SLOT(onTabClose(int)));
}

void MainWindow::on_actionOpen_triggered()
{
   QString fileName = QFileDialog::getOpenFileName(this);
   if(fileName.isEmpty())
       return ;
   QString name = fileName.right(fileName.length()-fileName.indexOf("#")-1);
   QString timename = name.left(name.length()-4);
   QDateTime startTime=QDateTime::fromString(timename,"yyyy-MM-dd hh-mm-ss");
   if(startTime.isValid()==false)
   {

       QMessageBox::critical(this,"error","wrong file name");
       return;
   }
   if(loadData(fileName))
   {
        addNewTab(fileName);
   }

}
void MainWindow::onTabClose(int tabNum)
{
   // if (tabWidget->widget(tabNum) == containerWidget)
    //        deleteLater();
    dataTabs->removeTab(tabNum);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionSet_triggered()
{
    SetDialog dlg(this);
 //   dlg.setVar(A,B);
    if(QDialog::Accepted==dlg.exec())
    {
  //      dlg.getVar(&A,&B);
  //      QSettings set ;
   //     set.setValue("A",A);
   //     set.setValue("B",B);
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About Analyzer","Copyright 2010.Analyze data tools ");
}
