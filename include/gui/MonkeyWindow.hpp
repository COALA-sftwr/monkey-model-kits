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
    MonkeyModel* _selectedModel = nullptr;

public:
    explicit MonkeyWindow(QWidget *parent = nullptr);
    ~MonkeyWindow() override;

    void openFileStart(std::string fileName);

    // File handling functions.
    void openFile();
    void loadButtons();
    void onSwitchWidgetButtonClicked(int buttonIndex);
    void loadFile();
    void saveFile();

    void loadFavorites();
    // Tab loading functions.
    void loadHome();

    void updateTimeLabel(MonkeySession *session);

    void loadCollection();
    void showForm();
    void loadModelCombo();
    void comboModelChange(int index);
    void loadStopWatch();
    void loadStatistics();

    // Home Loading functions.
    void loadLastModel();
};

