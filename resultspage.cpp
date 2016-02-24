#include "resultspage.h"

ResultsPage::ResultsPage()
{
    setTitle("Results");

    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel("Your messages have been analysed. ");
    label->setWordWrap(true);
    layout->addWidget(label);


    text = new QTextEdit();
    text->setReadOnly(true);
    text->setText("results\n more resultss\n more results\n s\n more results\n s\n more results\n s\n more results\n s\n more results\n s\n more results\n s\n more results\n s\n more results\n s\n more results\n \n more results\n more results\n more results\n more results");

    layout->addWidget(text);

    QPushButton *saveButton = new QPushButton("Save my Encrypted Data");
    connect(saveButton,SIGNAL(clicked(bool)),this,SLOT(launchFilePicker()));
    layout->addWidget(saveButton);

    setLayout(layout);


}

void ResultsPage::setText(QString str)
{
    text->setText(str);

}

void ResultsPage::launchFilePicker() {

    QString filepath = QFileDialog::getSaveFileName(this, "Save Messages File", "/Users/tomh/Downloads", "Facebook Message File (*.html *.htm)");
    if (filepath != "") {
    //emit completeChanged();
    //statusLabel->setText("File selected");
    //filepathLineEdit->setText(messagesFilepath);
    }
    //parseButton->setEnabled(true);


}

