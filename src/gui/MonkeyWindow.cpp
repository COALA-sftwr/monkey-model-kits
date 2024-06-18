/*
 *  File:           MonkeyWindow.cpp
 *  Created:        Albert 05/05/2024
 *  Description:    File for the Window of the app
*/

#include "MonkeyWindow.hpp"
#include "MonkeyManager.hpp"
#include <QFileDialog>
#include <ui_MonkeyWindow.h>

MonkeyWindow::MonkeyWindow(QWidget *parent) :
    QMainWindow(parent), _ui(new Ui::MonkeyWindow) {
    _ui->setupUi(this);
    _ui->stackedWidget->setCurrentIndex(0);
    _ui->modelSearch->hide();

    loadButtons();
    connect(_ui->actionOuvrir, &QAction::triggered, this, &MonkeyWindow::openFile);
    connect(_ui->actionSauvegarder, &QAction::triggered, this, &MonkeyWindow::saveFile);
}

MonkeyWindow::~MonkeyWindow() {
    delete _ui;
}

void MonkeyWindow::openFileStart(std::string fileName)
{
    _manager.setFilePath(fileName);

    if (!_manager.getFilePath().empty()){
        _manager.openFile(_manager.getFilePath(), _collection);
        loadFile();
    }
}

void MonkeyWindow::loadButtons()
{
    connect(_ui->HomeButton, &QPushButton::clicked, this, [=] {_ui->stackedWidget->setCurrentIndex(0); _ui->pageLabel->setText("Accueil"); _ui->pageLabel->show();});
    connect(_ui->CollectionButton, &QPushButton::clicked, this, [=] {_ui->stackedWidget->setCurrentIndex(1); _ui->pageLabel->setText("Collection"); _ui->pageLabel->show();});
    connect(_ui->StopWatchButton, &QPushButton::clicked, this, [=] {_ui->stackedWidget->setCurrentIndex(2); _ui->pageLabel->setText("Chronomètre"); _ui->pageLabel->show();});
    connect(_ui->StatisticsButton, &QPushButton::clicked, this, [=] {_ui->stackedWidget->setCurrentIndex(3); _ui->pageLabel->setText("Statistiques"); _ui->pageLabel->show();});
}

void MonkeyWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                QDir::homePath().append("/Documents/kits"),
                                                tr("All Files (*)"));
    std::filesystem::path filePath = fileName.toStdString();
    _manager.openFile(filePath, _collection);
    loadFile();
}

void MonkeyWindow::loadFile() {
    loadHome();
    loadCollection();
    loadStopWatch();
    // loadStatistics();
}

void MonkeyWindow::saveFile()
{
    _manager.saveFile(_collection);
}

void selectButton()
{
    // _ui->HomeButton->setStyleSheet("QPushButton {border-color: #646464;; border-radius: 15px; background-color: #505050;}");
}