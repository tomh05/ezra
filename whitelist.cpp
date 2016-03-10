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
#elif SAM
    username = "Sam Bason";
    isFullVersion = false;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";
    whitelist.append("Tom Howe");
#elif BECKY
    username = "Becky Skeggs";
    isFullVersion = false;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";

#elif MEGAN
    username = "Megan Davies";
    isFullVersion = true;
    startDateString = "2016-01-15 00:00:00";
    endDateString = "2016-01-25 23:59:59";
    whitelist.append("Rhys Davies");
    whitelist.append("Dell Davies");
    whitelist.append("Angharad Annie Evans");
    whitelist.append("Katie Evans");
    whitelist.append("Llinos Evans");
    whitelist.append("Bronwen Lloyd");
    whitelist.append("Megan Rees");
    whitelist.append("Nia Paddison Rees");
    whitelist.append("Tanwen Mair");
    whitelist.append("Catrin Long");

#elif ALEX
    username = "Alex Lloyd Young";
    isFullVersion = true;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";
    whitelist.append("Alastair Young");
    whitelist.append("Berenice Lloyd");
    whitelist.append("Ivo Lloyd Young");
    whitelist.append("Zain Cruinkshank");
    whitelist.append("Bruno Thompson");
    whitelist.append("James Ross");
    whitelist.append("Ethan Brodie");

#elif IVO
    username = "Ivo Lloyd Young";
    isFullVersion = true;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";
    whitelist.append("Alastair Young");
    whitelist.append("Berenice Lloyd");
    whitelist.append("Alex Lloyd Young");
    whitelist.append("Zain Cruinkshank");
    whitelist.append("Bruno Thompson");
    whitelist.append("James Ross");
    whitelist.append("Ethan Brodie");


#elif CALVIN
    username = "Calvin Pearson";
    isFullVersion = true;
    startDateString = "2016-02-05 00:00:00";
    endDateString = "2016-02-15 23:59:59";
    whitelist.append("Helen Kirkham");
    whitelist.append("Lauren Pearson");
    whitelist.append("Simon Harrison");
    whitelist.append("Connor Watkins");
    whitelist.append("Katie Moulson");

#elif ALICE
    username = "Alice Baller";
    isFullVersion = true;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";
    whitelist.append("Tracey Baller");
    whitelist.append("Nigel Baller");
    whitelist.append("Mabel Baller");
    whitelist.append("Phoebe Baller");
    whitelist.append("Phoebe Emily Baller");
    whitelist.append("Hayley Nurten");
    whitelist.append("Amy Crumpton");
    whitelist.append("Jack Hughes");
    whitelist.append("Mia Biddle");
    whitelist.append("James Barry");
    whitelist.append("Ruby Davis");


#elif PHOEBE
    username = "Phoebe Baller";
    isFullVersion = true;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";
    whitelist.append("Tracey Baller");
    whitelist.append("Nigel Baller");
    whitelist.append("Alice Baller");
    whitelist.append("Hayley Nurthen");
    whitelist.append("Loz Tabor");
    whitelist.append("Holly Sealey");
    whitelist.append("Leigha Phillips");
    whitelist.append("Seranna Barnett");

#elif CHARLOTTE
    username = "Charlotte ????";
    isFullVersion = true;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";
    whitelist.append("Jacqui Pritchard");
    whitelist.append("Richard J Langeveld");
    whitelist.append("Annie Sinclair");
    whitelist.append("Anayla Ford");
    whitelist.append("Katie Salisbury");

#elif REBECCA
    username = "REBECCA ????";
    isFullVersion = true;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";
    whitelist.append("Alex Rappoport");
    whitelist.append("Gill Saunders");
    whitelist.append("Ellie Palmer");
    whitelist.append("Hannah Globe");
    whitelist.append("Chloe Ziff");
    whitelist.append("Abby Williams");
    whitelist.append("Zachary Igielman");

#elif MABEL
    username = "Mabel Baller";
    isFullVersion = true;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";
    whitelist.append("Tracey Baller");
    whitelist.append("Nigel Baller");
    whitelist.append("Alice Baller");
    whitelist.append("Phoebe Baller");
    whitelist.append("Hayley Nurthen");

#elif HET
    username = "Het ????";
    isFullVersion = true;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";
    whitelist.append("Shikha Parekh");
    whitelist.append("Nisha Moktan");
    whitelist.append("Lekha Bhagat");
    whitelist.append("Jasmina Hamdona");
    whitelist.append("Chandni Savjani");
    //whitelist.append("Tejal Shah"); // is this used??
    //whitelist.append("Vijay Shah"); // is this used??

#elif NATHAN
    username = "Nathan ???";
    isFullVersion = false;
    startDateString = "2016-02-01 00:00:00";
    endDateString = "2016-02-10 23:59:59";

#elif ETHAN
    username = "Ethan Kerr";
    isFullVersion = false;
    startDateString = "2016-02-19 00:00:00";
    endDateString = "2016-03-07 23:59:59";
 #elif EVE
    username = "Eve Scarborough";
    isFullVersion = false;
    startDateString = "2016-02-05 00:00:00";
    endDateString = "2016-02-15 23:59:59";


#else
    qDebug()<<"NO whitelist SELECTED!";
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


