#include "whitelist.h"

Whitelist::Whitelist(QObject *parent) : QObject(parent)
{

    whitelist.append("Tom Howe");
    whitelist.append("Sam Bason");
    whitelist.append("Peter Taylour");


}

QStringList Whitelist::getWhitelist()
{

    return whitelist;

}

bool Whitelist::searchFor(QString candidate)
{

    //QStringList::iterator q = whitelist.begin();
    //while (q != whitelist.end()) {
        return (whitelist.indexOf(QRegExp(candidate)) > -1);


       // q++;


}


