#ifndef SCHOOL_H
#define SCHOOL_H

#include <QString>

class School
{
public:
    School();
    School(QString id, QString name);

    const QString& name() const { return name_;};
    const QString& id() const {return id_;};
private:
    QString name_;
    QString id_;
};

#endif // SCHOOL_H
