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

#include "recentdocuments.h"
#include <QAction>
#include <QSettings>
#include <QSignalMapper>

namespace {
const QString SETTINGS_RECENT_DOCUMENTS_DOCUMENT_KEY = "document";
} // namespace {}

RecentDocuments::RecentDocuments(int max_documents, QObject *parent)
    : QObject(parent)
    , m_maxDocuments(max_documents)
{
    QSignalMapper *mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(onRecentDocumentsActionTriggered(int)));

    for (int i = 0; i < m_maxDocuments; ++i) {
        QAction* action = new QAction(this);
        connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
        mapper->setMapping(action, i);
        m_recentDocumentsActions << action;
        m_actions << action;
    }

    m_separatorAction = new QAction(this);
    m_separatorAction->setSeparator(true);
    m_actions << m_separatorAction;

    foreach(QAction* action, m_actions) {
        action->setVisible(false);
    }

    // m_clearAction is allways visible
    m_clearAction = new QAction(this);
    m_clearAction->setText(tr("Clear"));
    m_actions << m_clearAction;

    connect(m_clearAction, SIGNAL(triggered()), this, SLOT(onCleatActionTriggered()));
}

void RecentDocuments::clear()
{
    foreach(QAction* action, m_recentDocumentsActions) {
        action->setText("");
        action->setVisible(false);
    }

    m_separatorAction->setVisible(false);
}

void RecentDocuments::accessing(const QString &name)
{
    int index = m_documents.indexOf(name);
    if (index >= 0) {
        m_documents.removeAt(index);
    }

    m_documents.prepend(name);

    if (m_documents.size() > m_maxDocuments) {
        m_documents = m_documents.mid(0, m_maxDocuments);
    }

    index = 0;
    for (; index < m_documents.size(); ++index) {
        m_recentDocumentsActions[index]->setText(tr("%1. %2").arg(index + 1).arg(m_documents[index]));
        m_recentDocumentsActions[index]->setVisible(true);
    }

    for (; index < m_recentDocumentsActions.size(); ++index) {
        m_recentDocumentsActions[index]->setText("");
        m_recentDocumentsActions[index]->setVisible(false);
    }

    m_separatorAction->setVisible(true);
}

void RecentDocuments::readFromSettings(QSettings& settings, const QString &section)
{
    m_documents.clear();

    int size = settings.beginReadArray(section);
    int index = 0;
    for (; index < qMin(size, m_maxDocuments); ++index) {
        settings.setArrayIndex(index);
        m_documents.append(settings.value(SETTINGS_RECENT_DOCUMENTS_DOCUMENT_KEY).toString());
        m_recentDocumentsActions[index]->setText(tr("%1. %2").arg(index + 1).arg(m_documents[index]));
        m_recentDocumentsActions[index]->setVisible(true);
    }
    settings.endArray();

    for (; index < m_recentDocumentsActions.size(); ++index) {
        m_recentDocumentsActions[index]->setText("");
        m_recentDocumentsActions[index]->setVisible(false);
    }

    m_separatorAction->setVisible(size > 0);
}

void RecentDocuments::writeToSettings(QSettings &settings, const QString &section)
{
    settings.remove(section);
    settings.beginWriteArray(section);
    for(int index = 0; index < m_documents.size(); ++index) {
        settings.setArrayIndex(index);
        settings.setValue(SETTINGS_RECENT_DOCUMENTS_DOCUMENT_KEY, m_documents.at(index));
    }
    settings.endArray();
}

void RecentDocuments::onCleatActionTriggered()
{
    clear();
}

void RecentDocuments::onRecentDocumentsActionTriggered(int index)
{
    emit recentDocument(m_documents.value(index));
}
