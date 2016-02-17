#ifndef MESSAGESPARSER_H
#define MESSAGESPARSER_H

#include <QObject>
#include <QFile>
//#include <QXmlStreamReader>
#include <QDebug>
#include <QWebPage>
#include <QWebFrame>
#include <QUrl>
#include <QWebElement>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCryptographicHash>
#include <QThread>



class MessagesParser : public QObject
{
    Q_OBJECT
    QThread messagesParserThread;
public:
    explicit MessagesParser(QObject *parent = 0);



signals:
    void finishedParsing(QJsonDocument doc);
    void updateProgress(QString,int);

public slots:
    void parseFile(QString filename, QDateTime _minDateTime, QDateTime _maxDateTime);
private slots:
    void onLoadFinished(bool status);


private:
    QJsonArray processThread(QWebElement thread);
    int processMessage(QWebElement message, QJsonArray &jsonMessages);
    bool isOnWhitelist(QString candidate);
    QString hash(QString input);
    QString obfuscate(QString input);


    enum {GOT_MESSAGE, NO_MESSAGE, FINISHED_THREAD};

    QWebPage * page;
    QWebFrame * frame;
    QDateTime minDateTime, maxDateTime;

    QJsonArray jsonThreads;




};

#endif // MESSAGESPARSER_H
