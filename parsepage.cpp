#include "parsepage.h"

ParsePage::ParsePage()
{
    doneParsing = false;
    setTitle("Parsing message...");
    qDebug()<<"Constructor for page"<<endl;
    QLabel * introLabel = new QLabel("This process may take a few minutes.");
    introLabel->setWordWrap(true);

    statusLabel = new QLabel("");
    statusLabel->setWordWrap(true);

    progressBar = new QProgressBar();


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(introLabel);
    layout->addWidget(statusLabel);
    layout->addWidget(progressBar);

    setLayout(layout);
}

bool ParsePage::isComplete() const
{
    qDebug()<<"isComplete called";
    //emit completeChanged();
    return (doneParsing);
}

void ParsePage::updateStatus(QString status,int percent) {
    statusLabel->setText(status);
    progressBar->setValue(percent);
}
