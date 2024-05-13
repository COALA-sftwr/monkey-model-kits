/*
 *  File:       MonkeyWindow.hpp
 *  Created:    Albert 05/05/2024
 *  Description:
*/

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MonkeyWindow; }
QT_END_NAMESPACE

class MonkeyWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MonkeyWindow(QWidget *parent = nullptr);
    ~MonkeyWindow() override;

private:
    Ui::MonkeyWindow *ui;
};

