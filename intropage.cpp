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
        if (whitelist->getIsFullVersion()) {
            label->setText("<p>Hi "
                           + whitelist->getUsername().split(" ").first()
                           +",</p>"
                            "<p>As you know, during the week of your phone trial, we gathered all the Facebook messages from you and your Whitelisted contacts."
                            " Unfortunately, although the messages themselves came through fine, the times and dates were mixed up, making them invalid for the experiment.</p>"
                          "<p>This tool is going to gather those same messages (and ONLY those messages) again, to complete the experiment.</p>"
                          "<p>As a bonus, if you choose this tool can also work out the number of messages you sent and received in the whole of 2015."
                            " We tested it on our production team, and the record to beat is 6,075 sent messages!</p>"
                          "<p>Thanks again for taking part in the Child of Our Time social media experiment!</p>"
                            "<br/><p>The CoOT team</p> "
                            "");
        } else {
            label->setText("<p>Hi "
                           + whitelist->getUsername().split(" ").first()
                           +",</p>"
                            "<p>As you know, during the week of your phone trial, the app counted the number of messages you sent and received,"
                            " and what time of day you sent and received them. (We did not collect any of the message content, just the total numbers.) </p>"
                          "<p>Unfortunately, the times and dates were mixed up, making them invalid for the experiment.</p>"
                          "<p>This tool is going to count those same messages again, to complete the experiment."
                            " (Once again, we will not collect any of the message content, just the total numbers.)</p>"
                          "<p>As a bonus, if you choose this tool can also work out the number of messages you sent and received in the whole of 2015."
                            " We tested it on our production team, and the record to beat is 6,075 sent messages!</p>"
                          "<p>Thanks again for taking part in the Child of Our Time social media experiment!</p>"
                            "<br/><p>The CoOT team</p> "
                            "");
        }

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
