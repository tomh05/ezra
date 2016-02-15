#include "fbwizard.h"

FbWizard::FbWizard(MessagesParser * _mp, QWidget *parent)
    : QWizard(parent)
{
    messagesParser = _mp;

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
    messagesParser->parseFile(filename);
}
