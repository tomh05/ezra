#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <QObject>
#include <QIODevice>
#include <QtCrypto>
#include <QDebug>
#include <QFile>

class encryptor : public QObject
{
    Q_OBJECT
public:
    explicit encryptor(QObject *parent = 0);
    void encrypt(QString string);

signals:

public slots:

private:
    QCA::PGPKey pubKey;


};

#endif // ENCRYPTOR_H
