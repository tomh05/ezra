#ifndef FBWIZARD_H
#define FBWIZARD_H

#include <QWizard>
#include "messagesparser.h"
#include "fileselectpage.h"
#include "intropage.h"
#include "parsepage.h"
#include <QDebug>
#include <QJsonDocument>
#include "encryptor.h"
#include "uploader.h"


class FbWizard : public QWizard
{
    Q_OBJECT
public:
    FbWizard(QWidget *parent = 0);
    enum {Page_Intro, Page_FileSelect, Page_Parse};

    MessagesParser * messagesParser;
    Encryptor * encryptor;
    Uploader * uploader;

    FileSelectPage* fileSelectPage;
    ParsePage* parsePage;

signals:
    void parseFile(QString filename, QDateTime minDateTime, QDateTime maxDateTime);
    void encrypt(QString string);
    void upload(QString string);

private slots:
    void runParser(QString filename);

    void onFinishedParsing(QJsonDocument doc);
    void onFinishedEncrypting(QString result);
    void onFinishedUploading(QString result);

private:
    QDateTime minDateTime, maxDateTime;
    QThread messagesParserThread, encryptorThread, uploaderThread;
    QJsonDocument messagesJsonDoc;

};

#endif // FBWIZARD_H
