#include <QApplication>
#include "fbwizard.h"
#include "messagesparser.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.addLibraryPath("/usr/local/lib/qca-qt5/");

    FbWizard fbWizard;
    fbWizard.show();

    return a.exec();
}
