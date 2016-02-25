#ifndef CHECKDETAILSPAGE_H
#define CHECKDETAILSPAGE_H

#include <QObject>
#include <QGridLayout>
#include <QWizardPage>
#include <QLineEdit>
#include "whitelist.h"
#include <QLabel>
#include <QListWidget>
#include <QCheckBox>

class CheckDetailsPage : public QWizardPage
{
    Q_OBJECT
public:
    CheckDetailsPage(Whitelist *whitelist);
};

#endif // CHECKDETAILSPAGE_H
