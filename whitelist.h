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
    QList<QDateTime> getStartDates() const;
    QList<QDateTime> getEndDates() const;
    bool getIsFullVersion() const;

signals:

public slots:

private:
    QString username;
    QStringList whitelist;
    //QDateTime startDate,endDate, startDate2, endDate2, startDate3, endDate3;
    QList<QDateTime> startDates;
    QList<QDateTime> endDates;
    bool isFullVersion;
};

#endif // WHITELIST_H
