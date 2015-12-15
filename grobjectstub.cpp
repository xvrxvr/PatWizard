#include "grobjectstub.h"
#include <QDebug>

GrObjectStub::GrObjectStub()
{
    qDebug() << "GrObjectStub created";
}

QVector<Constrain> GrObjectStub::get_constrains() {
    return constrains;
}

void GrObjectStub::addConstrain(const Constrain c) {
    qDebug() << "Constrain: type = " << c.type;
    constrains.append(c);
}

QVector<GrShape> GrObjectStub::get_image() {
    return shapes;
}

void GrObjectStub::addShape(const GrShape sh) {
    shapes.append(sh);
}
