#include "messagesparser.h"

MessagesParser::MessagesParser(QObject *parent) : QObject(parent)
{


}


void MessagesParser::parseFile(QString filename, Whitelist* _whitelist, bool countYear)
{
    qDebug()<<"countyear"<<countYear;
    whitelist = _whitelist;
    minDateTime = whitelist->getStartDate();
    maxDateTime = whitelist->getEndDate();
    qDebug()<<minDateTime.toString("dd-MM-yy hh:mm:ss");
    qDebug()<<maxDateTime.toString("dd-MM-yy hh:mm:ss");

        /*
    QFile messagesFile(filename);
    if (!messagesFile.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Can't read file: "<< qPrintable(messagesFile.errorString())<< endl;
    }
    */

    qApp->processEvents();
        qDebug() <<"loading page...";
        page = new QWebPage();
        frame = page->mainFrame();
        frame->load(QUrl::fromLocalFile(filename));
        emit updateProgress("Loading File...", 0);
        connect( frame,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished(bool)));

}

void MessagesParser::onLoadFinished(bool status) {
        if (!status) {
                qDebug() <<"Loading Failed";
                return;
        }

                qApp->processEvents();
        QWebElement docEl = frame->documentElement();
        QWebElementCollection threads = docEl.findAll("div.contents div.thread");
        qDebug()<< threads.count() << " threads found.";


        QWebElementCollection::iterator ti = threads.begin();
        while (ti != threads.end()) {
                QWebElement thread = *ti;
                ++ti;
                //qDebug()<<"Got a thread:";
                QJsonArray jsonMessages = processThread(thread);

                if (jsonMessages.size()>0) {

                        QString peopleString = thread.toPlainText().split(QRegExp("[\r\n]"),QString::SkipEmptyParts).first();
                        qDebug()<<"People";
                        qDebug()<< peopleString;

                        QJsonArray jsonPeople;

                        QStringList peopleStringList = peopleString.split(", ");
                        foreach (QString personString, peopleStringList) {
                                if (personString == whitelist->getUsername() || whitelist->searchFor(personString)) {
                                        jsonPeople.append(personString);
                                } else {
                                        jsonPeople.append(hash(personString));
                                }
                        }

                        QJsonObject jsonThread;
                        jsonThread.insert("people",jsonPeople);
                        jsonThread.insert("messages",jsonMessages);
                        jsonThreads.append(jsonThread);
                }

                float percentage = 100.0 * (ti-threads.begin()) / threads.count();
                emit updateProgress("Analysing messages", percentage);
                qApp->processEvents();
        }

        QJsonDocument doc(jsonThreads);
        emit finishedParsing(doc);

}
QJsonArray MessagesParser::processThread(QWebElement thread) {


        QJsonArray jsonMessages;

        QWebElementCollection messages = thread.findAll("div.message");
        QWebElementCollection::iterator mi = messages.begin();
        while (mi != messages.end()) {
                QWebElement message = *mi;
                int result = processMessage(message,jsonMessages);
                if (result == FINISHED_THREAD) return jsonMessages;
                ++mi;
        }

        return jsonMessages;
}
///
/// [ array of threads
/// thread:{people,
///         array of messages: [ messages
///                             {date,sender,content}
///
/// ]}
///
///        ]
///
int MessagesParser::processMessage(QWebElement message,QJsonArray& jsonMessages) {

        QString user = message.findFirst("span.user").toPlainText();
        QString dateTimeString = message.findFirst("span.meta").toPlainText();
    qDebug()<<"process message from"<<user << dateTimeString;
        //QString dateTimeFormat = "dddd, d MMMM yyyy' at 'hh:mm' UTC+01'";


        QDateTime dateTime;
        QString dateTimeFormat;
        dateTimeFormat = "dddd, d MMMM yyyy' at 'hh:mm 'UTC'";
        dateTime = QDateTime::fromString(dateTimeString,dateTimeFormat);
        if (!dateTime.isValid()) {
                dateTimeFormat = "dddd, d MMMM yyyy' at 'hh:mm' UTC+01'";
                dateTime = QDateTime::fromString(dateTimeString,dateTimeFormat);
                if (!dateTime.isValid()) {
                        //qDebug() <<"invalid date '"<< dateTimeString <<"'";
                        //break;
                }
        }

        if (dateTime<whitelist->getStartDate()) {
                return FINISHED_THREAD;
        }

        if (dateTime < whitelist->getEndDate()) {
                QString messageContent = "";
                QWebElement nextSib = message.nextSibling();
                while (nextSib.localName() == "p") {
                        messageContent += nextSib.toPlainText();
                        nextSib = nextSib.nextSibling();
                }

                QString formattedDT = dateTime.toString("dd-MM-yy hh:mm:ss");
                qDebug() << formattedDT << ": " << user <<": " << messageContent;


                QJsonObject jsonMessage;
                jsonMessage.insert("datetime",formattedDT);
                if(whitelist->getIsFullVersion()) {
                        if (user == whitelist->getUsername()) {
                                jsonMessage.insert("user", user);
                                jsonMessage.insert("body",messageContent);
                        } else if (whitelist->searchFor(user)) {
                                jsonMessage.insert("user", user);
                                jsonMessage.insert("body",messageContent);
                        } else {
                                jsonMessage.insert("user", hash(user));
                                jsonMessage.insert("body",obfuscate(messageContent));
                        }

                } else {
                        if (user == whitelist->getUsername()) {
                                jsonMessage.insert("user", user);
                                jsonMessage.insert("body",obfuscate(messageContent));
                        } else if (whitelist->searchFor(user)) {
                                jsonMessage.insert("user", user);
                                jsonMessage.insert("body",obfuscate(messageContent));
                        } else {
                                jsonMessage.insert("user", hash(user));
                                jsonMessage.insert("body",obfuscate(messageContent));
                        }
                }

                jsonMessages.append(jsonMessage);
                return GOT_MESSAGE;

        } else {
                //qDebug() <<dateTime.toString("dd-MM-yy hh:mm:ss") << "outside range" << minDateTime.toString("dd-MM-yy hh:mm:ss")  <<" and "<<maxDateTime.toString("dd-MM-yy hh:mm:ss") ;

        }
        return NO_MESSAGE;
}

QString MessagesParser::hash(QString input)
{

        QString response = input +"_"+ QString(QCryptographicHash::hash(input.toUtf8(),QCryptographicHash::Sha1).toHex());
        return response;

}

QString MessagesParser::obfuscate(QString input)
{
        int len = input.length();
        QString outputString = "";
        for (int i=0;i<len;i++) {
                outputString.append('*');
        }
        return outputString;
}

bool MessagesParser::isOnWhitelist(QString candidate) {
    bool result = whitelist->searchFor(candidate);
    qDebug()<<"Checking whitelist for " << candidate << result;
        return result;
}
