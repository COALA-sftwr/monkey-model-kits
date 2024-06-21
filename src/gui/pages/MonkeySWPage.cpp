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
        connect(_ui->startWatch, &QPushButton::clicked, this, [this] {_selectedModel->startSession();});
        connect(_ui->stopWatch, &QPushButton::clicked, this, [this] {_selectedModel->stopSession();});
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
    connect(_ui->startWatch, &QPushButton::clicked, this, [this] {_selectedModel->startSession();});
    connect(_ui->stopWatch, &QPushButton::clicked, this, [this] {_selectedModel->stopSession(); loadLastModel();});
}