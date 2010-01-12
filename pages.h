#ifndef PAGES_H
#define PAGES_H
#include <QWidget>
class FormulaWidget:public QWidget
{
    Q_OBJECT
public:
    FormulaWidget(QWidget* parent = 0 );

public slots:
    void lineEditAChanged(QString);
    void lineEditBChanged(QString);
};
class CustomCurveWidget:public QWidget
{
    Q_OBJECT
public:
    CustomCurveWidget(QWidget* parent = 0 );

};

#endif // PAGES_H
