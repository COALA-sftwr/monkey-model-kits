/*
 *  File:       MonkeyWindow.cpp
 *  Created:    Albert 05/05/2024
 *  Description:
*/
// You may need to build the project (run Qt uic code generator) to get "ui_MonkeyWindow.h" resolved

#include "MonkeyWindow.hpp"
#include "ui_MonkeyWindow.h"

MonkeyWindow::MonkeyWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MonkeyWindow) {
    ui->setupUi(this);
}

MonkeyWindow::~MonkeyWindow() {
    delete ui;
}

