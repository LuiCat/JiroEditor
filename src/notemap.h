class NoteMap;

#ifndef NOTEMAP_H
#define NOTEMAP_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QStringList>

#include "note.h"

class NoteMap : public QObject
{
    Q_OBJECT

public:

    explicit NoteMap(QObject *parent = 0);

protected:

    QList<QList<Note>> segments;
    QHash<QString, QString> mapProperties;
    QStringList listProperties;

    QString mapFilename;
    QString mapDir;

};

#endif // NOTEMAP_H
