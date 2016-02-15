#ifndef PAGESERVER_H
#define PAGESERVER_H

#include <QWidget>
#include "QWizardPage"
#include "QLabel"
#include "QVBoxLayout"
#include "QPushButton"
#include "QFileDialog"


class PageServer : public QWidget
{
    Q_OBJECT
public:
    explicit PageServer(QWidget *parent = 0);
    QWizardPage*  createSelectFilePage();

signals:

public slots:

private slots:
    void launchFilePicker();

private:
    QString messagesFilepath;
};

#endif // PAGESERVER_H
