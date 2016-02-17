#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <QObject>
#include <QIODevice>
//#include <QtCrypto>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include "botan.h"

using namespace Botan;

class Encryptor : public QObject
{
    Q_OBJECT
public:
    explicit Encryptor(QObject *parent = 0);


signals:
    void finishedEncrypting(QString result);

public slots:
    void encrypt(QString string);

private:
    //QCA::PGPKey pubKey;
    SecureVector<byte> mSalt;
    QString mPassword;
    QString hash(QString data);



};

#endif // ENCRYPTOR_H
