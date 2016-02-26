#include "fileselectpage.h"

FileSelectPage::FileSelectPage()
{
    setTitle("Load messages file");

    QVBoxLayout *layout = new QVBoxLayout;



    QLabel *label = new QLabel("That's the hard bit over! We're now ready to process the messages file.");
    label->setWordWrap(true);
    layout->addWidget(label);



    filepathLineEdit = new QLineEdit();
    filepathLineEdit->setDisabled(true);
    layout->addWidget(filepathLineEdit);
    //registerField("filepath*",filepathLineEdit);

    QPushButton *selectFilesButton = new QPushButton("Select Messages File");
    layout->addWidget(selectFilesButton);

    QLabel *label2 = new QLabel("<p>Press the button above and select the messages file."
                               " It will be in the folder you unzipped in the previous step, inside the <em>html</em> subfolder.</p>"
                                "<p> When you've found it, your window should look something like this:</p>");
    label2->setWordWrap(true);
    layout->addWidget(label2);


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
    layout->addWidget(imageLabel);



    statusLabel = new QLabel("");
    statusLabel->setWordWrap(true);

    layout->addWidget(statusLabel);

    //parseButton = new QPushButton("Analyse the data!");
    //parseButton->setDisabled(true);

    //layout->addWidget(parseButton);


    connect(selectFilesButton,SIGNAL(clicked(bool)),this,SLOT(launchFilePicker()));
    //connect(parseButton,SIGNAL(clicked(bool)),this,SLOT(parseButtonPressed()));
    setLayout(layout);
}


void FileSelectPage::launchFilePicker() {

    messagesFilepath = QFileDialog::getOpenFileName(this, "Open Messages File", "/Users/tomh/Downloads", "Facebook Message File (messages.htm)");
    if (messagesFilepath != "") {
    emit completeChanged();
    statusLabel->setText("<span style='color:#0A0'> Great! Press next to begin analysing your data...</span>");
    filepathLineEdit->setText(messagesFilepath);
    }
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
