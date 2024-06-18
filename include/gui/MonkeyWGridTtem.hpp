//
// Created by alber on 17/06/2024.
//

#ifndef MONKEYWGRIDTTEM_H
#define MONKEYWGRIDTTEM_H

#include "MonkeyWindow.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MonkeyWGridItem; }
QT_END_NAMESPACE

class MonkeyWGridItem : public QWidget {
Q_OBJECT

public:
    MonkeyWGridItem(QWidget *parent = nullptr);
    MonkeyWGridItem(MonkeyModel& model);
    ~MonkeyWGridItem() override;

private:
    Ui::MonkeyWGridItem *_ui;
};


#endif //MONKEYWGRIDTTEM_H
