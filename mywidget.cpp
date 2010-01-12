#include "mywidget.h"
#include "QMessageBox"
#include <QtGui/QApplication>
const int FRAME_DATA_NUMS = 6000;
extern double A ;
extern double B ;
MyWidget::MyWidget(QString path ,QWidget* parent, Qt::WindowFlags f):QWidget(parent,f)
{
    QString name = path.right(path.length()-path.indexOf("#")-1);
    QString timename = name.left(name.length()-4);
    startTime=QDateTime::fromString(timename,"yyyy-MM-dd hh-mm-ss");

    openFile(path);

    vboxLayout= new QVBoxLayout(this);
    setLayout(vboxLayout);

    toolWidget = new QWidget(this);
    hboxLayout = new QHBoxLayout(toolWidget);
    toolWidget->setLayout(hboxLayout);
    QLabel *label = new QLabel("Minutes",toolWidget);
    counter = new QwtCounter(this);
    int max = fileSize/FRAME_DATA_NUMS+1 ;
    counter->setRange(1,max,1,2);

    connect(counter, SIGNAL(valueChanged(double)),
        this, SLOT(setFrameIndex(double)) );

    hboxLayout->addWidget(label);
    hboxLayout->addWidget(counter);
    hboxLayout->addWidget(new QWidget(toolWidget), 10);


    plot = new DataPlot(this);

    plot->setTitle(path);

    tableView = new QTableView(this);
    vboxLayout->addWidget(toolWidget);
    vboxLayout->addWidget(plot);
    vboxLayout->addWidget(tableView);


    vboxLayout->setContentsMargins(0, 0, 0, 0);
    initTableModel();

    setFrameIndex(1);

}
MyWidget::~MyWidget()
{
    if(file->isOpen())
        file->close();
}

void MyWidget::setFrameIndex(double index)
{
    if((index-1)*FRAME_DATA_NUMS<=fileSize)
    {
        if(index*FRAME_DATA_NUMS<=fileSize)
        {
            memLength = FRAME_DATA_NUMS;
            mapFile((index-1)*FRAME_DATA_NUMS,FRAME_DATA_NUMS);
        }
        else
        {
            memLength = fileSize-(index-1)*FRAME_DATA_NUMS;
            mapFile((index-1)*FRAME_DATA_NUMS,fileSize-(index-1)*FRAME_DATA_NUMS);
        }
        freshDisplay();
    }
}
void MyWidget::freshPlot()
{
    double x[PLOT_SIZE],y[PLOT_SIZE];
    memset(x,'\0',PLOT_SIZE*sizeof(double));
    memset(y,'\0',PLOT_SIZE*sizeof(double));
    if(memLength<FRAME_DATA_NUMS)
    {
        for(int i= 0; i< PLOT_SIZE ;i++)
            x[i] = i ;
        memLength -= 1 ;
    }
    for(int i = 0 ;i <memLength*5/100;i++ )
    {
            double ret = 0;
            for(int j= 0 ; j<20;j+=2)
                ret +=memData[i*20+j]+memData[i*20+j+1]*256;
            if(ret == 0)
                ret = A-B ;
            else
                ret = A-B*log(ret);
            x[i] = i ;
            y[i] = ret ;

    }
    plot->setData(x,y);
}
void MyWidget::freshTable()
{
    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());

    for(int i = 0;  i<memLength*5/100;i++)
    {
        QDateTime t = startTime.addMSecs(i*200);
        int currentRow = model->rowCount();
        model->insertRow(currentRow);
        qApp->processEvents();
        QModelIndex index1 = model->index(currentRow, 0,QModelIndex());
        model->setData(index1, t.toString("yyyy-MM-dd hh:mm:ss:zzz"));
        double ret = 0;
        for(int j= 0;j<20;j+=2)
        {
            index1 = model->index(currentRow,j/2+1,QModelIndex());
            ret +=memData[i*20+j]+memData[i*20+j+1]*256;
            model->setData(index1,memData[i*20+j]+memData[i*20+j+1]*256);
        }
        index1 = model->index(currentRow, 11,QModelIndex());

        if(ret == 0)
            ret = A-B ;
        else
            ret = A-B*log(ret);
        model->setData(index1,ret);
    }
}

void MyWidget::freshDisplay()
{
    freshPlot();
    freshTable();
}

bool MyWidget::openFile(QString name)
{
    file = new QFile(name,this);
    file->open(QIODevice::ReadOnly);
    fileSize = file->size();    
    return true ;
}

void MyWidget::mapFile(int s,int l)
{
    if(file!=0&&file->isOpen())
    {
        memData = file->map(s,l);
    }
}

void MyWidget::initTableModel()
{
    model = new QStandardItemModel(0,12,this);
    model->setHeaderData(0, Qt::Horizontal, "time");
    for(int i = 1 ; i < 11 ;i++)
        model->setHeaderData(i, Qt::Horizontal, i);
    model->setHeaderData(11, Qt::Horizontal, "Meas");
    tableView->setModel(model);
}

