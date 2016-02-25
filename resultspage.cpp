#include "resultspage.h"

ResultsPage::ResultsPage()
{
    setTitle("Results");

    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel("<p><b>Great! Your messages have been analysed :)</b></p>"
                               "<p>The results have been securely encrypted to make sure they can only be interpreted on our production server. In case you're curious, here they are:</p> ");
    label->setWordWrap(true);
    layout->addWidget(label);


    text = new QTextEdit();
    text->setReadOnly(true);
    text->setText("results\n more resultss\n more results\n s\n more results\n s\n more results\n s\n more results\n s\n more results\n s\n more results\n s\n more results\n s\n more results\n s\n more results\n \n more results\n more results\n more results\n more results");

    layout->addWidget(text);

        QLabel *label2 = new QLabel("<p>The final step is to <b>save and send</b> the encryped data to us.</p>"
                               "<p>Click the button below to save the file. Please send it to us by emailing to matilda.hay@bbc.co.uk, or as an attachemnt on facebook messenger. <b>Thanks!</b></p> ");
    label2->setWordWrap(true);
    layout->addWidget(label2);



    QPushButton *saveButton = new QPushButton("Save my Encrypted Data");
    layout->addWidget(saveButton);
    connect(saveButton,SIGNAL(clicked(bool)),this,SLOT(launchFilePicker()));

    setLayout(layout);


}

void ResultsPage::setText(QString str)
{
    resultsData = str;
    text->setText(resultsData);

}

void ResultsPage::launchFilePicker() {
    qDebug()<<"launched";
    QString username = "username-to-fill-in";
    QString savePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+ "/" +username + "-encrypted.txt";

    filepath = QFileDialog::getSaveFileName(this, "Save your data", savePath, "Facebook Message File (*.txt)");
    qDebug()<<filepath;
    if (filepath != "") {
        //if (!filepath.endsWith(".encrypted.txt"))
        //    filepath += ".encrypted.txt";
    //statusLabel->setText("File selected");
    //filepathLineEdit->setText(messagesFilepath);
    QFile outFile(filepath);
    if(!outFile.open(QFile::WriteOnly | QFile::Text))
        qDebug()<<"Can't open file!";

    outFile.write(resultsData.toUtf8());
    outFile.close();

    emit completeChanged();
    }
    //parseButton->setEnabled(true);


}
bool ResultsPage::isComplete() const
{
    qDebug()<<"isComplete called";
    //emit completeChanged();
    return (filepath != "");
}


