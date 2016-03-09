#ifndef PARSEPAGE_H
#define PARSEPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QVBoxLayout>
#include <messagesparser.h>
#include <QDebug>
#include <QProgressBar>
#include "whitelist.h"

class ParsePage : public QWizardPage
{
    Q_OBJECT
public:
    ParsePage(Whitelist * wl);

public slots:
    void updateStatus(QString status,int percent,int subPercent);

private:
    bool isComplete() const;

    bool doneParsing;
    QLabel *statusLabel, *label2,*label3;
    QProgressBar *progressBar,*subProgressBar;
};

#endif // PARSEPAGE_H
