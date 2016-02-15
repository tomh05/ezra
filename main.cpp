#include "mainwindow.h"
#include <QApplication>
#include "fbwizard.h"
#include "messagesparser.h"





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MessagesParser * messagesParser = new MessagesParser;

    FbWizard fbWizard(messagesParser);
    fbWizard.show();

    return a.exec();
}
