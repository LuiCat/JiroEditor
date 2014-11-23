class NoteMap;

#ifndef NOTEMAP_H
#define NOTEMAP_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QStringList>

#include "notemapprivate.h"

#include "note.h"
#include "segment.h"
#include "mapstate.h"


class NoteMap : public QObject
{
    Q_OBJECT

public:

    friend class MapState;

    explicit NoteMap(QObject *parent = 0);

    MapState begin() const;
    MapState timeBegin() const;
    MapState end() const;

    bool loadNoteMapFile(QString filename);
    bool saveNoteMapFile(QString filename);
    bool saveNoteMapFile();
    bool reloadNoteMap();

    QString getProperty(QString key) const;

    QString getMapDir() const;
    QString getMapFilename() const;
    QString getMapFullPath() const;

protected:

    QList<Segment> segments;

    QHash<QString, QString> mapProperties;
    QStringList listProperties;

    QString mapFilename;
    QString mapDir;

};

#endif // NOTEMAP_H
