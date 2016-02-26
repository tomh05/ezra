#include "resultspage.h"

ResultsPage::ResultsPage()
{
    setTitle("Results");
    username = "participant";

    QVBoxLayout *layout = new QVBoxLayout;

    resultsLabel = new QLabel("");
    layout->addWidget(resultsLabel);

    QLabel *label = new QLabel("<p><b>Great! Your messages have been analysed :)</b></p>"
                               "<p>The results have been securely encrypted to make sure they can only be interpreted on our production server. In case you're curious, here they are:</p> ");
    label->setWordWrap(true);
    layout->addWidget(label);


    text = new QTextEdit();
    text->setReadOnly(true);
    text->setText("Error. Please contact CooT team.");

    layout->addWidget(text);

        QLabel *label2 = new QLabel("<p>The final step is to <b>save and send</b> the encryped data to us.</p>"
                               "<p>Click the button below to save the file. Please send it to us by emailing to matilda.hay@bbc.co.uk, or as an attachemnt on Facebook messenger. <b>Thanks!</b></p> ");
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

void ResultsPage::setTotals(int _sent, int _received)
{
    if (_sent>0 || _received>0) {
    resultsLabel->setText(QString("<p>In 2015, you sent <b><span style='color:#060'>%1</span></b> messages, and received <b><span style='color:#009'>%2</span></b> messages.</p>").arg(_sent).arg(_received));
    } else
        resultsLabel->hide();

}

void ResultsPage::launchFilePicker() {
    qDebug()<<"launched";
    QString savePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+ "/" +username + "-encrypted.txt";

    filepath = QFileDialog::getSaveFileName(this, "Save your data", savePath, "Facebook Message File (*.txt)");
    qDebug()<<filepath;
    if (filepath != "") {
        //if (!filepath.endsWith(".encrypted.txt"))
        //    filepath += ".encrypted.txt";
    //statusLabel->setText("File selected");
    //filepathLineEdit->setText(messagesFilepath);
    QFile outFile(filepath);
    if(!outFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug()<<"Can't open file!";
    } else {

    outFile.write(resultsData.toUtf8());
    outFile.close();
    emit saveComplete();
    emit completeChanged();
    }
    }
    //parseButton->setEnabled(true);


}
bool ResultsPage::isComplete() const
{
    qDebug()<<"isComplete called";
    //emit completeChanged();
    return (filepath != "");
}

void ResultsPage::setUsername(QString value)
{
    username = value;
}


