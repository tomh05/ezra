#ifndef FBWIZARD_H
#define FBWIZARD_H

#include <QWizard>
#include "messagesparser.h"
#include "fileselectpage.h"
#include "intropage.h"
#include "parsepage.h"
#include <QDebug>



class FbWizard : public QWizard
{
    Q_OBJECT
public:
    FbWizard(MessagesParser * _mp, QWidget *parent = 0);
    enum {Page_Intro, Page_FileSelect, Page_Parse};

    MessagesParser * messagesParser;
    FileSelectPage* fileSelectPage;

private slots:
    void runParser(QString filename);

private:
    QDateTime minDateTime, maxDateTime;

};

#endif // FBWIZARD_H
