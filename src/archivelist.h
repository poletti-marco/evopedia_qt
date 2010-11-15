#ifndef ARCHIVELIST_H
#define ARCHIVELIST_H

#include <QTreeWidget>
#include <QHash>
#include <QPair>
#include <QString>
#include <QSignalMapper>

#include "archive.h"
#include "localarchive.h"
#include "partialarchive.h"
#include "downloadablearchive.h"

class ArchiveList : public QTreeWidget
{
    Q_OBJECT

    QSignalMapper *downloadPausedMapper;
    QSignalMapper *downloadStartedMapper;

    void fillLocalArchiveItem(LocalArchive *a, QTreeWidgetItem *item);
    void fillPartialArchiveItem(PartialArchive *a, QTreeWidgetItem *item);
    void fillDownloadableArchiveItem(DownloadableArchive *a, QTreeWidgetItem *item);

private slots:

    void itemClickedHandler(QTreeWidgetItem *item, int column);
    void downloadPausedHandler(QWidget *button);
    void downloadStartedHandler(QWidget *button);

public:
    explicit ArchiveList(QWidget *parent = 0);

signals:

public slots:
    void updateArchives(const QList<Archive *> &archives);
    void exchangeArchives(DownloadableArchive *from, PartialArchive *to);
    void exchangeArchives(PartialArchive *from, LocalArchive *to);

};

#endif // ARCHIVELIST_H