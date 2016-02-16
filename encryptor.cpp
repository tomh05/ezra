#include "encryptor.h"

encryptor::encryptor(QObject *parent) : QObject(parent)
{

    QCA::Initializer init;
    if (!QCA::isSupported("openpgp")) {
        qDebug()<<"OpenPGP is not supported!";
    }

    QFile pubkey("pubkey.asc");
    if(!pubkey.open(QFile::ReadOnly | QFile::Text))
        throw std::exception();
    QString pubkey_str = pubkey.readAll();
    qDebug() << "pubkey_str:\n"<< pubkey_str;
    pubkey.flush();
    pubkey.close();

    QCA::ConvertResult cr;
    pubKey = QCA::PGPKey::fromString(pubkey_str,&cr);


    if(cr != QCA::ConvertGood) {
        throw std::exception();
    }

    qDebug()<<pubKey.toString();



}

void encryptor::encrypt(QString string)
{


    QCA::SecureMessageKey to;
    to.setPGPPublicKey(pubKey);
    QCA::OpenPGP pgp;
    QCA::SecureMessage msg(&pgp);


    msg.setRecipient(to);
    msg.setFormat(QCA::SecureMessage::Ascii);
    msg.startEncrypt();
    msg.update(string.toUtf8());
    msg.end();
    msg.waitForFinished(2000);
    QByteArray crpt = msg.read();
    qDebug() << QString::fromUtf8(crpt);


}


