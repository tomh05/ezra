#include "messagesparser.h"

MessagesParser::MessagesParser(QObject *parent) : QObject(parent)
{

}


bool MessagesParser::parseFile(QString filename)
{



    /*
    QFile messagesFile(filename);
    if (!messagesFile.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Can't read file: "<< qPrintable(messagesFile.errorString())<< endl;
    }
    */
   qDebug() <<"loading page...";
    page = new QWebPage();
    frame = page->mainFrame();
    frame->load(QUrl::fromLocalFile(filename));

    connect( frame,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished(bool)));


    /*
    QXmlStreamReader xsr;

    xsr.setDevice(&messagesFile);
    xsr.readNext();

    while(!xsr.atEnd())
        {
            if(xsr.isStartElement())
            {
                if(xsr.name() == "div")
                {
                    qDebug() <<"Got a div!" <<endl;
                    xsr.readNext();
                }
            }
    }
    */


}
void MessagesParser::onLoadFinished(bool status) {



    QWebElement docEl = frame->documentElement();

qDebug()<<docEl.findFirst("div").localName();
    qDebug()<<docEl.findFirst("div.contents").findFirst("h1").toPlainText();

qDebug() <<"loaded page...";
    qDebug() << frame->findFirstElement("div.contents").toPlainText();


}
