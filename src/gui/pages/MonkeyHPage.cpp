/*
 *  File:           MonkeyHPage.cpp
 *  Created:        Albert 17/06/2024
 *  Description:
*/

#include "MonkeyWindow.hpp"
#include "MonkeyWItem.hpp"
#include <ui_MonkeyWindow.h>


void MonkeyWindow::loadHome(){
    if (_collection.getModels().size() > 0)
    {
        loadLastModel();
        loadFavorites();
    }
}

void MonkeyWindow::loadLastModel() {
    MonkeyModel *tempModel = _collection.findLastModel();
    int emptyT = 0;

    _ui->lastNameLabel->setText(QString::fromStdString(tempModel->getName()));
    _ui->lastGradeLabel->setText(QString::fromStdString(etos(gradeMap, tempModel->getGrade())));
    _ui->lastSessionsLabel->setText(QString::number(tempModel->getNSessions()));

    if (tempModel->getSessions().size() == 0)
        updateTimeLabel(new MonkeySession(static_cast<std::chrono::duration<int>>(emptyT)));
    else
        updateTimeLabel(tempModel->getLastSession());
}

void MonkeyWindow::updateTimeLabel(MonkeySession *session) {
    auto duration = session->getDuration();

    int hours = duration.count() / 3600;
    int minutes = (duration.count() % 3600) / 60;
    int secs = duration.count() % 60;

    // Update the QLabel text with the formatted duration
    _ui->lastTimeLabel->setText(QString("%1:%2:%3").arg(hours, 2, 10, QChar('0'))
                                       .arg(minutes, 2, 10, QChar('0'))
                                       .arg(secs, 2, 10, QChar('0')));
}

void MonkeyWindow::loadFavorites()
{
    for (auto model : _collection.getModels())
    {
        if (model.getFav() == true)
        {
            _ui->favoritesLayout->addWidget(new MonkeyWidgetItem(model));
        }
    }
}