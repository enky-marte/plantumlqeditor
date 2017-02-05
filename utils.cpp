#include <QObject>
#include "utils.h"

QString cacheSizeToString(int size)
{
    return QObject::tr("%1 Mb").arg(size / CACHE_SCALE, 0, 'f', 2);
}
