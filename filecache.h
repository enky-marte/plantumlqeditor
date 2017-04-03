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

#ifndef FILECACHE_H
#define FILECACHE_H

#include <functional>
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QMap>
#include <QSet>

//------------------------------------------------------------------------------

struct FileCacheError {};

//------------------------------------------------------------------------------

class AbstractFileCacheItem : public QObject
{
    Q_OBJECT
public:
    explicit AbstractFileCacheItem(const QString& path, const QString& key, int cost, const QDateTime& date_time, QObject* parent = 0);
    virtual ~AbstractFileCacheItem();

    const QString& path() const { return m_path; }
    const QString& key() const { return m_key; }
    int cost() const { return m_cost; }
    const QDateTime& dateTime() const { return m_dateTime; }

    void removeFileFromDisk() const { removeFileFromDisk(m_path); }

protected:
    virtual void removeFileFromDisk(const QString& path) const = 0;

private:
    QString m_path;
    QString m_key;
    int m_cost;
    QDateTime m_dateTime;
};

//------------------------------------------------------------------------------

class FileCacheItem : public AbstractFileCacheItem
{
    Q_OBJECT
public:
    explicit FileCacheItem(const QString& path, const QString& key, int cost, const QDateTime& date_time, QObject* parent = 0);
    virtual ~FileCacheItem();

private:
    virtual void removeFileFromDisk(const QString& some_path) const;

    mutable bool m_removed;
};

//------------------------------------------------------------------------------

class FileCache : public QObject
{
    Q_OBJECT
public:
    typedef std::function<AbstractFileCacheItem* (const QString&, // path
                                                  const QString&, // key
                                                  int, // cost
                                                  const QDateTime&, // access time
                                                  QObject* // parent
                                                  )>  ItemGenerator;

    FileCache(int maxCost = 0, QObject* parent = 0);
    virtual ~FileCache();

    int maxCost() const { return m_maxCost; }
    void setMaxCost(int max_cost);

    bool hasItem(const QString& key) const;
    void addItem(AbstractFileCacheItem* item);
    void addItem(const QByteArray& data, const QString& key, ItemGenerator item_generator);

    int totalCost() const { return m_totalCost; }

    int size() const { return m_items.size(); }
    QList<QString> keys() const { return m_items.keys(); }
    const AbstractFileCacheItem* item(const QString& key) const { return m_items.value(key); }

    void clear();
    void clearFromDisk();

    bool setPath(const QString& path, ItemGenerator item_generator);
    const QString& path() const { return m_path; }

private:
    bool updateFromDisk(const QString &path, ItemGenerator item_generator);

    QString m_path;
    int m_maxCost;
    int m_totalCost;
    QMap<QString, AbstractFileCacheItem*> m_items;
    QList<QString> m_indexByDate;
};

//------------------------------------------------------------------------------

#endif // FILECACHE_H
