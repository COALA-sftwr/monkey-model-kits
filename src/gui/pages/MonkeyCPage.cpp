/*
 *  File:           MonkeyCPage.cpp
 *  Created:        Albert 17/06/2024
 *  Description:
*/

#include "MonkeyWindow.hpp"
#include "MonkeyWGridTtem.hpp"
#include <ui_MonkeyWindow.h>


void MonkeyWindow::loadCollection()
{
    _ui->gridLayout->addWidget(new MonkeyWGridItem());
    _ui->gridLayout->addWidget(new MonkeyWGridItem());
}
