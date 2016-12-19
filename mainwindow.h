/**
* @file  mainwindow.h
* @brief Header implementing a class for the main window of the example program.
*
* @section License
*
* Copyright (C) 2013 Robert B. Colton
* This file is a part of the QCodeEdit styled text control.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QCodeEdit/qcodecpp.h"
#include "QCodeEdit/qcodeedit.h"

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void about();
    void newFile();
    void openFile(const QString &path = QString());
    void compileFile();
    void jumpToBug(QTableWidgetItem *);

private:
    void setupEditor();
    void setupFileMenu();
    void setupHelpMenu();
    void setupTable();

Q_SIGNALS:
    void itemDoubleClicked(QTableWidgetItem *item);

private:
    QCodeEdit *editor;
    QCodeCPP *highlighter;
    QTableWidget *errorTable;
    QTableWidgetItem *newItem1;
    QTableWidgetItem *newItem2;
    QTableWidgetItem *newItem3;
    QTableWidgetItem *newItem4;
    QTableWidgetItem *newItem5;
    QTableWidgetItem *newItem6;
    QTableWidgetItem *newItem7;
    QTableWidgetItem *newItem8;
    QTableWidgetItem *newItem9;

};

#endif // MAINWINDOW_H
