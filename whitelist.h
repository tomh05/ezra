#ifndef WHITELIST_H
#define WHITELIST_H

#include <QObject>

class Whitelist : public QObject
{
    Q_OBJECT
public:
    explicit Whitelist(QObject *parent = 0);
    QStringList getWhitelist();
    bool searchFor(QString candidate);

signals:

public slots:

private:
    QStringList whitelist;
};

#endif // WHITELIST_H
