//
// Created by alber on 18/06/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MonkeyNewModel.h" resolved

#include "gui/MonkeyNewModel.hpp"
#include "ui_MonkeyNewModel.h"


MonkeyNewModel::MonkeyNewModel(QWidget *parent) :
    QDialog(parent), _ui(new Ui::MonkeyNewModel)
{
    _ui->setupUi(this);
    setWindowTitle("Nouvelle maquette");
    connect(_ui->buttonBox, &QDialogButtonBox::accepted, this, &MonkeyNewModel::accept);
    connect(_ui->buttonBox, &QDialogButtonBox::rejected, this, &MonkeyNewModel::reject);
}

MonkeyNewModel::~MonkeyNewModel() {
    delete _ui;
}

std::string MonkeyNewModel::getName()
{
    return _ui->nameLine->text().toStdString();
}

Grade MonkeyNewModel::getGrade()
{
    return stoe(_ui->gradeCombo->currentText().toStdString(), gradeMap);
}

Status MonkeyNewModel::getStatus()
{
    return static_cast<Status>(_ui->statusCombo->currentData().toInt());
    // return stoe(_ui->statusCombo->currentText().toStdString(), statusMap);
}

double MonkeyNewModel::getPrice()
{
    return _ui->priceSpinBox->text().toDouble();
}
