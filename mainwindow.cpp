#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include <QMetaObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new QAction("settings");
    remove = new QAction("remove");
    rotate = new QAction("rotate");
    settings->setIcon(QIcon(":res/icons/settings.png"));
    remove->setIcon(QIcon(":res/icons/basket.png"));
    rotate->setIcon(QIcon(":res/icons/rotation.png"));

    ui->toolBar->addAction(settings);
    ui->toolBar->addAction(remove);
    ui->toolBar->addAction(rotate);

    settings->setEnabled(false);
    remove->setEnabled(false);
    rotate->setEnabled(false);

    scene = new CustomScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    connect(ui->addBattery, SIGNAL(clicked()), this, SLOT(onPushBattery()));
    connect(ui->addResistor, SIGNAL(clicked()), this, SLOT(onPushResistor()));
    connect(ui->addWire, SIGNAL(clicked()), this, SLOT(onPushWire()));
    connect(ui->startButton, SIGNAL(clicked()), SLOT(onPushStart()));
    connect(settings, SIGNAL(triggered()), this, SLOT(settingsButton()));
    connect(remove, SIGNAL(triggered()), SLOT(deleteButton()));
    connect(rotate, SIGNAL(triggered()), SLOT(rotateButton()));
    connect(scene, SIGNAL(resetEl()), SLOT(resetSelectedEl()));

    scene->setSceneRect(0,0,1000,1000);

    for(auto i = 0; i < 41; ++i){
        for(auto j = 0; j < 41; ++j) {
            scene->addEllipse(i*25, j*25, 1, 1);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPushBattery() {
    scene->setTypeElement(CustomScene::BatteryType);
    scene->setPreviousPosition(QPointF(0,0));
    scene->setNextPosition(QPointF(0,0));
}

void MainWindow::onPushResistor() {
    scene->setTypeElement(CustomScene::ResistorType);
    scene->setPreviousPosition(QPointF(0,0));
    scene->setNextPosition(QPointF(0,0));
}

void MainWindow::onPushWire() {
    scene->setTypeElement(CustomScene::WireType);
    scene->setPreviousPosition(QPointF(0,0));
    scene->setNextPosition(QPointF(0,0));
}

void MainWindow::elementSelected(QGraphicsItem *el) {
    qDebug() << "done";
    remove->setEnabled(true);
    if (dynamic_cast<Element*>(el) != nullptr) {
        settings->setEnabled(true);
        rotate->setEnabled(true);
    }
    selectedEl = el;
}

void MainWindow::deleteButton() {
    settings->setEnabled(false);
    remove->setEnabled(false);
    rotate->setEnabled(false);
    if (selectedEl) {
        delete selectedEl;
        selectedEl = nullptr;
    }
}

void MainWindow::settingsButton() {
    qDebug() << "settings";
    QObject *selectedObj = dynamic_cast<QObject*>(selectedEl);
    settingsDialog *dialog = new settingsDialog(this, selectedObj);
    connect(dialog, SIGNAL(afterOkPushed(QHash<const char *, QLineEdit*>*)), this, SLOT(settingsOkPushed(QHash<const char *, QLineEdit*> *)));
    dialog->show();
}

void MainWindow::rotateButton() {
    if (selectedEl) {
        selectedEl->setRotation(selectedEl->rotation() == 0 ? -90 : 0);
        selectedEl->update();
    }
}

void MainWindow::settingsOkPushed(QHash<const char *, QLineEdit*> *params) {
    QObject *selectedObj = dynamic_cast<QObject*>(selectedEl);
    foreach (const char *key, params->keys()) {
        qDebug() << key;
        qDebug() << params->value(key)->text().toInt();
        selectedObj->setProperty(key, params->value(key)->text().toInt());
    }
    qDebug() << "colour changed";
    selectedEl->update();
}

void MainWindow::resetSelectedEl() {
    if (selectedEl != nullptr) {
        Element *el = dynamic_cast<Element*>(selectedEl);
        if (el != nullptr) {
            el->setIsSelected(false);
        }
    }
    selectedEl = nullptr;
    settings->setEnabled(false);
    remove->setEnabled(false);
    rotate->setEnabled(false);
}

void MainWindow::onPushStart() {
    qDebug() << scene->items().length();
}
