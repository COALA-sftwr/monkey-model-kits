//
// Created by alber on 16/06/2024.
//

#ifndef MONKEYWITEM_H
#define MONKEYWITEM_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MonkeyWidgetItem; }
QT_END_NAMESPACE

class MonkeyWidgetItem : public QWidget {
Q_OBJECT

public:
    explicit MonkeyWidgetItem(QWidget *parent = nullptr);
    ~MonkeyWidgetItem() override;

private:
    Ui::MonkeyWidgetItem *ui;
};


#endif //MONKEYWITEM_H
