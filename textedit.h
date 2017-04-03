/*
 * This file is part of PlantUML QEditor.
 *
 * PlantUML QEditor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PlantUML QEditor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PlantUML QEditor. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QPlainTextEdit>


class TextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = 0);
    
    void setIndentSize(int indentSize) {this->_indentSize = indentSize;}
    int  indentSize() const {return this->_indentSize;}

    void setIndentWithSpace(bool indentWithSpace)  {this->_indentWithSpace = indentWithSpace;}
    bool indentWithSpace() const { return _indentWithSpace; }

    void setAutoIndent(bool autoIndent) {this->_autoIndent = autoIndent;}
    bool autoIndent() const {return this->_autoIndent;}

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void keyPressEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    int  _indentSize;
    bool _indentWithSpace;
    bool _autoIndent;

    QWidget *lineNumberArea;
};

#endif // TEXTEDIT_H
