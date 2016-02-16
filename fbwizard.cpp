#include "fbwizard.h"

FbWizard::FbWizard(MessagesParser * _mp, QWidget *parent)
    : QWizard(parent)
{
    messagesParser = _mp;
    minDateTime = QDateTime::fromString("2016-01-10 00:00:00","yyyy-MM-dd hh:mm:ss");
    maxDateTime = QDateTime::fromString("2016-01-20 00:00:00","yyyy-MM-dd hh:mm:ss");
    qDebug()<<minDateTime.toString("dd-MM-yy hh:mm:ss");
    qDebug()<<maxDateTime.toString("dd-MM-yy hh:mm:ss");

    fileSelectPage = new FileSelectPage;
    setPage(Page_Intro, new IntroPage);
    setPage(Page_FileSelect, fileSelectPage);
    setPage(Page_Parse, new ParsePage);
    setStartId(Page_Intro);

    connect(fileSelectPage,SIGNAL(launchParser(QString)),this,SLOT(runParser(QString)));
#ifndef Q_OS_MAC
    setWizardStyle(ModernStyle);
#endif
    setOption(HaveHelpButton, true);
    //setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));
    //connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));
    setWindowTitle(tr("COOT FB"));
}

void FbWizard::runParser(QString filename)
{
    messagesParser->parseFile(filename,minDateTime,maxDateTime);
}
