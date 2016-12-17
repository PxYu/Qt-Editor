/**
* @file  qcodeedit.h
* @brief Header implementing the QCodeEdit widget.
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

#ifndef QCODEEDITOR_H
#define QCODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QAbstractItemModel>
#include <QCompleter>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

class QCodeEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    QCodeEdit(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void setTabSpaces(const int tabStop);
    void setFont(const QFont& font);
    void setCompleter(QCompleter *completer);
    QString textUnderCursor() const;
    QAbstractItemModel *modelFromFile(const QString& fileName);

protected:
    void resizeEvent(QResizeEvent *event);
    void focusInEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *e);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void insertCompletion(const QString& completion);

private:
    QWidget *lineNumberArea;
    QColor marginForeground;
    QColor marginBackground;
    QColor currentLineBackground;
    QCompleter *codeCompleter;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(QCodeEdit *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    QCodeEdit *codeEditor;
};

#endif
