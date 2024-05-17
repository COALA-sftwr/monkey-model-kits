/*
 *  File:       MonkeyWindow.hpp
 *  Created:    Albert 05/05/2024
 *  Description:
*/

#pragma once

#include <QMainWindow>
#include <QAction>
#include <QMenu>

#include "MonkeyCollection.hpp"
#include "MonkeyManager.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MonkeyWindow; }
QT_END_NAMESPACE

class MonkeyWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MonkeyWindow *_ui;
    MonkeyCollection _collection;
    MonkeyManager _manager;

public:
    explicit MonkeyWindow(QWidget *parent = nullptr);
    ~MonkeyWindow() override;

    // File handling functions.
    void openFile();
    void loadFile();

    // Tab loading functions.
    void loadHome();

    void updateTimeLabel(MonkeySession *session);

    void loadCollection();
    void loadChronometer();
    void loadStatistics();

    // Home Loading functions.
    void loadLastModel();
};

