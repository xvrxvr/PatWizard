#ifndef GROBJECTSTUB_H
#define GROBJECTSTUB_H

#include <QVector>
#include "gr_object.h"

class GrObjectStub : public GrObject
{
private:
    QVector<Constrain> constrains;
    QVector<GrShape> shapes;
public:
    GrObjectStub();
    void addConstrain(const Constrain c);
    void addShape(const GrShape sh);
    virtual QVector<GrShape> get_image();
    virtual QVector<Constrain> get_constrains();
};

#endif // GROBJECTSTUB_H
