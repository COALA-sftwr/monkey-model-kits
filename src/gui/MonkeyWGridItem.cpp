//
// Created by alber on 17/06/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MonkeyWGridTtem.h" resolved

#include "gui/MonkeyWGridTtem.hpp"
#include "ui_MonkeyWGridTtem.h"


MonkeyWGridItem::MonkeyWGridItem(QWidget *parent) :
    QWidget(parent), _ui(new Ui::MonkeyWGridItem) {
    _ui->setupUi(this);
}

MonkeyWGridItem::MonkeyWGridItem(MonkeyModel& model) :
    _ui(new Ui::MonkeyWGridItem())
{
    std::string priceString = std::to_string(model.getPrice());

    priceString.resize(priceString.find('.') + 3, '0');
    _ui->setupUi(this);
    _ui->nameLabel->setText(model.getName().data());
    _ui->gradeVL->setText(etos(gradeMap, model.getGrade()).data());
    _ui->sessionsVL->setText(std::to_string(model.getSessions().size()).data());
    _ui->priceVL->setText(priceString.data());
    _ui->timeVL->setText(model.getFormattedTime().data());
}

MonkeyWGridItem::~MonkeyWGridItem() {
    delete _ui;
}
