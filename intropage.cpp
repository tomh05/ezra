#include "intropage.h"

IntroPage::IntroPage(Whitelist *wl)
{
    whitelist=wl;
    setTitle("Welcome");
    pgpWasFound = false;

    label = new QLabel("Please wait, checking for PGP tool...");
    label->setWordWrap(true);


    textedit = new QTextEdit();
    textedit->setReadOnly(true);
    textedit->hide();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(textedit);

    setLayout(layout);
}

void IntroPage::pgpFound(bool wasFound, QString status)
{
    pgpWasFound = wasFound;
    if (pgpWasFound) {
        label->setText("<p>Hi "
                       + whitelist->getUsername().split(" ").first()
                       +",</p>"
                        "<p>This tool analyses your Facebook messages. Only data that you've already agreed to send to us in your consent form will be extracted by it."
                        " It will take about 20 minutes to use, though you can go off and do something else while it processes the data.</p> "
                      "<p>Thanks again for agreeing to take part in the Child of our Time social media experiment!</p>"
                        "<br/><p>The CooT team</p> "
                        "");
    } else {

        label->setText("Error: we couldn't find an installation of GnuPG.<br /><br /> It's needed to encrypt your data. Install GnuPG and then run this app again. If you're still having problem, please email the text below to us and we'll look into it.");
        textedit->setText(status);
        textedit->show();
    }
    emit completeChanged();

}


bool IntroPage::isComplete() const
{
    return pgpWasFound;
}
