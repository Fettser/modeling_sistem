#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QPushButton>
#include <QMetaProperty>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QComboBox>

settingsDialog::settingsDialog(QWidget *parent, QObject *selectedEl) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    const QMetaObject *metaObj= selectedEl->metaObject();
    const QList<QString> prefixes = {"p", "n", "μ", "m", "", "k", "M"};
    for (int i = metaObj->propertyOffset(); i < metaObj->propertyCount(); i++) {
        QMetaProperty prop = metaObj->property(i);
        const char *name = prop.name();
        QHBoxLayout *HLayout = new QHBoxLayout;
        QLabel *label = new QLabel(QString(prop.name()) + ":");
        QLineEdit *line = new QLineEdit(selectedEl->property(name).toString().split(" ")[0]);
        QComboBox *box = new QComboBox;
        QString unit = selectedEl->property(name).toString().split(" ")[1];
        int idx = 0;
        for (int i = unit.length() - 1; i >= 0; i--) {
            if (unit[i] > 'A' && unit[i] < 'Z') {
                idx = i;
                break;
            }
        }
        foreach(const QString prefix, prefixes) {
            box->addItem(prefix + unit.mid(idx));
        }
        int currValue = (idx > 0) ? prefixes.indexOf(selectedEl->property(name).toString().split(" ")[1][0]) : 4;
        box->setCurrentIndex(currValue);
        line->setValidator(new QRegularExpressionValidator(QRegularExpression("[1-9][0-9]{1}"),line));
        lines[name] = line;
        boxes[name] = box;
        HLayout->addWidget(label);
        HLayout->addWidget(line);
        HLayout->addWidget(box);
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
    close();
}

void settingsDialog::onPushOk() {
    emit afterOkPushed(&lines, &boxes);
    close();
}
