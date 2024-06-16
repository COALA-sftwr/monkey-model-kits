/*
 *  File:           MonkeyWItem.cpp
 *  Created:        Albert 15/06/2024
 *  Description:    File for Monkey Favorite Widget Items
*/

// You may need to build the project (run Qt uic code generator) to get "ui_MonkeyWItem.h" resolved

#include "../../include/gui/MonkeyWItem.hpp"
#include "ui_MonkeyWItem.h"


MonkeyWidgetItem::MonkeyWidgetItem(QWidget *parent) :
    QWidget(parent), ui(new Ui::MonkeyWidgetItem) {
    ui->setupUi(this);
}

MonkeyWidgetItem::~MonkeyWidgetItem() {
    delete ui;
}
