#ifndef MESSAGESPARSER_H
#define MESSAGESPARSER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QWebPage>
#include <QWebFrame>
#include <QUrl>
#include <QWebElement>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCryptographicHash>
#include <QApplication>
#include <QThread>
#include <QMessageBox>
#include "whitelist.h"


class MessagesParser : public QObject
{
    Q_OBJECT
    QThread messagesParserThread;
public:
    explicit MessagesParser(QObject *parent = 0);



signals:
    void finishedParsing(QJsonDocument doc);
    void updateProgress(QString,int,int);

public slots:
    void parseFile(QString filename, Whitelist* whitelist, bool _countYear);
private slots:
    void onLoadFinished(bool status);


private:
    QJsonArray processThread(QWebElement thread);
    int processMessage(QWebElement message, QJsonArray &jsonMessages);
    bool isOnWhitelist(QString candidate);
    QString hash(QString input);
    QString obfuscate(QString input);
    QDateTime parseDate(QString dateTimeString);
    QStringList dateTimeFormats;


    enum {GOT_MESSAGE, NO_MESSAGE, FINISHED_THREAD};

    QWebPage * page;
    QWebFrame * frame;
    QDateTime minDateTime, maxDateTime;
    QDateTime startYear, endYear;

    QJsonObject json;
    QJsonArray jsonThreads;

    Whitelist * whitelist;

    QWebElement docEl;
    bool countYear;
    int sentMessages;
    int receivedMessages;

    float mainPercentage,subPercentage;




};

#endif // MESSAGESPARSER_H
