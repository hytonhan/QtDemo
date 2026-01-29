#include "school.h"

School::School()
    : name_("TAMK")
{}

School::School(QString id, QString name)
    : id_(id)
    , name_(name)
{}
