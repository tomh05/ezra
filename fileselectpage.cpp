#include "fileselectpage.h"

FileSelectPage::FileSelectPage()
{
    setTitle("Select a file");

    QLabel *label = new QLabel("Select a file");
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
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

    messagesFilepath = QFileDialog::getOpenFileName(this, "Open Messages File", "/Users/tomh/Downloads", "Facebook Message File (*.html *.htm)");
    if (messagesFilepath != "") {
    emit completeChanged();
    statusLabel->setText("File selected");
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
