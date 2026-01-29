#ifndef OPISKELIJAADAPTER_H
#define OPISKELIJAADAPTER_H

#pragma once

#include "koulutusohjelmanentiteetti.h"
#include "../domain/student.h"

class OpiskelijaAdapter : public KoulutusOhjelmanEntiteetti
{
public:
    explicit OpiskelijaAdapter(const Student& o) : opiskelija_(o) {}
    int id() const override { return opiskelija_.id().toInt(); }
    QString displayName() const override { return opiskelija_.fullName(); }
    const Student& entity() const { return opiskelija_; }
private:
    Student opiskelija_;
};

#endif // OPISKELIJAADAPTER_H
