//
// Created by alber on 17/06/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MonkeyWGridTtem.h" resolved

#include <iostream>

#include "gui/MonkeyWGridItem.hpp"
#include "ui_MonkeyWGridItem.h"


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

    if (model.getFav() == 1)
    {
        _ui->favCheck->setChecked(true);
    }

    connect(_ui->favCheck, &QCheckBox::clicked, this, [this, &model]{switchFavState(model);});
}

MonkeyWGridItem::~MonkeyWGridItem() {
    delete _ui;
}

void MonkeyWGridItem::switchFavState(MonkeyModel &model)
{
    model.setFavStatus(!model.getFav());
    std::cout << model.getFav() << std::endl;
}