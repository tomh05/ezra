#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <QObject>
#include <QIODevice>
//#include <QtCrypto>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QStandardPaths>
//#include "botan.h"

//using namespace Botan;

class Encryptor : public QObject
{
    Q_OBJECT
public:
    explicit Encryptor(QObject *parent = 0);


signals:
    void finishedEncrypting(QString result);

public slots:
    void encrypt(QString string);
private slots:
    void loadedKeys(int exitCode,QProcess::ExitStatus status);
    void encrypted(int exitCode);



private:
    //QCA::PGPKey pubKey;
    QProcess *loadProcess, *encryptProcess;
    //SecureVector<byte> mSalt;
    //QString mPassword;
    //QString hash(QString data);
    QString tempPath;
    QFile plainFile;



};

#endif // ENCRYPTOR_H
