/*
 *  File:           MonkeySWPage.cpp
 *  Created:        Albert 17/06/2024
 *  Description:
*/

#include "MonkeyWindow.hpp"
#include <ui_MonkeyWindow.h>


void MonkeyWindow::loadStopWatch()
{
    loadModelCombo();
    if (_selectedModel)
    {
        connect(&_timer, &QTimer::timeout, this, &MonkeyWindow::updateStopWatch);
        connect(_ui->startWatch, &QPushButton::clicked, this, [this] {startButton();});
        connect(_ui->stopWatch, &QPushButton::clicked, this, [this] {stopButton();});
    }
}

void MonkeyWindow::loadModelCombo()
{
    for (auto model : _collection.getModels())
        _ui->modelCombo->addItem(QString::fromStdString(model.getName()));
    if (_collection.getModels().size() > 0)
        _selectedModel = &_collection.getModelsAdr().at(_ui->modelCombo->currentIndex());
    connect(_ui->modelCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MonkeyWindow::comboModelChange);
}

void MonkeyWindow::comboModelChange(int index)
{
    _selectedModel = &_collection.getModelsAdr().at(_ui->modelCombo->currentIndex());
    connect(&_timer, &QTimer::timeout, this, &MonkeyWindow::updateStopWatch);
    connect(_ui->startWatch, &QPushButton::clicked, this, [this] {startButton();});
    connect(_ui->stopWatch, &QPushButton::clicked, this, [this] {stopButton();});
}

void MonkeyWindow::updateStopWatch()
{
    if (_selectedModel->isSWOn())
    {
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _selectedModel->getLastSession()->getStart().getC());
        auto hours = std::chrono::duration_cast<std::chrono::hours>(elapsedTime);
        elapsedTime -= std::chrono::duration_cast<std::chrono::seconds>(hours);
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsedTime);
        elapsedTime -= std::chrono::duration_cast<std::chrono::seconds>(minutes);
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsedTime);
        _ui->hoursLCD->display(static_cast<int>(hours.count()));
        _ui->minutesLCD->display(static_cast<int>(minutes.count()));
        _ui->secondsLCD->display(static_cast<int>(seconds.count()));
    }
}

void MonkeyWindow::startButton()
{
    if (!_selectedModel->isSWOn())
    {
        _selectedModel->startSession();
        _timer.start(1);
        updateStopWatch();
    }
}

void MonkeyWindow::stopButton()
{
    _selectedModel->stopSession();
    updateStopWatch();
    loadHome();
    loadCollection();
}