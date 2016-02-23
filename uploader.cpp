#include "uploader.h"

Uploader::Uploader(QObject *parent) : QObject(parent)
{

}

void Uploader::upload(QString string)
{
    qDebug()<<"uploading";

    /*
    QSslSocket socket;
    qDebug()<<"made socket";
    socket.connectToHostEncrypted("https://132.185.142.102", 443);
    qDebug()<<"connecting";
    if (!socket.waitForEncrypted()) {
        qDebug() << socket.errorString();
        return;
    }
    qDebug()<<"got to write";
    socket.write("GET / HTTP/1.0\r\n\r\n");
    while (socket.waitForReadyRead())
        qDebug() << socket.readAll().data();
*/

    /*
    QFile keyFile(":/r/transfer.key");
    if(!keyFile.open(QFile::ReadOnly | QFile::Text))
    qDebug()<<"Can't open file!";

    QString transferKey = keyFile.readAll();
    keyFile.flush();
    keyFile.close();
    */


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));


    QUrlQuery postData;
    postData.addQueryItem("type", "fb_extractor");
    postData.addQueryItem("data", string);

    QNetworkRequest request;
    request.setUrl(QUrl("https://132.185.142.102"));


    QFile keyFile(":/r/ca.pem");
    keyFile.open(QIODevice::ReadOnly);
    QSslCertificate cert(&keyFile,QSsl::Pem);


    QList<QSslCertificate> certs;
    certs.append(cert);


    QSslConfiguration sslConfiguration;
    sslConfiguration.setProtocol(QSsl::TlsV1_0OrLater);
    sslConfiguration.setCaCertificates(certs);
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);



    qDebug() << sslConfiguration.caCertificates();

    request.setSslConfiguration(sslConfiguration);
    //qDebug() << request.sslConfiguration().caCertificates().first().issuerInfoAttributes();


    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart textPartType;
    textPartType.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"type\""));
    textPartType.setBody("facebook_extract");

    QHttpPart textPartData;
    textPartData.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    textPartData.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"data\""));
    //textPartData.setBody(string.toUtf8());


    QFile *file = new QFile("/Users/tomh/Programming/coot/facebook/facebook-fetch/data.json");
    file->open(QIODevice::ReadOnly);
    textPartData.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart


    multiPart->append(textPartType);
    multiPart->append(textPartData);






    //QNetworkReply* reply = manager->post(request,postData.toString(QUrl::FullyEncoded).toUtf8());
    QNetworkReply* reply = manager->post(request,multiPart);
    //connect(reply, SIGNAL(), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(slotSslErrors(QList<QSslError>)));


}

void Uploader::replyFinished(QNetworkReply *reply)
{
    qDebug()<<"reply";
    if (reply->error()) {
    qDebug()<< reply->errorString();
    } else {
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
               qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
               qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
               qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
               qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

               qDebug() << reply->readAll();

    }
}

void Uploader::slotError(QNetworkReply::NetworkError ne)
{
    qDebug()<<"slotError";

    qDebug()<< ne;

}

void Uploader::slotSslErrors(QList<QSslError> es)
{
    qDebug()<<"slotSslErrors";

    foreach(QSslError e,es) {
        e.errorString();
    }

}
