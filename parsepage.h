#ifndef PARSEPAGE_H
#define PARSEPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QVBoxLayout>
#include <messagesparser.h>
#include <QDebug>
#include <QProgressBar>

class ParsePage : public QWizardPage
{
    Q_OBJECT
public:
    ParsePage();

public slots:
    void updateStatus(QString status,int percent);

private:
    bool isComplete() const;

    bool doneParsing;
    QLabel *statusLabel;
    QProgressBar *progressBar;
};

#endif // PARSEPAGE_H
