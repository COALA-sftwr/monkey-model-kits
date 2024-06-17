/*
 *  File:           MonkeySWPage.cpp
 *  Created:        Albert 17/06/2024
 *  Description:
*/

#include "MonkeyWindow.hpp"
#include <ui_MonkeyWindow.h>


void MonkeyWindow::loadStopWatch()
{
    connect(_ui->startWatch, &QPushButton::clicked, this, [this] {_selectedModel->startSession();});
    connect(_ui->stopWatch, &QPushButton::clicked, this, [this] {_selectedModel->stopSession();});
}
