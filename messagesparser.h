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



class MessagesParser : public QObject
{
    Q_OBJECT
public:
    explicit MessagesParser(QObject *parent = 0);

    void parseFile(QString filename, QDateTime _minDateTime, QDateTime _maxDateTime);

signals:

public slots:

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
