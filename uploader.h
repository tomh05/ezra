#ifndef UPLOADER_H
#define UPLOADER_H

#include <QObject>
#include <QDebug>
//#include <QSslSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QFile>
#include <QHttpPart>



class Uploader : public QObject
{
    Q_OBJECT
public:
    explicit Uploader(QObject *parent = 0);

signals:
    void finishedUploading(QString result);

public slots:
    void upload(QString string);

private slots:
    void replyFinished(QNetworkReply* reply);
    void slotError(QNetworkReply::NetworkError ne);
    void slotSslErrors(QList<QSslError> es);
};

#endif // UPLOADER_H
