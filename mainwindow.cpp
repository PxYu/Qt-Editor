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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupFileMenu();
    setupHelpMenu();
    setupEditor();
    setupTable();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(editor, 3);
    mainLayout->addWidget(errorTable, 1);

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);
    setCentralWidget(widget);

    setWindowTitle(tr("QCodeEdit"));

    connect(errorTable, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(jumpToBug(QTableWidgetItem *)));
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
    editor->clear();
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "C++ Files (*.cpp *.h)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            editor->setPlainText(file.readAll());
    }
}

void MainWindow::compileFile()
{
    QProcess p;
    QString cmd = QString("osascript");
    QStringList args;
    QString TerminalCmd = "ls";
    QString ascript = "tell application \"Terminal\"\n";
    ascript += "  activate\n";
    ascript += "  do script \"";
    ascript += TerminalCmd;
    ascript += "\"\n";
    ascript += "end tell";
    args << "-e" << ascript;
    p.startDetached(cmd, args);
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
    errorTable = new QTableWidget(3, 3);
    errorTable->setHorizontalHeaderLabels(QStringList()<<"Row"<<"Column"<<"Information");
    QHeaderView* header = errorTable->horizontalHeader();
    header->setStretchLastSection(true);

    newItem1 = new QTableWidgetItem(tr("1"));
    newItem2 = new QTableWidgetItem(tr("2"));
    newItem3 = new QTableWidgetItem(tr("Error1"));
    errorTable->setItem(0, 0, newItem1);
    errorTable->setItem(0, 1, newItem2);
    errorTable->setItem(0, 2, newItem3);
    newItem1->setFlags(newItem1->flags() ^ Qt::ItemIsEditable);
    newItem2->setFlags(newItem2->flags() ^ Qt::ItemIsEditable);
    newItem3->setFlags(newItem3->flags() ^ Qt::ItemIsEditable);

    newItem4 = new QTableWidgetItem(tr("2"));
    newItem5 = new QTableWidgetItem(tr("100"));
    newItem6 = new QTableWidgetItem(tr("Error2"));
    errorTable->setItem(1, 0, newItem4);
    errorTable->setItem(1, 1, newItem5);
    errorTable->setItem(1, 2, newItem6);
    newItem4->setFlags(newItem4->flags() ^ Qt::ItemIsEditable);
    newItem5->setFlags(newItem5->flags() ^ Qt::ItemIsEditable);
    newItem6->setFlags(newItem6->flags() ^ Qt::ItemIsEditable);

    newItem7 = new QTableWidgetItem(tr("6"));
    newItem8 = new QTableWidgetItem(tr("8"));
    newItem9 = new QTableWidgetItem(tr("Error3"));
    errorTable->setItem(2, 0, newItem7);
    errorTable->setItem(2, 1, newItem8);
    errorTable->setItem(2, 2, newItem9);
    newItem7->setFlags(newItem7->flags() ^ Qt::ItemIsEditable);
    newItem8->setFlags(newItem8->flags() ^ Qt::ItemIsEditable);
    newItem9->setFlags(newItem9->flags() ^ Qt::ItemIsEditable);
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);
    fileMenu->addAction(tr("Compile"), this, SLOT(compileFile()), QKeySequence(Qt::CTRL + Qt::Key_R));
}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(helpMenu);
    helpMenu->addAction(tr("&About"), this, SLOT(about()));
}

//void MainWindow::handleButton()
//{
////    QString file_full, file_name, file_path;
////    QFileInfo fi;
////    file_full = QFileDialog::getOpenFileName(this);
////    fi = QFileInfo(file_full);
////    file_name = fi.fileName();
////    file_path = fi.absolutePath();
////    editor->setPlainText(file_path+"\\"+file_name);

//    QProcess p;
//    QString cmd = QString("osascript");
//    QStringList args;
//    QString TerminalCmd = "ls";
//    QString ascript = "tell application \"Terminal\"\n  activate\n  do script \"";
//    ascript+= TerminalCmd;
//    ascript+= "\"\n end tell";
//    args << "-e" << ascript;
//    p.startDetached(cmd, args);

//}
