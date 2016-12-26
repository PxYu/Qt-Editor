/**
* @file  highlighter.cpp
* @brief Source implementing a class for a basic C++ syntax highlighter.
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

#include "qcodecpp.h"

QCodeCPP::QCodeCPP(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
#define KEYWORD(KW) (keywordPatterns << "\\b" #KW "\\b")
    KEYWORD(if);
    KEYWORD(else);
    KEYWORD(for);
    KEYWORD(while);
    KEYWORD(do);
    KEYWORD(break);
    KEYWORD(continue);
    KEYWORD(return);
    KEYWORD(int);
    KEYWORD(double);
    KEYWORD(bool);
    KEYWORD(void);
    KEYWORD(string);
    KEYWORD(infix);
    KEYWORD(true);
    KEYWORD(false);
#undef KEYWORD
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    numericConstantFormat.setFontWeight(QFont::Bold);
    numericConstantFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\b-?[0-9]+.[0-9]*|-?[0-9]+\\b");
    rule.format = numericConstantFormat;
    highlightingRules.append(rule);

    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    infixOperatorFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("\\b[\\\\=\\^\\$\\?\\|\\*\\+-/<>@]+\\b");
    rule.format = infixOperatorFormat;
    highlightingRules.append(rule);

    dynamicFunctionFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+!(?=\\()");
    rule.format = dynamicFunctionFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::darkCyan);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void QCodeCPP::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
