#ifndef UPLOADMANAGER_H
#define UPLOADMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QHttpMultiPart>

class UploadManager : public QObject
{
    Q_OBJECT
public:
    explicit UploadManager(QObject *parent = 0);

    void uploadFile(QString filename);

signals:

public slots:

};

#endif // UPLOADMANAGER_H
