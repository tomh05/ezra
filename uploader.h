#ifndef UPLOADER_H
#define UPLOADER_H

#include <QObject>
#include <QDebug>

class Uploader : public QObject
{
    Q_OBJECT
public:
    explicit Uploader(QObject *parent = 0);

signals:
    void finishedUploading(QString result);

public slots:
    void upload(QString string);
};

#endif // UPLOADER_H
