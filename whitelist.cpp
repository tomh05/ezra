#include "whitelist.h"

Whitelist::Whitelist(QObject *parent) : QObject(parent)
{
    QString format = "yyyy-MM-dd hh:mm:ss";
    QString startDateString, endDateString;

#ifdef TOM
    username = "Tom Howe";
    isFullVersion = true;
    startDateString = "2016-01-01 00:00:00";
    endDateString = "2016-02-01 00:00:00";
    whitelist.append("Sam Bason");
    whitelist.append("Peter Taylour");
    qDebug()<<"Tom selected";
#elif ROSS

    whitelist.append("Tom Howe");
#else
#endif


    startDate = QDateTime::fromString(startDateString,format);
    endDate = QDateTime::fromString(endDateString,format);

}

QStringList Whitelist::getWhitelist()
{

    return whitelist;

}

bool Whitelist::searchFor(QString candidate)
{
    if (candidate == username) return true;
    return (whitelist.indexOf(QRegExp(candidate)) > -1);

    //QStringList::iterator q = whitelist.begin();
    //while (q != whitelist.end()) {
       // q++;
}

QString Whitelist::getUsername() const
{
    return username;
}

QDateTime Whitelist::getStartDate() const
{
    return startDate;
}

QDateTime Whitelist::getEndDate() const
{
    return endDate;
}

bool Whitelist::getIsFullVersion() const
{
    return isFullVersion;
}


