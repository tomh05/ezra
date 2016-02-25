#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>


class IntroPage : public QWizardPage
{
    Q_OBJECT
public:
    IntroPage();


public slots:
    void pgpFound(bool wasFound);
private:
    bool isComplete() const;
    bool pgpWasFound;
    QLabel * label;
};

#endif // INTROPAGE_H
