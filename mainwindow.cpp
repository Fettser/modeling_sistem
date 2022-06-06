#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "wire.h"
#include "capacitor.h"
#include "resistor.h"
#include "inductor.h"
#include "battery.h"
#include "switch.h"
#include <QMetaObject>
#include <QMetaProperty>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    msgBox = new QMessageBox;
    msgBox->setText("Are you sure? Current scheme hasn`t been saved.");
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

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
    connect(ui->addCapacitor, SIGNAL(clicked()), this, SLOT(onPushCapacitor()));
    connect(ui->addInductor, SIGNAL(clicked()), this, SLOT(onPushInductor()));
    connect(ui->addSwitch, SIGNAL(clicked()), this, SLOT(onPushSwitch()));
    connect(settings, SIGNAL(triggered()), this, SLOT(settingsButton()));
    connect(remove, SIGNAL(triggered()), SLOT(deleteButton()));
    connect(rotate, SIGNAL(triggered()), SLOT(rotateButton()));
    connect(scene, SIGNAL(resetEl()), SLOT(resetSelectedEl()));
    connect(ui->actionSave, SIGNAL(triggered()), SLOT(onSaveButton()));
    connect(ui->actionOpen, SIGNAL(triggered()), SLOT(onOpenButton()));
    connect(ui->actionSave_SVG, SIGNAL(triggered()), SLOT(onSaveSVGButton()));
    connect(ui->actionNew, SIGNAL(triggered()), SLOT(onClearScene()));

    scene->setSceneRect(0,0,1000,1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClearScene() {
    scene->clear();
}

void MainWindow::onPushBattery() {
    scene->setTypeElement(CustomScene::BatteryType);
    scene->setPreviousPosition(QPointF(0,0));
    scene->setNextPosition(QPointF(0,0));
}

void MainWindow::onPushSwitch() {
    scene->setTypeElement(CustomScene::SwitchType);
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

void MainWindow::onPushCapacitor() {
    scene->setTypeElement(CustomScene::CapacitorType);
    scene->setPreviousPosition(QPointF(0,0));
    scene->setNextPosition(QPointF(0,0));
}

void MainWindow::onPushInductor() {
    scene->setTypeElement(CustomScene::InductorType);
    scene->setPreviousPosition(QPointF(0,0));
    scene->setNextPosition(QPointF(0,0));
}

void MainWindow::elementSelected(QGraphicsItem *el) {
    remove->setEnabled(true);
    if (dynamic_cast<Element*>(el) != nullptr) {
        settings->setEnabled(true);
        rotate->setEnabled(true);
    }
    selectedEl = el;
}

void MainWindow::openFile() {
    scene->clear();

    QString openFileName = QFileDialog::getOpenFileName(this,
                                                            tr("Open Json File"),
                                                            QString(),
                                                            tr("JSON (*.json)"));
    QString fileValue;
    QFileInfo fileInfo(openFileName);
    QDir::setCurrent(fileInfo.path());
    QFile jsonFile(openFileName);

    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    fileValue = jsonFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileValue.toUtf8());
    QJsonObject json = doc.object();
    QJsonArray arr = json["objects"].toArray();
    for (int i = 0; i < arr.count(); i++) {
        QJsonObject item = arr.at(i).toObject();
        QString name = item.value("objectName").toString();
        if (name == "capacitor") {
            QJsonObject coords = item.value("coords").toObject();
            Capacitor *capacitor = new Capacitor(scene, item.value("capacity").toString());
            capacitor->setPos(coords.value("x").toInt(), coords.value("y").toInt());
            capacitor->setRotation(item.value("angle").toInt());
            connect(capacitor, SIGNAL(onSelectElement(QGraphicsItem*)), this, SLOT(elementSelected(QGraphicsItem*)));
            scene->addItem(capacitor);
        }
        if (name == "resistor") {
            QJsonObject coords = item.value("coords").toObject();
            Resistor *resistor = new Resistor(scene, item.value("resistance").toString());
            resistor->setPos(coords.value("x").toInt(), coords.value("y").toInt());
            resistor->setRotation(item.value("angle").toInt());
            connect(resistor, SIGNAL(onSelectElement(QGraphicsItem*)), this, SLOT(elementSelected(QGraphicsItem*)));
            scene->addItem(resistor);
        }
        if (name == "inductor") {
            QJsonObject coords = item.value("coords").toObject();
            Inductor *inductor = new Inductor(scene, item.value("inductance").toString());
            inductor->setPos(coords.value("x").toInt(), coords.value("y").toInt());
            inductor->setRotation(item.value("angle").toInt());
            connect(inductor, SIGNAL(onSelectElement(QGraphicsItem*)), this, SLOT(elementSelected(QGraphicsItem*)));
            scene->addItem(inductor);
        }
        if (name == "battery") {
            QJsonObject coords = item.value("coords").toObject();
            Battery *battery = new Battery(scene, item.value("voltage").toString(), item.value("resistance").toString());
            battery->setPos(coords.value("x").toInt(), coords.value("y").toInt());
            battery->setRotation(item.value("angle").toInt());
            connect(battery, SIGNAL(onSelectElement(QGraphicsItem*)), this, SLOT(elementSelected(QGraphicsItem*)));
            scene->addItem(battery);
        }
        if (name == "switch") {
            QJsonObject coords = item.value("coords").toObject();
            Switch *my_switch= new Switch(scene);
            my_switch->setPos(coords.value("x").toInt(), coords.value("y").toInt());
            my_switch->setRotation(item.value("angle").toInt());
            connect(my_switch, SIGNAL(onSelectElement(QGraphicsItem*)), this, SLOT(elementSelected(QGraphicsItem*)));
            scene->addItem(my_switch);
        }
        if (name == "wire") {
            QJsonObject firstPoint = item.value("firstPoint").toObject();
            QJsonObject secondPoint = item.value("secondPoint").toObject();
            Wire *line = new Wire(this, QPointF(firstPoint.value("x").toInt(), firstPoint.value("y").toInt()), QPointF(secondPoint.value("x").toInt(), secondPoint.value("y").toInt()));
            connect(line, SIGNAL(onSelectElement(QGraphicsItem*)), this, SLOT(elementSelected(QGraphicsItem*)));
            line->setPen(QPen(Qt::black, 4, Qt::SolidLine));
            line->setLine(QLineF(QPointF(firstPoint.value("x").toInt(), firstPoint.value("y").toInt()), QPointF(secondPoint.value("x").toInt(), secondPoint.value("y").toInt())));
            scene->addItem(line);
            line->setFirstPoint(QPointF(firstPoint.value("x").toInt(), firstPoint.value("y").toInt()));
            line->setSecondPoint(QPointF(secondPoint.value("x").toInt(), secondPoint.value("y").toInt()));
        }
    }
}

void MainWindow::onOpenButton() {
    int ret = msgBox->exec();

    switch (ret) {
        case QMessageBox::Ok: {
            openFile();           
            break;
        }
        case QMessageBox::Cancel: {
            break;
        }
        default: {           
            break;
        }
    }

}

void MainWindow::onSaveButton() {
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                            tr("Save Json File"),
                                                            QString(),
                                                            tr("JSON (*.json)"));

    QFileInfo fileInfo(saveFileName);
    QDir::setCurrent(fileInfo.path());
    QFile jsonFile(saveFileName);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }
    QJsonArray list;
    foreach(QGraphicsItem *item, scene->items()) {
        if (dynamic_cast<Element*>(item)) {
            QJsonObject coords;
            coords["x"] = item->pos().x();
            coords["y"] = item->pos().y();
            QObject *object = dynamic_cast<QObject*>(item);
            const QMetaObject *metaobject = object->metaObject();
            int count = metaobject->propertyCount();
            QVariantMap map;
            for (int i=0; i<count; ++i) {
                QMetaProperty metaproperty = metaobject->property(i);
                const char *name = metaproperty.name();
                QVariant value = object->property(name);
                if (!value.toPointF().isNull()) {
                    QPointF val = value.toPointF();
                    QJsonObject point;
                    point["x"] = val.x();
                    point["y"] = val.y();
                    map.insert(metaproperty.name(), point);
                } else {
                    map.insert(metaproperty.name(), value);
                }
            }
            map.insert("coords", coords);
            list.append(QJsonValue(QJsonObject::fromVariantMap(map)));
        }

        if (dynamic_cast<Wire*>(item)) {
            QObject *object = dynamic_cast<QObject*>(item);
            const QMetaObject *metaobject = object->metaObject();
            int count = metaobject->propertyCount();
            QVariantMap map;
            for (int i=0; i<count; ++i) {
                QMetaProperty metaproperty = metaobject->property(i);
                const char *name = metaproperty.name();
                QVariant value = object->property(name);
                if (!value.toPointF().isNull()) {
                    QPointF val = value.toPointF();
                    QJsonObject point;
                    point["x"] = val.x();
                    point["y"] = val.y();
                    map.insert(metaproperty.name(), point);
                } else {
                    map.insert(metaproperty.name(), value);
                }
            }
            list.append(QJsonValue(QJsonObject::fromVariantMap(map)));
        }
    }
    QJsonObject objects;
    objects["objects"] = list;
    jsonFile.write(QJsonDocument(objects).toJson());
    jsonFile.close();
}

