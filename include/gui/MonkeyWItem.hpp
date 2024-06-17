//
// Created by alber on 16/06/2024.
//

#ifndef MONKEYWITEM_H
#define MONKEYWITEM_H

#include "MonkeyWindow.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MonkeyWidgetItem; }
QT_END_NAMESPACE

class MonkeyWidgetItem : public QWidget {
Q_OBJECT

public:
    MonkeyWidgetItem(QWidget *parent = nullptr);
    MonkeyWidgetItem(MonkeyModel& model);
    ~MonkeyWidgetItem() override;

private:
    Ui::MonkeyWidgetItem *_ui;
};


#endif //MONKEYWITEM_H
