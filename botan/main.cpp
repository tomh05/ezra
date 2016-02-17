#include <QtCore/QCoreApplication>
#include "botanwrapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BotanWrapper cWrapper;

   // QString cPlain = "/home/rootshell/Source/Wraper/test.txt";
   // QString cEncrypted = "/home/rootshell/Source/Wraper/encrypted.txt";
   // QString cDecrypted = "/home/rootshell/Source/Wraper/decrypted.txt";

   // cWrapper.EncryptFile(cPlain,cEncrypted);
   // cWrapper.DecryptFile(cEncrypted,cDecrypted);

    cWrapper.setPassword("!@#$%^&*()_kjnklawh!@ucoi9293");
    cWrapper.setSalt("#$%^&!*@y9sg08dfsdfs");
    QString cEnc = cWrapper.Encrypt("This is my secret :)");

    qDebug() << cEnc;
    qDebug() << cWrapper.Decrypt(cEnc);
    


    return a.exec();
}
