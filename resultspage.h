#ifndef RESULTSPAGE_H
#define RESULTSPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTextEdit>
#include <QDebug>
#include <QStandardPaths>

class ResultsPage : public QWizardPage
{
    Q_OBJECT

public:
    ResultsPage();
    void setText(QString str);

private slots:
    void launchFilePicker();

private:
    QTextEdit  * text;
    QString filepath;
    bool isComplete() const;
    QString resultsData;


};

#endif // RESULTSPAGE_H
