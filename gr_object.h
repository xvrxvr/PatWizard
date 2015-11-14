#ifndef GR_OBJECT_H
#define GR_OBJECT_H
#include <stdint.h>
#include <vector>
#include <QVector>
#include <QMap>
using namespace std;

struct GrShape {
    enum Type {
        MoveTo,
        LineTo,
        ArcTo,
        ArcCenter,
        ArcCenter2, // For ellipse
        ClosePath,
        Text
    } type;
    uint32_t x,y;
    uint32_t options;
    const char* text;
    uint8_t color;
    uint8_t shape;

    enum Options {
        FixedPoint     = 0x00000001,
        ArcCW          = 0x00000002,
        FillPath       = 0x00000004,
        ArcIsEllips    = 0x00000008,
        Hidden         = 0x00000010,
        FullCircle     = 0x00000020
    };
};

struct Constrain{
    GrShape obj1;
    GrShape obj2;
    enum Type {
        PointCoord = 1,
        PointToPoint,
        LineToPoint,
        ArcToPoint,
        LineToLine,
        LineAngle,
        ArcToArc,
        ArcAngle,
        ArcSweep,
        ArcRadius
    }type;
    struct Options{
        double param1;
        double param2;
    }options;
};

class GrObject {
public:
    QVector<GrShape> get_image(){
        QVector<GrShape> vector = *new QVector<GrShape>;
        return vector;

    }

    QMap<QString,uint32_t> get_constrain_vars(){
        QMap<QString,uint32_t> vector = *new QMap<QString,uint32_t>;
        return vector;

    }
    QVector<Constrain> get_constrains(){
        QVector<Constrain> vector = *new QVector<Constrain>;
        return vector;

    }
};

class GrReader {
public:
    virtual void destroy() =0;
    virtual void read(QMap<QString,QString> config) =0;
    virtual QVector<GrObject*> get_objects() =0;

    virtual void update() =0;
};

class GrReaderFabric {
    static GrReaderFabric* root;
    GrReaderFabric* next;
    QString name;
public:
    GrReaderFabric(QString n) : name(n)
    {
        next=root;
        root=this;
    }
    virtual GrReader* create() =0;
    static QMap<QString,GrReaderFabric*> list_all()
    {
        QMap<QString,GrReaderFabric*> rv;
        for(GrReaderFabric* self=root; self; self=self->next)
            rv[self->name]=self;
        return rv;
    }
};

template<class GR>
class GrRdrFabricImp : public GrReaderFabric {
public:
    GrRdrFabricImp(QString nm) : GrReaderFabric(nm) {}

    virtual GrReader* create() {return new GR;}
};

#define DEF_GR(ClassName)  static GrRdrFabricImp<ClassName> gr_reader_fabric_instance_##ClassName(#ClassName)


#endif // GR_OBJECT_H

