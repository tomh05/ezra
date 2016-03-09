#include "fileselectpage.h"

FileSelectPage::FileSelectPage()
{
    setTitle("Load messages file");

    QGridLayout *layout = new QGridLayout;



    QLabel *label = new QLabel("That's the hard bit over! We're now ready to process the messages file.");
    label->setWordWrap(true);
    layout->addWidget(label,0,0,1,2);


    QPixmap image;
#ifdef Q_OS_MAC
    image.load(":/r/images/open-mac.png");
#else
    image.load(":/r/images/open-win.png");
#endif
    image.setDevicePixelRatio(devicePixelRatio());

    QLabel * imageLabel = new QLabel();
    imageLabel->setPixmap(image.scaled(400*devicePixelRatio(),300*devicePixelRatio(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    // set a scaled pixmap to a w x h window keeping its aspect ratio
    layout->addWidget(imageLabel,1,0,1,2);



    QLabel *label2 = new QLabel("<p>Press the button below and select the messages file."
                               " It will be in the folder you unzipped in the previous step, inside the <em>html</em> subfolder.</p>"
                                "<p> When you've found it, your window should look something like the image above.</p>");
    label2->setWordWrap(true);
    layout->addWidget(label2,2,0,1,2);




    filepathLineEdit = new QLineEdit();
    filepathLineEdit->setDisabled(true);
    layout->addWidget(filepathLineEdit,3,0,1,1);
    //registerField("filepath*",filepathLineEdit);

    QPushButton *selectFilesButton = new QPushButton("Select Messages File");
    selectFilesButton->setGeometry(50,50,100,30);
    layout->addWidget(selectFilesButton,3,1,1,1);

    statusLabel = new QLabel("");
    statusLabel->setWordWrap(true);

    layout->addWidget(statusLabel,4,0,1,2);

    //parseButton = new QPushButton("Analyse the data!");
    //parseButton->setDisabled(true);

    //layout->addWidget(parseButton);


    connect(selectFilesButton,SIGNAL(clicked(bool)),this,SLOT(launchFilePicker()));
    //connect(parseButton,SIGNAL(clicked(bool)),this,SLOT(parseButtonPressed()));
    setLayout(layout);
}


void FileSelectPage::launchFilePicker() {

    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    messagesFilepath = QFileDialog::getOpenFileName(this, "Open Messages File", defaultPath, "Facebook Message File (messages.htm)");
    filepathLineEdit->setText(messagesFilepath);
    if (messagesFilepath != "") {
#ifdef Q_OS_MAC
    statusLabel->setText("<span style='color:#0A0'> Great! Press continue...</span>");
#else
    statusLabel->setText("<span style='color:#0A0'> Great! Press next...</span>");
#endif
    } else {

    statusLabel->setText("");
    }
    emit completeChanged();
    //parseButton->setEnabled(true);


}

void FileSelectPage::parseButtonPressed() {
    //emit
    emit launchParser(messagesFilepath);
}

bool FileSelectPage::isComplete() const
{
    qDebug()<<"isComplete called";
    //emit completeChanged();
    return (messagesFilepath != "");
}

bool FileSelectPage::validatePage()
{
    emit launchParser(messagesFilepath);
    return true;
}
