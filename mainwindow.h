#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "mywidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    bool loadData(QString filePath);
    void addNewTab(QString fileName);
private:
    Ui::MainWindow *ui;

private slots:
    void on_actionAbout_triggered();
    void on_actionSet_triggered();
    void on_actionExit_triggered();
    void on_actionOpen_triggered();
    void onTabClose(int num);
private:
    QTabWidget* dataTabs;
};

#endif // MAINWINDOW_H
