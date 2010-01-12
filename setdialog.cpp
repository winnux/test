#include "setdialog.h"
#include "pages.h"

SetDialog::SetDialog(QWidget *parent) :
    QDialog(parent)
{
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    listWidget = new QListWidget(this);

    listWidget->setViewMode(QListView::IconMode);
    listWidget->setIconSize(QSize(72, 72));
    listWidget->setMovement(QListView::Static);
    listWidget->setMaximumWidth(128);
    listWidget->setSpacing(12);

    horizontalLayout->addWidget(listWidget);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(new FormulaWidget(stackedWidget));
    stackedWidget->addWidget(new CustomCurveWidget(stackedWidget));

    horizontalLayout->addWidget(stackedWidget);


    verticalLayout->addLayout(horizontalLayout);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    verticalLayout->addWidget(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QListWidgetItem *configButton = new QListWidgetItem(listWidget);
    configButton->setIcon(QIcon(":/images/mydocuments.png"));
    configButton->setText(tr("Calc Formula"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(listWidget);
    updateButton->setIcon(QIcon(":/images/looknfeel.png"));
    updateButton->setText(tr("Custom curve"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(listWidget,
            SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));
    listWidget->setCurrentRow(0);




    setWindowTitle(tr("Config Dialog"));
}


void SetDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    stackedWidget->setCurrentIndex(listWidget->row(current));
}


