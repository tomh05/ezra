#include "checkdetailspage.h"

CheckDetailsPage::CheckDetailsPage(Whitelist * whitelist)
{
    setTitle("Check details");

    QGridLayout *layout = new QGridLayout;

    QLabel *label = new QLabel("This app will only analyse data involved in the trial period.If the details below are incorrect, contact us before using this app.");
    label->setWordWrap(true);
    //label->setMargin(10);
    layout->addWidget(label,0,0,1,2);


    QLabel *usernameLabel = new QLabel("Your name:");
    layout->addWidget(usernameLabel,1,0);
    QLineEdit * usernameEdit = new QLineEdit(whitelist->getUsername());
    usernameEdit->setReadOnly(true);
    layout->addWidget(usernameEdit,1,1);

    QLabel *startLabel = new QLabel("Trial start:");
    layout->addWidget(startLabel,2,0);
    QLineEdit * startEdit = new QLineEdit(whitelist->getStartDate().toString("dddd dd MMMM yyyy"));
    startEdit->setReadOnly(true);
    layout->addWidget(startEdit,2,1);

    QLabel *endLabel = new QLabel("Trial end:");
    layout->addWidget(endLabel,3,0);
    QLineEdit * endEdit = new QLineEdit(whitelist->getEndDate().toString("dddd dd MMMM yyyy"));
    endEdit->setReadOnly(true);
    layout->addWidget(endEdit,3,1);


    if (!whitelist->getIsFullVersion()) {

    QLabel *fullLabel = new QLabel("Trial version:");
    layout->addWidget(fullLabel,4,0);
    QString fullText = (whitelist->getIsFullVersion())? "encrypted" : "light";
    QLineEdit * fullEdit = new QLineEdit(fullText);
    fullEdit->setReadOnly(true);
    layout->addWidget(fullEdit,4,1);
    }

    QLabel *listLabel = new QLabel("Whitelist:");
    layout->addWidget(listLabel,5,0);
    QListWidget * list = new QListWidget();
    foreach(QString whitelistItem,whitelist->getWhitelist()) {
    list->addItem(whitelistItem);
    }
    layout->addWidget(list,5,1,1,1);




    setLayout(layout);

}
