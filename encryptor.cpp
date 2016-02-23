#include "encryptor.h"

Encryptor::Encryptor(QObject *parent) : QObject(parent)
{



    /*
    //Set the default salt size
    mSalt.resize(48);

    //Set the default salt
    for(int i = 0; i < mSalt.size(); i++)
    {
        mSalt[i] = i;
    }

    //Set the default password
    mPassword = hash("!@&^jdshUG24!T^!@*&!Y@()&^909+!-@!@#07");
    */


    /*
    QCA::Initializer init;
    if (!QCA::isSupported("openpgp")) {
        qDebug()<<"OpenPGP is not supported!";
    }


    QFile pubkey(":/r/coot_pro.asc");
    if(!pubkey.open(QFile::ReadOnly | QFile::Text))
        qDebug()<<"Can't open file!";

    QString pubkey_str = pubkey.readAll();
    pubkey.flush();
    pubkey.close();

    QCA::ConvertResult cr;
    pubKey = QCA::PGPKey::fromString(pubkey_str,&cr);


    if(cr != QCA::ConvertGood) {
        qDebug()<<"Key construction failed!";
    } else {
        qDebug()<<pubKey.toString();

    }
*/



}

void Encryptor::encrypt(QString string)
{

    /*
    try
    {



        //Setup the key derive functions
        PKCS5_PBKDF2 pbkdf2(new HMAC(new SHA_160));
        const u32bit PBKDF2_ITERATIONS = 8192;

        //Create the KEY and IV
        KDF* kdf = get_kdf("KDF2(SHA-1)");

        //Create the master key
        SecureVector<byte> mMaster = pbkdf2.derive_key(48, mPassword.toStdString(), &mSalt[0], mSalt.size(),PBKDF2_ITERATIONS).bits_of();
        SymmetricKey mKey = kdf->derive_key(32, mMaster, "salt1");
        InitializationVector mIV = kdf->derive_key(16, mMaster, "salt2");

        Pipe pipe(get_cipher("AES-256/CBC/PKCS7", mKey, mIV,ENCRYPTION),new Base64_Encoder);
        pipe.process_msg(string.toStdString());
        QString value = QString::fromStdString(pipe.read_all_as_string(0));
        emit finishedEncrypting(value);
    }
    catch(...)
    {
        qDebug()<<"Error encrypting";
    }

    */


    /*

    qDebug() <<"Encrypting " << string << "...";
    qDebug() << QCA::supportedFeatures();
    qDebug() << QCoreApplication::instance()->libraryPaths();
    qDebug("%s", QCA::pluginDiagnosticText().toUtf8().constData());
    // TODO: add crypto folder to library path.


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


    QString cryptString = QString::fromUtf8(crpt);
    qDebug() << cryptString;
    emit finishedEncrypting(cryptString);

    */


    // copy public key file to temp dir
    QFile pubkey(":/r/coot_pro.asc");

    QString tempPath = QDir::tempPath();
    qDebug()<<tempPath;

    QFile::copy(":/r/coot_pro.asc",tempPath+"/coot_pro.asc");

    // Write extracted data to temp dir
    QFile plainFile(tempPath+"/plain.txt");
    plainFile.open(QFile::WriteOnly | QFile::Text);
    plainFile.write(string.toUtf8());
    plainFile.flush();
    plainFile.close();

    // Call PGP to encrypt it

    QString program = "gpg2";
    QStringList arguments;
    arguments << "--homedir" << tempPath;
    arguments << "--recipient" << "0x2EEF71E3";
    arguments << "--armor";
    arguments << "--output" << tempPath + "/encrypted.txt.gpg";
    arguments << "--batch";
    arguments << "--trust-model" << "always";
    arguments << "--encrypt" << tempPath + "/plain.txt";

    myProcess = new QProcess();
    qDebug() << program << arguments;
    connect(myProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(response()));
    connect(myProcess,SIGNAL(readyReadStandardError()),this,SLOT(response()));
    connect(myProcess,SIGNAL(started()),this,SLOT(response()));

    myProcess->setProgram(program);
    myProcess->setArguments(arguments);
    qDebug() << myProcess->arguments();
    qDebug() << myProcess->program();
    myProcess->execute(program,arguments);
    qDebug() << myProcess->errorString();


            //run:  gpg2 --homedir . --recipient 0x2EEF71E3 --armor --output wasteout.txt.gpg --batch --trust-model always --encrypt waste.txt
    // Delete  original file

    plainFile.remove();



    // Load in encrypted file

    //if(!pubkey.open(QFile::ReadOnly | QFile::Text))

    /*

*/
    //QDir::tempPath()

    qDebug()<<"Out!";

    //emit finishedEncrypting(cryptString);


}

void Encryptor::response()
{
    qDebug()<< "resp";
    qDebug()<< myProcess->readAllStandardOutput();
    qDebug()<< myProcess->readAllStandardError();

}




/*QString Encryptor::hash(QString data)
{
    try
    {
        Pipe pipe(new Hash_Filter("SHA-1"));
        pipe.process_msg(data.toStdString());
        QString value = QString::fromStdString(pipe.read_all_as_string(0));
        return value;
    }
    catch(...)
    {
        return "";
    }
}

*/
