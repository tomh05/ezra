#include "parsepage.h"

ParsePage::ParsePage()
{
    setTitle("Parsing message...");
    qDebug()<<"Constructor for page"<<endl;
    QLabel *label = new QLabel("Intro Page");
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    setLayout(layout);
}
