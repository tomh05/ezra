#include "parsepage.h"

ParsePage::ParsePage(Whitelist * wl)
{
    doneParsing = false;
    setTitle("Message Selection...");
    QLabel * introLabel;


    if (wl->getIsFullVersion()) {
    introLabel = new QLabel("Sit back and relax, this process may take a few minutes."
                                     " The tool is selecting only the messages that you have consented to.");
    } else {

    introLabel = new QLabel("Sit back and relax, this process may take a few minutes."
                                     " The tool is counting your messages.");
    }
    introLabel->setWordWrap(true);

    statusLabel = new QLabel("");
    statusLabel->setWordWrap(true);

    label2 = new QLabel("<b>Total Progress</b>");

    label3 = new QLabel("Progress");



    progressBar = new QProgressBar();
    subProgressBar = new QProgressBar();


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(introLabel);
    layout->addWidget(statusLabel);
    layout->addWidget(label3);
    layout->addWidget(subProgressBar);
    layout->addWidget(label2);
    layout->addWidget(progressBar);

    setLayout(layout);
}

bool ParsePage::isComplete() const
{
    qDebug()<<"isComplete called";
    //emit completeChanged();
    return (doneParsing);
}

void ParsePage::updateStatus(QString status, int percent, int subPercent) {
    //statusLabel->setText(status);
    progressBar->setValue(percent);
    subProgressBar->setValue(subPercent);
}
