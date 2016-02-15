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

class MessagesParser : public QObject
{
    Q_OBJECT
public:
    explicit MessagesParser(QObject *parent = 0);

    bool parseFile(QString filename);

signals:

public slots:

private slots:
    void onLoadFinished(bool status);


private:
    QWebPage * page;
    QWebFrame * frame;
};

#endif // MESSAGESPARSER_H
