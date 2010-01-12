#include"pages.h"
#include <QLabel>
#include <QLineEdit>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>

extern double A ;
extern double B ;
FormulaWidget::FormulaWidget(QWidget *parent)
    :QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* hLayout1 = new QHBoxLayout(this);
    QHBoxLayout* hLayout2 = new QHBoxLayout(this);

    QLabel* label = new QLabel(this);
    QFont font;
    font.setPointSize(20);
    label->setFont(font);
    label->setText("Formula: A-B*log(SUM(F));");

    QLabel* label_2 = new QLabel(this);
    label_2->setFont(font);
    label_2->setText("A:");
    QLineEdit* lineEdit = new QLineEdit(this);    

    QLineEdit* lineEdit_2 = new QLineEdit(this);
    QLabel* label_3 = new QLabel(this);
    label_3->setFont(font);
    label_3->setText("B:");


    lineEdit->setText(QString("%1").arg(A));
    lineEdit_2->setText(QString("%1").arg(B));

    mainLayout->addWidget(label);
    hLayout1->addWidget(label_2);
    hLayout1->addWidget(lineEdit);

    hLayout2->addWidget(label_3);
    hLayout2->addWidget(lineEdit_2);

    mainLayout->addLayout(hLayout1);
    mainLayout->addLayout(hLayout2);

    connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(lineEditAChanged(QString)));
    connect(lineEdit_2,SIGNAL(textChanged(QString)),this,SLOT(lineEditBChanged(QString)));
}
void FormulaWidget::lineEditAChanged(QString var)
{
    A = var.toDouble();
    QSettings set ;
    set.setValue("A",A);
}
void FormulaWidget::lineEditBChanged(QString var)
{
    B = var.toDouble();
    QSettings set ;
    set.setValue("B",B);
}
CustomCurveWidget::CustomCurveWidget(QWidget *parent)
    :QWidget(parent)
{

}
