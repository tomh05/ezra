#ifndef EXPLAINERPAGE_H
#define EXPLAINERPAGE_H

#include <QWizardPage>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

class ExplainerPage : public QWizardPage
{
    Q_OBJECT
public:
    ExplainerPage(QString title = "", QString text = "", QString imagePath = "");
};

#endif // EXPLAINERPAGE_H
