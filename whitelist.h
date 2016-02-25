#ifndef WHITELIST_H
#define WHITELIST_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

class Whitelist : public QObject
{
    Q_OBJECT
public:
    explicit Whitelist(QObject *parent = 0);
    QStringList getWhitelist();
    bool searchFor(QString candidate);

    QString getUsername() const;
    QDateTime getStartDate() const;
    QDateTime getEndDate() const;
    bool getIsFullVersion() const;

signals:

public slots:

private:
    QString username;
    QStringList whitelist;
    QDateTime startDate,endDate;
    bool isFullVersion;
};

#endif // WHITELIST_H
