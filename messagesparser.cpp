#include "messagesparser.h"

MessagesParser::MessagesParser(QObject *parent) : QObject(parent)
{


    dateTimeFormats.append("dddd, d MMMM yyyy' at 'hh:mm 'UTC'");
    dateTimeFormats.append("dddd, d MMMM yyyy' at 'hh:mm 'UTC+01'");
    dateTimeFormats.append("dddd, MMMM d, yyyy' at 'hh:mm 'UTC'");
    dateTimeFormats.append("dddd, MMMM d, yyyy' at 'hh:mm 'UTC+01'");

    dateTimeFormats.append("dddd, d MMMM yyyy' at 'h:mmap 'UTC'");
    dateTimeFormats.append("dddd, d MMMM yyyy' at 'h:mmap 'UTC+01'");

    dateTimeFormats.append("dddd, MMMM d, yyyy' at 'h:mmap 'UTC'");
    dateTimeFormats.append("dddd, MMMM d, yyyy' at 'h:mmap 'UTC+01'");

    dateTimeFormats.append("dddd, d MMMM yyyy' at 'hh:mm 'UTC-01'");
    dateTimeFormats.append("dddd, d MMMM yyyy' at 'hh:mm 'UTC+02'");
    dateTimeFormats.append("dddd, MMMM d, yyyy' at 'hh:mm 'UTC-01'");
    dateTimeFormats.append("dddd, MMMM d, yyyy' at 'hh:mm 'UTC+02'");
}


void MessagesParser::parseFile(QString filename, Whitelist* _whitelist, bool _countYear)
{
        countYear = _countYear;
        qDebug()<<"countyear"<<countYear;
        whitelist = _whitelist;
        sentMessages = 0;
        receivedMessages = 0;
        //minDateTime = whitelist->getStartDate();
        //maxDateTime = whitelist->getEndDate();
        startYear = QDateTime::fromString("2015-01-01 00:00:00","yyyy-MM-dd hh:mm:ss");
        endYear = QDateTime::fromString("2016-01-01 00:00:00","yyyy-MM-dd hh:mm:ss");
        //qDebug()<<minDateTime.toString("dd-MM-yy hh:mm:ss");
        //qDebug()<<maxDateTime.toString("dd-MM-yy hh:mm:ss");

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
        emit updateProgress("Loading File...", 0,0);
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

                mainPercentage = 100.0 * (ti-threads.begin()) / threads.count();
                emit updateProgress("Analysing messages", mainPercentage,0);
                qApp->processEvents();
        }

        json.insert("threads",jsonThreads);
        json.insert("sent",sentMessages);
        json.insert("received",receivedMessages);
        QJsonDocument doc(json);
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

                if (messages.count()>300) {
                subPercentage = 100.0 * (mi-messages.begin()) / messages.count();
                emit updateProgress("Analysing messages", mainPercentage,subPercentage);
                } else {
                    emit updateProgress("Analysing messages", mainPercentage,0);
                }
                qApp->processEvents();

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
        //qDebug()<<"process message from"<<user << dateTimeString;
        //QString dateTimeFormat = "dddd, d MMMM yyyy' at 'hh:mm' UTC+01'";


        QDateTime dateTime = parseDate(dateTimeString);
        if (!dateTime.isValid()) {
        QMessageBox box;
        box.setText("Sorry, this tool can't understand the date: \n\n" + dateTimeString + "\n\n\nPlease send a picture of this dialog box to us and we'll sort it out! Thanks.");
        box.exec();
        exit(EXIT_FAILURE);
        }

        if (countYear) {
                if (dateTime<startYear) return FINISHED_THREAD;

                // if it's within 2015-16,
                if (dateTime<endYear) {
                        // work out if incoming/outgoing and add to totals
                        if (user == whitelist->getUsername()) {
                                sentMessages +=1;
                        } else {
                                receivedMessages +=1;
                        }

                }
        } else {
                if (isBeforeEarliestDate(dateTime)){

                qDebug()<<"returning as before earliest date "<<dateTime;

                    return FINISHED_THREAD;
                }
        }


        if (isWithinDateRanges(dateTime)) {
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
                qDebug() <<dateTime.toString("dd-MM-yy hh:mm:ss") << "outside range" << minDateTime.toString("dd-MM-yy hh:mm:ss")  <<" and "<<maxDateTime.toString("dd-MM-yy hh:mm:ss") ;

        }
        return NO_MESSAGE;
}

QString MessagesParser::hash(QString input)
{

        QString response = QString(QCryptographicHash::hash(input.toUtf8(),QCryptographicHash::Sha1).toHex());
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

bool MessagesParser::isWithinDateRanges(QDateTime candiDate)
{
        for (int i = 0; i<whitelist->getStartDates().size(); i++)
        {
                if (candiDate > whitelist->getStartDates().at(i) && candiDate < whitelist->getEndDates().at(i)) return true;
        }
        return false;
}

bool MessagesParser::isBeforeEarliestDate(QDateTime candiDate)
{
        for (int i = 0; i<whitelist->getStartDates().size(); i++)
        {
                if (candiDate > whitelist->getStartDates().at(i)) return false;
        }
        return true;
}


QDateTime MessagesParser::parseDate(QString dateTimeString) {
        QDateTime dateTime;

        foreach(const QString &format,dateTimeFormats) {
                dateTime = QDateTime::fromString(dateTimeString,format);
                if (dateTime.isValid()) {
                    return dateTime;
                }
        }



        return QDateTime();
}
