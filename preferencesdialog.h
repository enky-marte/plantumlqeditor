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

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

namespace Ui {
class PreferencesDialog;
}

class FileCache;

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(FileCache* file_cache, QWidget *parent = 0);
    ~PreferencesDialog();

    void readSettings();
    void writeSettings();

private slots:
    void onRejected();
    void on_customJavaPathEdit_textEdited(const QString &);
    void on_customJavaPathButton_clicked();
    void on_customPlantUmlEdit_textEdited(const QString &);
    void on_customPlantUmlButton_clicked();
    void on_assistantXmlButton_clicked();
    void on_customGraphizEdit_textEdited(const QString &);
    void on_customGraphizButton_clicked();
    void on_customCacheEdit_textEdited(const QString &);
    void on_customCacheButton_clicked();
    void on_clearCacheButton_clicked();
    void on_checkExternalPrograms_clicked();
    void onCurrentTabChanged();

private:
    void checkExternalPrograms();
    bool checkExternalProgram(const QString& path, const QStringList& arguments, QString& log, const QString& validator = QString());

    Ui::PreferencesDialog *m_ui;
    FileCache* m_fileCache;
};

#endif // PREFERENCESDIALOG_H
