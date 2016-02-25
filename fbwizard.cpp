#include "fbwizard.h"

FbWizard::FbWizard(QWidget *parent)
    : QWizard(parent)
{
    whitelist = new Whitelist;
    fileSelectPage = new FileSelectPage;
    parsePage = new ParsePage;
    resultsPage = new ResultsPage;
    introPage = new IntroPage;

    messagesParser = new MessagesParser;
    messagesParser->moveToThread(&messagesParserThread);
    connect(&messagesParserThread,SIGNAL(finished()),messagesParser,SLOT(deleteLater()));
    connect(this, SIGNAL(parseFile(QString,Whitelist*)), messagesParser, SLOT(parseFile(QString,Whitelist*)));
    connect(messagesParser, SIGNAL(finishedParsing(QJsonDocument)), this, SLOT(onFinishedParsing(QJsonDocument)));
    messagesParserThread.start();

    encryptor = new Encryptor;
    encryptor->moveToThread(&encryptorThread);
    connect(&encryptorThread,SIGNAL(finished()),encryptor,SLOT(deleteLater()));
    connect(this, SIGNAL(checkPgp()), encryptor, SLOT(checkPgp()));
    connect(this, SIGNAL(encrypt(QString)), encryptor, SLOT(encrypt(QString)));
    connect(encryptor, SIGNAL(pgpFound(bool)), introPage, SLOT(pgpFound(bool)));
    connect(encryptor, SIGNAL(finishedEncrypting(QString)), this, SLOT(onFinishedEncrypting(QString)));
    encryptorThread.start();

    emit checkPgp();

    /*
     uploader = new Uploader;
    uploader->moveToThread(&uploaderThread);
    connect(&uploaderThread,SIGNAL(finished()),uploader,SLOT(deleteLater()));
    connect(this, SIGNAL(upload(QString)), uploader, SLOT(upload(QString)));
    connect(uploader, SIGNAL(finishedUploading(QString)), this, SLOT(onFinishedUploading(QString)));
    uploaderThread.start();
    */


    setPage(Page_Intro, introPage);
    setPage(Page_How, new ExplainerPage("How this app works",
                                        "<p>We want to be transparent about how we are handling your data, so here is the process the app uses. (Don't worry, we'll guide you through each step!). </p>"
                                        "<ol><li><p>You download an archive of your Facebook data</p></li>"
                                        "<li><p>You feed the messages archive file into this app</p></li>"
                                        "<li><p>The app analyses the file for data.</p></li>"
                                        "<li><p>You will be given an encrypted file of your data which you can email to us.</p></li>"
                                        "</ol>"
                                        "<p>The app analyses the file for data that you have consented to us collecting. All messages that aren't part of the trial are ignored and not processed.</p>"));
    setPage(Page_CheckDetails, new CheckDetailsPage(whitelist));
    setPage(Page_Explainer, new ExplainerPage("Our promise",
                                              "We promise to:"
                                              "<ul><li>Only gather data from inside your trial period.</li></ul>"));
    setPage(Page_GetFacebookDump1, new ExplainerPage("Getting hold of your Facebook data",
                                                     "<h3>Step 1</h3> <p>Visit <a href='http://www.facebook.com/settings' >www.facebook.com/settings</a> in your web browser.</p><p> Click on <b>Download a copy of your facebook data</b>.</p>",":/r/images/settings-view.png"));
    setPage(Page_GetFacebookDump2, new ExplainerPage("Getting hold of your Facebook data",
                                                     "<h3>Step 2</h3> Click on <b>Start my Archive</b>. Enter your password when it asks.",
                                                     ":/r/images/archive.png"));
    setPage(Page_GetFacebookDump3, new ExplainerPage("Getting hold of your Facebook data",
                                                     "<h3>Step 3</h3> <p>Facebook will start gathering your data, and send you an email when it is ready to download. This usually takes 10 minutes or so.</p><p> When the email arrives, click the link at the bottom.</p>",":/r/images/email.png"));
    setPage(Page_GetFacebookDump4, new ExplainerPage("Getting hold of your Facebook data",
                                                     "<h3>Step 4</h3> <p> Click the green button to download your data.</p>",
                                                     ":/r/images/download.png"));
#ifdef Q_OS_MAC
    setPage(Page_GetFacebookDump5, new ExplainerPage("Unzip the file","<h3>Step 5</h3> <p>Find the zip file you have downloaded and double click it to unzip it into a folder.</p>",":/r/images/extract-mac.png"));
#else
    setPage(Page_GetFacebookDump5, new ExplainerPage("Unzip the file","Unzip it",":/r/images/extract-mac.png"));
#endif
    setPage(Page_FileSelect, fileSelectPage);
    setPage(Page_Parse, parsePage);
    setPage(Page_Results, resultsPage);
    setPage(Page_Thanks, new ExplainerPage("Thanks","<h3>Thank you!</h3> <p>Yay! </p>"));

    setStartId(Page_Intro);

    //emit upload("Test String!");
    //emit encrypt("hi messagesJsonDoc.toJson()");

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
    emit parseFile(filename,whitelist);
    QList<QWizard::WizardButton> button_layout;
    button_layout << QWizard::HelpButton << QWizard::Stretch;
    setButtonLayout(button_layout);
    connect(messagesParser,SIGNAL(updateProgress(QString,int)),parsePage,SLOT(updateStatus(QString,int)));
}

void FbWizard::onFinishedParsing(QJsonDocument doc)
{
    qDebug()<<"Finished parsing";
    messagesJsonDoc = doc;
    qDebug()<<doc.toJson();
    connect(encryptor,SIGNAL(updateProgress(QString,int)),parsePage,SLOT(updateStatus(QString,int)));
    emit encrypt(QString(messagesJsonDoc.toJson()));
}

void FbWizard::onFinishedEncrypting(QString encryptedString)
{
    qDebug()<<"Finished encrypting";
    qDebug()<< encryptedString;
    //emit upload(encryptedString);
    QList<QWizard::WizardButton> button_layout;
    button_layout << QWizard::HelpButton << QWizard::Stretch << QWizard::NextButton;
    setButtonLayout(button_layout);
    resultsPage->setText(encryptedString);
    this->next();
}

void FbWizard::onFinishedUploading(QString result)
{
    qDebug()<<"Finished uploading";
    qDebug()<< result;
}
