#include "whitelist.h"

Whitelist::Whitelist(QObject *parent) : QObject(parent)
{
    QString format = "yyyy-MM-dd hh:mm:ss";
    QString startDateString, endDateString;

#ifdef TOM
    username = "Tom Howe";
    isFullVersion = true;
    startDateString = "2016-01-01 00:00:00";
    endDateString = "2016-02-01 23:59:59";
    whitelist.append("Sam Bason");
    whitelist.append("Peter Taylour");
    qDebug()<<"Tom selected";
#elif ROSS
    username = "Ross Kirby";
    isFullVersion = true;
    startDateString = "2016-01-31 00:00:00";
    endDateString = "2016-02-20 23:59:59";
    whitelist.append("Alice Chen");
    whitelist.append("James Millward");
    whitelist.append("Dan Robertson");
    whitelist.append("Tom Harris");
    whitelist.append("Tom Coysh");
    whitelist.append("Nick Chamberlain");
    qDebug()<<"Ross selected";
#elif EILEEN
    username = "Eileen Inkson";
    isFullVersion = false;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";
#elif MATILDA
    username = "Matilda Blanche";
    isFullVersion = true;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-07 23:59:59";
    whitelist.append("Seb Dunnett");
    whitelist.append("Will Hünter");
    whitelist.append("Pete Brook");
    whitelist.append("Yas Min");
#elif LOUISE
    username = "Louise Coot";
    isFullVersion = true;
    startDateString = "2016-01-01 00:00:00";
    endDateString = "2016-01-14 23:59:59";
    whitelist.append("Matilda Coot");
    whitelist.append("Ross Coot");
#
#else
    qDebug()<<"NO WHITELIST SELECTED!";
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


