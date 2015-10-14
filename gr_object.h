#ifndef GR_OBJECT_H
#define GR_OBJECT_H

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

class GrObject {
public:
    virtual QVector<GrShape> get_image() =0;
    virtual QMap<QString,uint32_t> get_constrain_vars() =0;
    virtual QVector<Constrain*> get_constrains() =0;
};

class GrReader {
public:
    virtual void destroy() =0;
    virtual void read(QMap<QString,QString> config) =0;
    virtual QVector<GrObject*> get_objects() =0;

    virtual void update() =0;
};

#endif // GR_OBJECT_H

