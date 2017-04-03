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

#ifndef RECENTDOCUMENTS_H
#define RECENTDOCUMENTS_H

#include <QObject>
#include <QList>
#include <QStringList>

class QAction;
class QSettings;

class RecentDocuments : public QObject
{
    Q_OBJECT
public:
    explicit RecentDocuments(int max_documents, QObject *parent = 0);
    QList<QAction*> actions() const { return m_actions; }

    void clear();
    void accessing(const QString& name);
    void readFromSettings(QSettings& settings, const QString& section);
    void writeToSettings(QSettings& settings, const QString& section);

signals:
    void recentDocument(const QString& name);

private slots:
    void onCleatActionTriggered();
    void onRecentDocumentsActionTriggered(int index);

private:
    const int m_maxDocuments;
    QList<QAction*> m_actions;
    QList<QAction*> m_recentDocumentsActions;
    QAction* m_separatorAction;
    QAction* m_clearAction;
    QStringList m_documents;
};

#endif // RECENTDOCUMENTS_H
