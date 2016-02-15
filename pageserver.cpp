#include "pageserver.h"

PageServer::PageServer(QWidget *parent) : QWidget(parent)
{

}


QWizardPage * PageServer::createSelectFilePage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle("Select a file");

    QLabel *label = new QLabel("Select a file");
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    QPushButton *selectFilesButton = new QPushButton("Select Messages File");
    layout->addWidget(selectFilesButton);

    connect(selectFilesButton,SIGNAL(clicked(bool)),this,SLOT(launchFilePicker()));

    page->setLayout(layout);

    return page;
}

void PageServer::launchFilePicker() {

    messagesFilepath = QFileDialog::getOpenFileName(this, "Open Messages File", "/home/", "Facebook Message File (*.html)");

}
