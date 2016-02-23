#include "explainerpage.h"

ExplainerPage::ExplainerPage()
{
    setTitle("Our Promise");

    QLabel *label = new QLabel("We will:");
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    setLayout(layout);
}
