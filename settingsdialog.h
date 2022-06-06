#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QColor>
#include <QLineEdit>
#include <QHash>
#include <QComboBox>

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
    void afterOkPushed(QHash<const char *, QLineEdit*> *lines, QHash<const char *, QComboBox*> *boxes);

private slots:
    void onPushOk();
    void closeClicked();

private:
    Ui::settingsDialog *ui;
    void cancelPushed();
    QColor *color;
    QHash<const char *, QLineEdit*> lines;
    QHash<const char *, QComboBox*> boxes;
};

#endif // SETTINGSDIALOG_H
