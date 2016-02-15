#include "intropage.h"

IntroPage::IntroPage()
{
    setTitle("Welcome");

    QLabel *label = new QLabel("Intro Page");
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    setLayout(layout);
}
