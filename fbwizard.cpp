#include "fbwizard.h"

FbWizard::FbWizard(QWidget *parent)
    : QWizard(parent)
{
    messagesParser = new MessagesParser;
    messagesParser->moveToThread(&messagesParserThread);
    connect(&messagesParserThread,SIGNAL(finished()),messagesParser,SLOT(deleteLater()));
    connect(this, SIGNAL(parseFile(QString,QDateTime,QDateTime)), messagesParser, SLOT(parseFile(QString,QDateTime,QDateTime)));
    connect(messagesParser, SIGNAL(finishedParsing(QJsonDocument)), this, SLOT(onFinishedParsing(QJsonDocument)));
    messagesParserThread.start();

    encryptor = new Encryptor;
    encryptor->moveToThread(&encryptorThread);
    connect(&encryptorThread,SIGNAL(finished()),encryptor,SLOT(deleteLater()));
    connect(this, SIGNAL(encrypt(QString)), encryptor, SLOT(encrypt(QString)));
    connect(encryptor, SIGNAL(finishedEncrypting(QString)), this, SLOT(onFinishedEncrypting(QString)));
    encryptorThread.start();

    /*
     uploader = new Uploader;
    uploader->moveToThread(&uploaderThread);
    connect(&uploaderThread,SIGNAL(finished()),uploader,SLOT(deleteLater()));
    connect(this, SIGNAL(upload(QString)), uploader, SLOT(upload(QString)));
    connect(uploader, SIGNAL(finishedUploading(QString)), this, SLOT(onFinishedUploading(QString)));
    uploaderThread.start();
    */




    minDateTime = QDateTime::fromString("2016-01-10 00:00:00","yyyy-MM-dd hh:mm:ss");
    maxDateTime = QDateTime::fromString("2016-01-20 00:00:00","yyyy-MM-dd hh:mm:ss");
    qDebug()<<minDateTime.toString("dd-MM-yy hh:mm:ss");
    qDebug()<<maxDateTime.toString("dd-MM-yy hh:mm:ss");

    fileSelectPage = new FileSelectPage;
    parsePage = new ParsePage;
    setPage(Page_Intro, new IntroPage);
    setPage(Page_Explainer, new ExplainerPage);
    setPage(Page_FileSelect, fileSelectPage);
    setPage(Page_Parse, parsePage);
    setStartId(Page_Intro);

    //emit upload("Test String!");
    emit encrypt("hi messagesJsonDoc.toJson()");

    connect(fileSelectPage,SIGNAL(launchParser(QString)),this,SLOT(runParser(QString)));
#ifndef Q_OS_MAC
    setWizardStyle(ModernStyle);
#endif
    setOption(HaveHelpButton, false);
    //setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));
    //connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));
    setWindowTitle(tr("COOT FB"));
}

void FbWizard::runParser(QString filename)
{
    emit parseFile(filename,minDateTime,maxDateTime);
    QList<QWizard::WizardButton> button_layout;
    button_layout << QWizard::HelpButton << QWizard::Stretch << QWizard::NextButton;
    setButtonLayout(button_layout);
    connect(messagesParser,SIGNAL(updateProgress(QString,int)),parsePage,SLOT(updateStatus(QString,int)));
}

void FbWizard::onFinishedParsing(QJsonDocument doc)
{
    qDebug()<<"Finished parsing";
    messagesJsonDoc = doc;
    qDebug()<<doc.toJson();
    emit encrypt(QString(messagesJsonDoc.toJson()));
}

void FbWizard::onFinishedEncrypting(QString encryptedString)
{
    qDebug()<<"Finished encrypting";
    qDebug()<< encryptedString;
    //emit upload(encryptedString);
}

void FbWizard::onFinishedUploading(QString result)
{
    qDebug()<<"Finished uploading";
    qDebug()<< result;
}
