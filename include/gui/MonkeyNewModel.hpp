//
// Created by alber on 18/06/2024.
//

#ifndef MONKEYNEWMODEL_H
#define MONKEYNEWMODEL_H

#include <QDialog>

#include "MonkeyModel.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MonkeyNewModel; }
QT_END_NAMESPACE

class MonkeyNewModel : public QDialog {
Q_OBJECT

public:
    explicit MonkeyNewModel(QWidget *parent = nullptr);
    ~MonkeyNewModel() override;

    std::string getName();
    Grade getGrade();
    Status getStatus();
    double getPrice();

private:
    Ui::MonkeyNewModel *_ui;
    QString _name;
    Grade _grade;
    Status _status;
    double _price;
};


#endif //MONKEYNEWMODEL_H
