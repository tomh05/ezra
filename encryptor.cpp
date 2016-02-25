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


    qDebug() <<"Encrypting " << string << "...";
    // copy public key file to temp dir
    QFile pubkey(":/r/coot_pro.asc");

    tempPath = QDir::tempPath();
    qDebug()<<"Temp path:" << tempPath;

    QFile::copy(":/r/pubring.gpg",tempPath+"/pubring.gpg");

    // Write extracted data to temp dir
    plainFile.setFileName(tempPath+"/plain.txt");
    plainFile.open(QFile::WriteOnly | QFile::Text);
    plainFile.write(string.toUtf8());
    plainFile.flush();
    plainFile.close();

    emit updateProgress("Encrypting messages", 25);

    QString program = "gpg2";
    QStringList loadArguments;
    loadArguments << "--homedir" << tempPath;
    loadArguments << "--import" << tempPath + "/pubring.gpg";

    loadProcess = new QProcess();
    connect(loadProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(loadedKeys(int,QProcess::ExitStatus)));
    connect(loadProcess,SIGNAL(error(QProcess::ProcessError)),this,SLOT(error(QProcess::ProcessError)));
    loadProcess->setWorkingDirectory(tempPath);
    loadProcess->start(program,loadArguments);

    //run:  gpg2 --homedir . --recipient 0x2EEF71E3 --armor --output wasteout.txt.gpg --batch --trust-model always --encrypt waste.txt
    // Delete  original file

}

void Encryptor::loadedKeys(int exitCode,QProcess::ExitStatus status)
{

    qDebug()<< "loaded key, status "<<exitCode;
    qDebug()<< "stdout:"<<loadProcess->readAllStandardOutput();
    qDebug()<<"stderr:" << loadProcess->readAllStandardError();

    emit updateProgress("Encrypting messages", 50);
    qDebug()<< "about to encrypt";
    // Encrypt it
    QString program = "gpg2";
    QStringList encryptArguments;
    encryptArguments << "--homedir" << tempPath;
    encryptArguments << "--recipient" << "0x2EEF71E3";
    encryptArguments << "--armor";
    encryptArguments << "--output" << tempPath + "/encrypted.txt.gpg";
    encryptArguments << "--batch";
    encryptArguments << "--trust-model" << "always";
    encryptArguments << "--encrypt" << tempPath + "/plain.txt";

    encryptProcess = new QProcess();

    connect(encryptProcess,SIGNAL(finished(int)),this,SLOT(encrypted(int)));
    encryptProcess->start(program,encryptArguments);


}

void Encryptor::encrypted(int exitCode)
{

    emit updateProgress("Encrypting messages", 75);
    qDebug()<< "encryption finished with code "<<exitCode<< encryptProcess->readAll();
    plainFile.remove();


    //QFile::copy(tempPath+"/encrypted.txt.gpg",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"/encrypted.txt.gpg");

    // now load file back in to program and delete it
    QFile encryptedFile(tempPath + "/encrypted.txt.gpg");
    if(!encryptedFile.open(QFile::ReadOnly | QFile::Text))
        qDebug()<<"Can't open file!";

    QString encryptedString = encryptedFile.readAll();
    qDebug()<<"file"<<encryptedString;
    encryptedFile.flush();
    encryptedFile.close();
    encryptedFile.remove();


    emit finishedEncrypting(encryptedString);

}

void Encryptor::response()
{
    qDebug()<<"response";

}

void Encryptor::error(QProcess::ProcessError e)
{
     qDebug()<<"error" << e;
    if (e==QProcess::FailedToStart) {
            qDebug() << "could not start program "<< loadProcess->program() << loadProcess->arguments();
    }

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
