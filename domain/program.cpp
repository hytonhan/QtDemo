#include "program.h"

Program::Program(QString id, QString name)
    : id_(std::move(id))
    , name_(std::move(name))
{ }
