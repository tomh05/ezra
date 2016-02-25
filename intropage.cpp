#include "intropage.h"

IntroPage::IntroPage()
{
    setTitle("Welcome");
    pgpWasFound = false;

    label = new QLabel("Please wait, checking for PGP tool...");
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    setLayout(layout);
}

void IntroPage::pgpFound(bool wasFound)
{
    pgpWasFound = wasFound;
    if (pgpWasFound) {
        label->setText("Welcome");
    } else {

        label->setText("Error: we couldn't find an installation of GnuPG.<br /><br /> It's needed to encrypt your data. Install GnuPG and then run this app again.");
    }
    emit completeChanged();

}


bool IntroPage::isComplete() const
{
    return pgpWasFound;
}
