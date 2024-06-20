/*
 *  File:           MonkeyCPage.cpp
 *  Created:        Albert 17/06/2024
 *  Description:
*/

#include "MonkeyWindow.hpp"
#include "MonkeyWGridItem.hpp"
#include "MonkeyNewModel.hpp"
#include "MonkeyModel.hpp"
#include <ui_MonkeyWindow.h>


void MonkeyWindow::loadCollection()
{
    int numModels = _collection.getModels().size();
    int numRows = (numModels + 2) / 3; // Ensure at least one row

    for (int j = 0; j < numRows; j++) {
        for (int i = 0; i < 3; i++) {
            int modelIndex = j * 3 + i;
            if (modelIndex < numModels) {
                _ui->gridLayout->addWidget(new MonkeyWGridItem(_collection.getModels().at(modelIndex)), j, i, Qt::AlignTop);
                _ui->gridLayout->addWidget(new MonkeyWGridItem(_collection.getModels().at(modelIndex)), j, i, Qt::AlignTop);
            }
        }
    }

    connect(_ui->newModelButton, &QPushButton::clicked, this, &MonkeyWindow::showForm);
}

void MonkeyWindow::showForm()
{
    MonkeyNewModel dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // std::string name = dialog.getName();
        // Grade grade = dialog.getGrade();
        // Status status = dialog.getStatus();
        // double price = dialog.getPrice();
        //
        // MonkeyModel model(name, grade, price, status);
        // _collection.addModel(model);


        MonkeyModel temp(dialog.getName(), dialog.getGrade(), dialog.getPrice(), dialog.getStatus());
        _collection.addModel(temp);

        int lastRow = -1;
        int lastColumn = -1;

        int count = _ui->gridLayout->count();

        for (int i = 0; i < count; ++i) {
            QLayoutItem* item = _ui->gridLayout->itemAt(i);
            if (item) {
                int row, column, rowSpan, columnSpan;
                _ui->gridLayout->getItemPosition(i, &row, &column, &rowSpan, &columnSpan);
                if (row + rowSpan - 1 > lastRow) {
                    lastRow = row + rowSpan - 1;
                }
                if (column + columnSpan - 1 > lastColumn) {
                    lastColumn = column + columnSpan - 1;
                }
            }
        }

        _ui->gridLayout->addWidget(new MonkeyWGridItem(temp), lastRow, lastColumn , Qt::AlignTop);
        // TODO: fucker right here doesnt work
    } else {
        qDebug() << "Form was cancelled";
    }
}

void MonkeyWindow::adjustGridColumns()
{
    QList<QWidget *> items;
    int width = _ui->gridWidget->width();//this->width();
    int columnCount = qMax(3, width / 150); // Adjust 150 to your desired column width

    // Remove all items from the grid layout
    for (int i = 0; i < items.size(); ++i) {
        _ui->gridLayout->removeWidget(items[i]);
    }

    // Re-add items with new column count
    for (int i = 0; i < items.size(); ++i) {
        _ui->gridLayout->addWidget(items[i], i / columnCount, i % columnCount);
    }
}
