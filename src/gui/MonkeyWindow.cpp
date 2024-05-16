/*
 *  File:       MonkeyWindow.cpp
 *  Created:    Albert 05/05/2024
 *  Description:
*/
// You may need to build the project (run Qt uic code generator) to get "ui_MonkeyWindow.h" resolved

#include <QFileDialog>
#include "MonkeyWindow.hpp"

#include "MonkeyManager.hpp"
#include "ui_MonkeyWindow.h"

MonkeyWindow::MonkeyWindow(QWidget *parent) :
    QMainWindow(parent), _ui(new Ui::MonkeyWindow) {
    _ui->setupUi(this);

    connect(_ui->actionOuvrir, &QAction::triggered, this, &MonkeyWindow::openFile);
}

MonkeyWindow::~MonkeyWindow() {
    delete _ui;
}

void MonkeyWindow::loadFile() {
    loadHome();
    // loadCollection();
    // loadChronometer();
    // loadStatistics();
}

void MonkeyWindow::loadHome() {
    loadLastModel();
}

void MonkeyWindow::loadLastModel() {
    MonkeyModel *tempModel = _collection.findLastModel();

    _ui->lastNameLabel->setText(QString::fromStdString(tempModel->getName()));
}

void MonkeyWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                QDir::homePath().append("/Documents/kits"),
                                                tr("All Files (*)"));
    std::filesystem::path filePath = fileName.toStdString();
    _manager.openFile(filePath,_collection);
    loadFile();
}
