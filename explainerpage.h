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
    ExplainerPage(QString title = "", QString _text = "", QString imagePath = "");
    void setText(const QString &value);

private:
    QString text;
};

#endif // EXPLAINERPAGE_H
