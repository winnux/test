#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QFile>
#include <qlabel.h>
#include <QDateTime>
#include "qwt_counter.h"
#include "data_plot.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QString path,QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~MyWidget();
   // void setTitle(QString s ){title = s;};
private:
    QVBoxLayout *vboxLayout ;
    QHBoxLayout *hboxLayout ;
    QTableView  *tableView ;
    DataPlot    *plot ;
    QWidget     *toolWidget ;
    QwtCounter  *counter ;
    QAbstractItemModel *model ;
    QFile       *file ;
    qint64         fileSize ;
    uchar        *memData ;
    int          memLength ;
    QDateTime    startTime ;
  //  QString     title ;
public slots:
    void setFrameIndex(double);
protected:
    void freshDisplay();
    void freshPlot();
    void freshTable();
    void initTableModel();
    bool openFile(QString);
    void mapFile(int,int);
};

#endif // MYWIDGET_H
