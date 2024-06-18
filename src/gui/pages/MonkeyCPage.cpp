/*
 *  File:           MonkeyCPage.cpp
 *  Created:        Albert 17/06/2024
 *  Description:
*/

#include "MonkeyWindow.hpp"
#include "MonkeyWGridTtem.hpp"
#include <ui_MonkeyWindow.h>


/*void MonkeyWindow::loadCollection()
{
    int modelIndex = 0;

    for (int j = 0; j != _collection.getModels().size()/3 ;j++)
    {
        for (int i = 0; i != 3; i++, modelIndex++)
        {
            _ui->gridLayout->addWidget(new MonkeyWGridItem(_collection.getModels().at(modelIndex)), j, i, Qt::AlignTop);
        }
    }
}*/

/*void MonkeyWindow::loadCollection()
{
    int nModels = _collection.getModels().size();
    int nRows = (nModels + 2) / 3;
    int nColumns;
}*/

void MonkeyWindow::loadCollection() {
    int numModels = _collection.getModels().size();
    int numRows = (numModels + 2) / 3; // Ensure at least one row

    for (int j = 0; j < numRows; j++) {
        for (int i = 0; i < 3; i++) {
            int modelIndex = j * 3 + i;
            if (modelIndex < numModels) {
                _ui->gridLayout->addWidget(new MonkeyWGridItem(_collection.getModels().at(modelIndex)), j, i, Qt::AlignTop);
            }
        }
    }
}