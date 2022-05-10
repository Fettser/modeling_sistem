#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QColor>
#include <QLineEdit>
#include <QHash>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingsDialog(QWidget *parent = nullptr, QObject *selectedEl = nullptr);
    ~settingsDialog();

signals:
    void onPushCancel();
    void afterOkPushed(QHash<const char *, QLineEdit*> *params);
private slots:
    void onPushOk();
    void closeClicked();

private:
    Ui::settingsDialog *ui;
    void cancelPushed();
    QColor *color;
    QHash<const char *, QLineEdit*> lines;
};

#endif // SETTINGSDIALOG_H
