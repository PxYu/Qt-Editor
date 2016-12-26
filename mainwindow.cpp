/**
* @file  mainwindow.cpp
* @brief Source implementing a class for the main window of the example program.
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
#include <QtWidgets>
#include <QTableWidget>
#include <iostream>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupFileMenu();
    setupHelpMenu();
    setupSettingMenu();
    setupEditor();
    setupTable();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(editor, 3);
    mainLayout->addWidget(errorTable, 1);

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);
    setCentralWidget(widget);

    setWindowTitle(tr("CMM Editor - "));

//    QString appPath = qApp->applicationDirPath();
//    editor->setPlainText(appPath);

    connect(errorTable, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(jumpToBug(QTableWidgetItem *)));
    connect(editor, SIGNAL(textChanged()), this, SLOT(changeState()));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"),
                tr("<p>The <b>QCodeEdit</b> example shows how " \
                   "to create a basic code editing component with " \
                   "simple syntax highlighting by subclassing " \
                   "the <b>QSyntaxHighlighter</b> class and describing " \
                   "highlighting rules using regular expressions.</p>"));
}

void MainWindow::newFile()
{
    if (!fileIsSaved) {
        QMessageBox::warning(NULL, QString("Warning"), QString("Please save current file before opening another file!"), QMessageBox::Ok);
    } else {
        editor->clear();
        currentFileName = "";
        fileIsSaved = false;
    }
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull()) {
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Cmm Files (*.cmm)");
    }

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            editor->setPlainText(file.readAll());
        }
        currentFileName = fileName;
    }
    fileIsSaved = true;
}

void MainWindow::saveFile()
{
    if (currentFileName != "") {
        QFile file(currentFileName);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << editor -> toPlainText();
        file.close();
        fileIsSaved = true;
    } else {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                QDir::currentPath(),
                                tr("Cmm Files (*.cmm)"));
        if (!fileName.isNull()) {
            QFile file(fileName);
            file.open(QIODevice::WriteOnly);
            QTextStream out(&file);
            out << editor->toPlainText();
            file.close();
            currentFileName = fileName;
            fileIsSaved = true;
        }
    }
}

void MainWindow::compileFile()
{
    if (!fileIsSaved) {
        QMessageBox::warning(NULL, QString("Warning"), QString("Please save before compiling!"), QMessageBox::Ok);
    } else {
        QProcess p;
        QString cmd = QString("osascript");
        QStringList args;
        //QString TerminalCmd = "ls";
        QString TerminalCmd = "~/Downloads/cmm/cmmbuild/cmm ";
        TerminalCmd += currentFileName + " " + arguments;
        QString ascript = "tell application \"Terminal\"\n";
        ascript += "  activate\n";
        ascript += "  do script \"";
        ascript += TerminalCmd;
        ascript += "\"\n";
        ascript += "end tell";
        args << "-e" << ascript;
        p.startDetached(cmd, args);
    }
}

void MainWindow::jumpToBug(QTableWidgetItem *item){
    int tableRow = item->row();
    int bugRow = errorTable->item(tableRow, 0)->text().toInt();
    int bugCol = errorTable->item(tableRow, 1)->text().toInt();
    QTextCursor qtc = editor->textCursor();
    qtc.setPosition(0);
    qtc.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor, bugRow-1);
    qtc.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, bugCol-1);
    editor->setFocus();
    editor->setTextCursor(qtc);
}

void MainWindow::changeState() {
    fileIsSaved = false;
}

void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("PT Mono");
    font.setFixedPitch(true);
    font.setPointSize(16);

    editor = new QCodeEdit();
    editor->setFont(font);

    highlighter = new QCodeCPP(editor->document());

    QFile file("mainwindow.h");
    if (file.open(QFile::ReadOnly | QFile::Text))
        editor->setPlainText(file.readAll());
}

void MainWindow::setupTable()
{
    errorTable = new QTableWidget(0, 3);
    errorTable->setHorizontalHeaderLabels(QStringList()<<"Row"<<"Column"<<"Information");
    QHeaderView* header = errorTable->horizontalHeader();
    header->setStretchLastSection(true);

//    errorTable->setItem(0, 0, new QTableWidgetItem(tr("1")));
//    errorTable->setItem(0, 1, new QTableWidgetItem(tr("2")));
//    errorTable->setItem(0, 2, new QTableWidgetItem(tr("e1")));
//    errorTable->setItem(1, 0, new QTableWidgetItem(tr("2")));
//    errorTable->setItem(1, 1, new QTableWidgetItem(tr("4")));
//    errorTable->setItem(1, 2, new QTableWidgetItem(tr("e2")));
//    errorTable->setItem(2, 0, new QTableWidgetItem(tr("5")));
//    errorTable->setItem(2, 1, new QTableWidgetItem(tr("2")));
//    errorTable->setItem(2, 2, new QTableWidgetItem(tr("e3")));

//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 2; j++) {
//            errorTable->item(i,j)->setFlags(errorTable->item(i,j)->flags() ^ Qt::ItemIsEditable);
//            errorTable->item(i,j)->setBackground(QColor::fromRgb(238,99,99));
//        }
//        errorTable->item(i,2)->setFlags(errorTable->item(i,2)->flags() ^ Qt::ItemIsEditable);
//    }
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("&Save"), this, SLOT(saveFile()), QKeySequence::Save);
    fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);
    fileMenu->addAction(tr("&Compile"), this, SLOT(compileFile()), QKeySequence(Qt::CTRL + Qt::Key_R));
}

void MainWindow::setupSettingMenu(){
    QMenu *settingMenu = new QMenu(tr("&Setting"), this);
    menuBar()->addMenu(settingMenu);

    settingMenu->addAction(tr("&set arguments"), this, SLOT(setArgs()), Qt::Key_A);
}

void MainWindow::setArgs(){
    bool isOk;
    QString text = QInputDialog::getText(NULL, "Input Dialog", "Please input your comment", QLineEdit::Normal, arguments, &isOk);
    if (isOk) {
        arguments = text;
    }
}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(helpMenu);
    helpMenu->addAction(tr("&About"), this, SLOT(about()));
}

void MainWindow::insertToTable(bool *isWarning, int *row, int *col, const std::string &msg) {

    int rowCount = errorTable->rowCount();
    errorTable->insertRow(rowCount);

    errorTable->setItem(rowCount, 0, new QTableWidgetItem(row));
    errorTable->setItem(rowCount, 1, new QTableWidgetItem(col));
    errorTable->setItem(rowCount, 2, new QTableWidgetItem(QString(msg)));

    if (!isWarning) {
        for (int i = 0; i < 3; i++) {
            errorTable->item(rowCount,i)->setFlags(errorTable->item(rowCount,i)->flags() ^ Qt::ItemIsEditable);
            errorTable->item(rowCount,i)->setBackground(QColor::fromRgb(238,99,99));
        }
    } else {
        for (int i = 0; i < 3; i++) {
            errorTable->item(rowCount,i)->setFlags(errorTable->item(rowCount,i)->flags() ^ Qt::ItemIsEditable);
            errorTable->item(rowCount,i)->setBackground(QColor::fromRgb(255,193,37));
        }
    }
}