void MainWindow::onSaveSVGButton() {
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
            path, tr("SVG files (*.svg)"));

        if (newPath.isEmpty())
            return;

        path = newPath;

        QSvgGenerator generator;
        generator.setFileName(path);
        generator.setSize(QSize(scene->width(), scene->height()));
        generator.setViewBox(QRect(0, 0, scene->width(), scene->height()));
        generator.setTitle(tr("SVG Example"));
        generator.setDescription(tr("File created by SVG Example"));

        QPainter painter;
        painter.begin(&generator);
        scene->render(&painter);
        painter.end();
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
    QObject *selectedObj = dynamic_cast<QObject*>(selectedEl);
    settingsDialog *dialog = new settingsDialog(this, selectedObj);
    connect(dialog, SIGNAL(afterOkPushed(QHash<const char *, QLineEdit*>*, QHash<const char *, QComboBox*>*)), this, SLOT(settingsOkPushed(QHash<const char *, QLineEdit*>*, QHash<const char *, QComboBox*>*)));
    dialog->show();
}

void MainWindow::rotateButton() {
    if (selectedEl) {
        selectedEl->setRotation(selectedEl->rotation() == 0 ? -90 : 0);
        dynamic_cast<Element*>(selectedEl)->setAngle(selectedEl->rotation());
        selectedEl->update();
    }
}

void MainWindow::settingsOkPushed(QHash<const char *, QLineEdit*> *lines, QHash<const char *, QComboBox*> *boxes) {
    QObject *selectedObj = dynamic_cast<QObject*>(selectedEl);
    foreach (const char *key, lines->keys()) {
        QString value = lines->value(key)->text() == "" ? selectedObj->property(key).toString().split(" ")[0] : lines->value(key)->text();
        QString param = value + " " + boxes->value(key)->currentText();
        selectedObj->setProperty(key, param);
    }
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
