#include "uploader.h"

Uploader::Uploader(QObject *parent) : QObject(parent)
{

}

void Uploader::upload(QString string)
{
    qDebug()<<"uploading";

}
