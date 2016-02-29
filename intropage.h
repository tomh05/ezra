#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "whitelist.h"
#include <QTextEdit>


class IntroPage : public QWizardPage
{
    Q_OBJECT
public:
    IntroPage(Whitelist* wl);


public slots:
    void pgpFound(bool wasFound,QString status);
private:
    bool isComplete() const;
    bool pgpWasFound;
    QLabel * label;
    Whitelist* whitelist;
    QTextEdit * textedit;
};

#endif // INTROPAGE_H
