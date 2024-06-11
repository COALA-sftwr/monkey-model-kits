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
    _ui->stackedWidget->setCurrentIndex(0);
    _ui->pageLabel->hide();

    loadButtons();

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

void MonkeyWindow::updateTimeLabel(MonkeySession *session) {
    auto duration = session->getDuration();

    int hours = duration.count() / 3600;
    int minutes = (duration.count() % 3600) / 60;
    int secs = duration.count() % 60;

    // Update the QLabel text with the formatted duration
    _ui->lastTimeLabel->setText(QString("%1:%2:%3").arg(hours, 2, 10, QChar('0'))
                                       .arg(minutes, 2, 10, QChar('0'))
                                       .arg(secs, 2, 10, QChar('0')));
}

void MonkeyWindow::loadLastModel() {
    MonkeyModel *tempModel = _collection.findLastModel();

    _ui->lastNameLabel->setText(QString::fromStdString(tempModel->getName()));
    _ui->lastGradeLabel->setText(QString::fromStdString(etos(gradeMap, tempModel->getGrade())));
    _ui->lastSessionsLabel->setText(QString::number(tempModel->getNSessions()));
    updateTimeLabel(tempModel->getLastSession());
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

void MonkeyWindow::loadButtons()
{
    connect(_ui->HomeButton, &QPushButton::clicked, this, [=]() {_ui->stackedWidget->setCurrentIndex(0); _ui->pageLabel->hide();});
    connect(_ui->CollectionButton, &QPushButton::clicked, this, [=]() {_ui->stackedWidget->setCurrentIndex(1); _ui->pageLabel->setText("Collection"); _ui->pageLabel->show();});
    connect(_ui->StopWatchButton, &QPushButton::clicked, this, [=]() {_ui->stackedWidget->setCurrentIndex(2); _ui->pageLabel->setText("Chronomètre"); _ui->pageLabel->show();});
    connect(_ui->StatisticsButton, &QPushButton::clicked, this, [=]() {_ui->stackedWidget->setCurrentIndex(3); _ui->pageLabel->setText("Statistiques"); _ui->pageLabel->show();});
}
