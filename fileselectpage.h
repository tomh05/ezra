#ifndef FILESELECTPAGE_H
#define FILESELECTPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>
#include <QDebug>
#include <QPixmap>


class FileSelectPage : public QWizardPage
{
    Q_OBJECT
public:
    FileSelectPage();

private slots:
    void launchFilePicker();
    void parseButtonPressed();


signals:
    void launchParser(QString);

private:
    QString messagesFilepath;
    QPushButton *parseButton;
    QLabel *statusLabel;

    QLineEdit *filepathLineEdit;


    bool isComplete() const;
    bool validatePage();
};

#endif // FILESELECTPAGE_H
