#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <QObject>
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
    void updateProgress(QString,int,int);
    void pgpFound(bool wasFound,QString status);

public slots:
    void encrypt(QString string);
    void checkPgp();
private slots:
    void loadedKeys(int exitCode,QProcess::ExitStatus status);
    void checkFinished(int exitCode,QProcess::ExitStatus status);
    void encrypted(int exitCode);
    void response();
    void error(QProcess::ProcessError e);
    void checkError(QProcess::ProcessError e);



private:
    //QCA::PGPKey pubKey;
    QProcess *loadProcess, *encryptProcess, *checkProcess;
    //SecureVector<byte> mSalt;
    //QString mPassword;
    //QString hash(QString data);
    QString tempPath;
    QFile plainFile;



};

#endif // ENCRYPTOR_H
