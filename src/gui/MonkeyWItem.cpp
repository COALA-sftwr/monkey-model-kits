/*
 *  File:           MonkeyWItem.cpp
 *  Created:        Albert 15/06/2024
 *  Description:    File for Monkey Favorite Widget Items
*/

// You may need to build the project (run Qt uic code generator) to get "ui_MonkeyWItem.h" resolved

#include "gui/MonkeyWItem.hpp"
#include "ui_MonkeyWItem.h"


MonkeyWidgetItem::MonkeyWidgetItem(QWidget *parent) :
    QWidget(parent), _ui(new Ui::MonkeyWidgetItem) {
    _ui->setupUi(this);
}

MonkeyWidgetItem::MonkeyWidgetItem(MonkeyModel& model) :
    _ui(new Ui::MonkeyWidgetItem())
{
    std::string priceString = std::to_string(model.getPrice());

    priceString.resize(priceString.find('.') + 3, '0');
    _ui->setupUi(this);
    _ui->nameLabel->setText(model.getName().data());
    _ui->gradeLabel->setText(etos(gradeMap, model.getGrade()).data());
    _ui->sessionsLabel->setText(std::to_string(model.getSessions().size()).data());
    _ui->priceLabel->setText(priceString.data());
    _ui->timeLabel->setText(model.getFormattedTime().data());
    // Todo: add function for listing all sessions of the model.
}

MonkeyWidgetItem::~MonkeyWidgetItem() {
    delete _ui;
}
