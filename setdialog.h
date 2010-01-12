#ifndef SETDIALOG_H
#define SETDIALOG_H
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QDialog>



namespace Ui {
    class SetDialog;
}

class SetDialog : public QDialog {
    Q_OBJECT
public:
    SetDialog(QWidget *parent = 0);
    ~SetDialog(){};

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);


private:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QDialogButtonBox *buttonBox;

};

#endif // SETDIALOG_H
