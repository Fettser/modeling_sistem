#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QPushButton>
#include <QMetaProperty>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

settingsDialog::settingsDialog(QWidget *parent, QObject *selectedEl) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);
    const QMetaObject *metaObj= selectedEl->metaObject();
    for (int i = metaObj->propertyOffset(); i < metaObj->propertyCount(); i++) {
        QMetaProperty prop = metaObj->property(i);
        const char *name = prop.name();
        qDebug() << selectedEl->property(name);
        QHBoxLayout *HLayout = new QHBoxLayout;
        QLabel *label = new QLabel(QString(prop.name()) + ":");
        QLineEdit *line = new QLineEdit(selectedEl->property(name).toString());
        line->setValidator(new QRegularExpressionValidator(QRegularExpression("[1-9][0-9]{1}"),line));
        lines[name] = line;
        HLayout->addWidget(label);
        HLayout->addWidget(line);
        ui->verticalLayout->addLayout(HLayout);
    }
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(onPushOk()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), SLOT(closeClicked()));
}

settingsDialog::~settingsDialog()
{
    delete ui;
}

void settingsDialog::closeClicked() {
    delete this;
}

void settingsDialog::onPushOk() {
    emit afterOkPushed(&lines);
    close();
}
