#ifndef RESULTSPAGE_H
#define RESULTSPAGE_H

#include <QObject>
#include <QWizardPage>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>

#include <QTextEdit>

class ResultsPage : public QWizardPage
{
public:
    ResultsPage();
    void setText(QString str);

private:
    QTextEdit  * text;

private slots:
    void launchFilePicker();
};

#endif // RESULTSPAGE_H
