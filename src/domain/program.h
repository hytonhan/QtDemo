#ifndef PROGRAM_H
#define PROGRAM_H
#include <QString>

class Program
{
private:
    QString id_;
    QString name_;
public:
    Program(const QString& id,
            const QString& name);

    const QString& name() const { return name_;};
    const QString& id() const {return id_;};
};

#endif // PROGRAM_H
