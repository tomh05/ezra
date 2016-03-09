#include "checkdetailspage.h"

CheckDetailsPage::CheckDetailsPage(Whitelist * whitelist)
{
    setTitle("Check details");

    QGridLayout *layout = new QGridLayout;

    QLabel *label = new QLabel("Please check the details below are correct:");
    label->setWordWrap(true);
    //label->setMargin(10);
    layout->addWidget(label,0,0,1,2);


    QLabel *usernameLabel = new QLabel("Facebook name:");
    layout->addWidget(usernameLabel,1,0);
    QLineEdit * usernameEdit = new QLineEdit(whitelist->getUsername());
    usernameEdit->setReadOnly(true);
    layout->addWidget(usernameEdit,1,1);

    QLabel *startLabel = new QLabel("Experiment start:");
    layout->addWidget(startLabel,2,0);
    QLineEdit * startEdit = new QLineEdit(whitelist->getStartDate().toString("dddd dd MMMM yyyy"));
    startEdit->setReadOnly(true);
    layout->addWidget(startEdit,2,1);

    QLabel *endLabel = new QLabel("Experiment end:");
    layout->addWidget(endLabel,3,0);
    QLineEdit * endEdit = new QLineEdit(whitelist->getEndDate().toString("dddd dd MMMM yyyy"));
    endEdit->setReadOnly(true);
    layout->addWidget(endEdit,3,1);


    if (whitelist->getIsFullVersion()) {

            QLabel *listLabel = new QLabel("Whitelist:");
            layout->addWidget(listLabel,5,0);
            QListWidget * list = new QListWidget();
            foreach(QString whitelistItem,whitelist->getWhitelist()) {
                    list->addItem(whitelistItem);
            }
            layout->addWidget(list,5,1,1,1);
    }

    QLabel *checkboxLabel = new QLabel("<b>Bonus Stats (Optional)</b>");
    QCheckBox * checkbox = new QCheckBox("Calculate and tell me how many messages I sent and received in 2015");
    checkbox->setChecked(true);
    layout->addWidget(checkboxLabel,6,0,1,2);
    layout->addWidget(checkbox,7,0,1,2);

    registerField("countyear",checkbox);
    QString checkBoxText;
    if (whitelist->getIsFullVersion()) {
        checkBoxText = "<em>(This will involve counting your messages only, we will not collect any extra message content if you check this.)</em>";
    } else {
        checkBoxText = "<em>(This will involve counting your messages only, we will not collect any message content if you check this.)</em>";
    }
    QLabel *checkboxLabel2 = new QLabel(checkBoxText);
    checkboxLabel2->setWordWrap(true);
    layout->addWidget(checkboxLabel2,8,0,1,2);




    setLayout(layout);

}
