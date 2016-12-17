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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupFileMenu();
    setupHelpMenu();
    setupEditor();

    setCentralWidget(editor);
    setWindowTitle(tr("QCodeEdit"));
    m_button = new QPushButton("Compile...", this);
    m_button->setGeometry(QRect(QPoint(270, 482), QSize(100, 30)));
    connect(m_button, SIGNAL (clicked()), this, SLOT (handleButton()));
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

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);
}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(helpMenu);
    helpMenu->addAction(tr("&About"), this, SLOT(about()));
}

void MainWindow::handleButton()
{
    //editor->setPlainText("TEST");
//    QString file_full, file_name, file_path;
//    QFileInfo fi;
//    file_full = QFileDialog::getOpenFileName(this);
//    fi = QFileInfo(file_full);
//    file_name = fi.fileName();
//    file_path = fi.absolutePath();
//    editor->setPlainText(file_path+"\\"+file_name);

    QProcess p;
    QString cmd = QString("osascript");
    QStringList args;
    QString TerminalCmd = "ls";
    QString ascript = "tell application \"Terminal\"\n  activate\n  do script \"";
    ascript+= TerminalCmd;
    ascript+= "\"\n end tell";
    args << "-e" << ascript;
    p.startDetached(cmd, args);

}
