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

    label2 = new QLabel("<b>Total Progress</b>");

    label3 = new QLabel("Current Thread");



    progressBar = new QProgressBar();
    subProgressBar = new QProgressBar();


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(introLabel);
    layout->addWidget(statusLabel);
    layout->addWidget(label2);
    layout->addWidget(progressBar);
    layout->addWidget(label3);
    layout->addWidget(subProgressBar);

    setLayout(layout);
}

bool ParsePage::isComplete() const
{
    qDebug()<<"isComplete called";
    //emit completeChanged();
    return (doneParsing);
}

void ParsePage::updateStatus(QString status, int percent, int subPercent) {
    statusLabel->setText(status);
    progressBar->setValue(percent);
    subProgressBar->setValue(subPercent);
}
