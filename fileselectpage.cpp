#include "fileselectpage.h"

FileSelectPage::FileSelectPage()
{
    setTitle("Load messages file");

    QVBoxLayout *layout = new QVBoxLayout;



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

    QLabel *label = new QLabel("Press the button below and select the messages file."
                               " It will be inside the <em>html</em> folder in the Facebook archive you downloaded.");
    label->setWordWrap(true);
    layout->addWidget(label);



    filepathLineEdit = new QLineEdit();
    filepathLineEdit->setDisabled(true);
    layout->addWidget(filepathLineEdit);
    //registerField("filepath*",filepathLineEdit);

    QPushButton *selectFilesButton = new QPushButton("Select Messages File");
    layout->addWidget(selectFilesButton);


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
