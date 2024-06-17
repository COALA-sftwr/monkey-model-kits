//
// Created by alber on 17/06/2024.
//

#ifndef MONKEYWGRIDTTEM_H
#define MONKEYWGRIDTTEM_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MonkeyWGridItem; }
QT_END_NAMESPACE

class MonkeyWGridItem : public QWidget {
Q_OBJECT

public:
    explicit MonkeyWGridItem(QWidget *parent = nullptr);
    ~MonkeyWGridItem() override;

private:
    Ui::MonkeyWGridItem *ui;
};


#endif //MONKEYWGRIDTTEM_H
