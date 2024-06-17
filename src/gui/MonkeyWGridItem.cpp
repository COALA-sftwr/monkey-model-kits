//
// Created by alber on 17/06/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MonkeyWGridTtem.h" resolved

#include "gui/MonkeyWGridTtem.hpp"
#include "ui_MonkeyWGridTtem.h"


MonkeyWGridItem::MonkeyWGridItem(QWidget *parent) :
    QWidget(parent), ui(new Ui::MonkeyWGridItem) {
    ui->setupUi(this);
}

MonkeyWGridItem::~MonkeyWGridItem() {
    delete ui;
}
