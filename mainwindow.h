#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QAction>
#include "customscene.h"
#include "element.h"
#include "settingsdialog.h"
#include "resistor.h"
#include "battery.h"
#include <QHash>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPushBattery();
    void onPushResistor();
    void onPushWire();
    void onPushStart();
    void onPushCapacitor();
    void onPushInductor();
    void elementSelected(QGraphicsItem *el);
    void deleteButton();
    void settingsButton();
    void rotateButton();
    void settingsOkPushed(QHash<const char *, QLineEdit*> *params);
    void resetSelectedEl();

signals:

private:
    int m_typeElement;
    Ui::MainWindow *ui;
    CustomScene *scene;
    QAction *settings;
    QAction *remove;
    QAction *rotate;
    settingsDialog *dialog;
    QGraphicsItem *selectedEl = nullptr;
};
#endif // MAINWINDOW_H
