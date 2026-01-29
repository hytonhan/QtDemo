#ifndef OPETTAJAADAPTER_H
#define OPETTAJAADAPTER_H

#pragma once

#include "koulutusohjelmanentiteetti.h"
#include "../domain/teacher.h"

class OpettajaAdapter : public KoulutusOhjelmanEntiteetti
{
public:
    explicit OpettajaAdapter(const Teacher& o) : teacher_(o) {}
    int id() const override { return teacher_.id().toInt(); }
    QString displayName() const override { return teacher_.fullName(); }
    const Teacher& entity() const { return teacher_; }
private:
    Teacher teacher_;
};

#endif // OPETTAJAADAPTER_H
