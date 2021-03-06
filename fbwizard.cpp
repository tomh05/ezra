#include "fbwizard.h"

FbWizard::FbWizard(QWidget *parent)
    : QWizard(parent)
{
    whitelist = new Whitelist;
    fileSelectPage = new FileSelectPage;
    parsePage = new ParsePage(whitelist);
    resultsPage = new ResultsPage;
    introPage = new IntroPage(whitelist);


    connect(resultsPage,SIGNAL(saveComplete()),this,SLOT(onSaveComplete()));

    messagesParser = new MessagesParser;
    //messagesParser->moveToThread(&messagesParserThread);
    //connect(&messagesParserThread,SIGNAL(finished()),messagesParser,SLOT(deleteLater()));
    connect(this, SIGNAL(parseFile(QString,Whitelist*,bool)), messagesParser, SLOT(parseFile(QString,Whitelist*,bool)));
    connect(messagesParser, SIGNAL(finishedParsing(QJsonDocument)), this, SLOT(onFinishedParsing(QJsonDocument)));
    //messagesParserThread.start();

    encryptor = new Encryptor;
    encryptor->moveToThread(&encryptorThread);
    connect(&encryptorThread,SIGNAL(finished()),encryptor,SLOT(deleteLater()));
    connect(this, SIGNAL(checkPgp()), encryptor, SLOT(checkPgp()));
    connect(this, SIGNAL(encrypt(QString)), encryptor, SLOT(encrypt(QString)));
    connect(encryptor, SIGNAL(pgpFound(bool,QString)), introPage, SLOT(pgpFound(bool,QString)));
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
    /*
    setPage(Page_How, new ExplainerPage("How this app works",
                                        "<p>We want to be transparent about how we are handling your data, so here is the process the app uses. (Don't worry, we'll guide you through each step!). </p>"
                                        "<ol><li><p>You download an archive of your Facebook data</p></li>"
                                        "<li><p>You feed the messages archive file into this app</p></li>"
                                        "<li><p>The app analyses the file for data.</p></li>"
                                        "<li><p>You will be given an encrypted file of your data which you can email to us.</p></li>"
                                        "</ol>"
                                        "<p>All messages that aren't part of the trial are ignored and not processed.</p>"
                                        ,":/r/images/process.png"));
                                        */
    setPage(Page_CheckDetails, new CheckDetailsPage(whitelist));
    /*
    if (whitelist->getIsFullVersion()) {
    setPage(Page_Explainer, new ExplainerPage("Our promise",
                                              "We promise to:"
                                              "<ul>"
                                              "<li>Only gather data from inside your trial period.</li>"
                                              "<li>Not store messages from anyone who wasn't in your whitelist</li>"
                                              "<li>Not store the names of any of your friends who weren't in your whitelist.</li>"
                                              "</ul>"));
    } else {
     setPage(Page_Explainer, new ExplainerPage("Our promise",
                                              "We promise to:"
                                              "<ul>"
                                              "<li>Only gather data from inside your trial period.</li>"
                                              "<li>Not read the content of any of your messages.</li>"
                                              "<li>Not store the names of any of your friends.</li>"
                                              "</ul>"));

    }
    */
    setPage(Page_GetFacebookDump1, new ExplainerPage("Getting hold of your Facebook data",
                                                     "<h3>Step 1</h3> <p>Visit <a href='http://www.facebook.com/settings' >www.facebook.com/settings</a> in your web browser.</p><p> Click on <b>Download a copy</b> of your facebook data.</p>",":/r/images/settings-view.png"));
    setPage(Page_GetFacebookDump2, new ExplainerPage("Getting hold of your Facebook data",
                                                     "<h3>Step 2</h3> Click on <b>Start my Archive</b>. Enter your password when it asks.",
                                                     ":/r/images/archive.png"));
    setPage(Page_GetFacebookDump3, new ExplainerPage("Getting hold of your Facebook data",
                                                     "<h3>Step 3</h3> <p><b>Facebook will send you an email</b> when your data is ready to download. You will have to <b>wait 10 minutes</b> or so.</p><p> When the email arrives, click the link in it.</p>",":/r/images/email.png"));
    setPage(Page_GetFacebookDump4, new ExplainerPage("Getting hold of your Facebook data",
                                                     "<h3>Step 4</h3> <p> Click on <b>Download Archive</b>. Enter your password when it asks.</p>",
                                                     ":/r/images/download.png"));
#ifdef Q_OS_MAC
    setPage(Page_GetFacebookDump5, new ExplainerPage("Unzip the file","<h3>Step 5</h3> <p>Find the zip file in your downloads folder and double click it to unzip it into a folder.</p>",":/r/images/extract-mac.png"));
#else
    setPage(Page_GetFacebookDump5, new ExplainerPage("Unzip the file","<h3>Step 5</h3> <p>Find the zip file in your downloads folder, right-click and choose 'Extract All' and follow instructions to unzip it into a folder.</p>",":/r/images/extract-win.png"));
#endif
    setPage(Page_FileSelect, fileSelectPage);
    setPage(Page_Parse, parsePage);
    setPage(Page_Results, resultsPage);
    setPage(Page_Thanks, new ExplainerPage("Thanks","<h3>All saved!</h3><p> Please email the encryped file to <a href='mailto:matilda.hay@bbc.co.uk'>matilda.hay@bbc.co.uk</a>, or as an attachment on Facebook messenger. Then you're all done!</p> <b>Thanks!</b>"));

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
    emit parseFile(filename,whitelist,field("countyear").toBool());
    QList<QWizard::WizardButton> button_layout;
    button_layout << QWizard::Stretch;
    setButtonLayout(button_layout);
    connect(messagesParser,SIGNAL(updateProgress(QString,int,int)),parsePage,SLOT(updateStatus(QString,int,int)));
}

void FbWizard::onFinishedParsing(QJsonDocument doc)
{
    qDebug()<<"Finished parsing";
    messagesJsonDoc = doc;
    sent = doc.object()["sent"].toInt();
    received = doc.object()["received"].toInt();
    qDebug()<<doc.toJson();
    connect(encryptor,SIGNAL(updateProgress(QString,int,int)),parsePage,SLOT(updateStatus(QString,int,int)));
    emit encrypt(QString(messagesJsonDoc.toJson()));
}

void FbWizard::onFinishedEncrypting(QString encryptedString)
{
    qDebug()<<"Finished encrypting";
    qDebug()<< encryptedString;
    //emit upload(encryptedString);
    QList<QWizard::WizardButton> button_layout;
    button_layout << QWizard::Stretch << QWizard::NextButton;
    setButtonLayout(button_layout);
    resultsPage->setText(encryptedString);
    resultsPage->setTotals(sent,received);
    resultsPage->setUsername(whitelist->getUsername().replace(" ",""));
    this->next();
}

void FbWizard::onFinishedUploading(QString result)
{
    qDebug()<<"Finished uploading";
    qDebug()<< result;
}

void FbWizard::onSaveComplete()
{
    next();
}
