#include "school.h"

School::School()
    : name_("TAMK")
{}

School::School(const QString& id,
               const QString& name)
    : id_(id)
    , name_(name)
{}
