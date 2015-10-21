#ifndef INP_DEF_H
#define INP_DEF_H

class LoadedHandler : public GrObject {
public:
    QString get_image(uint32_t);
    void set_image(const char*, uint32_t);
};

struct LoadedValue {
    union {
        const char* image;
        LoadedList* list;
    };
    uint32_t options;
    LoadedHandler* handler;
    uint32_t handler_opaque;

    enum {
        O_IsList   = 0x00000001,
        O_NewLine  = 0x00000002
    };
};

struct LoadedList {
    const char* tag;
    QVector<LoadedValue> values;
    LoadedHandler* handler;
    LoadedList* template_markup;
};


class ReadParser {
public:
    ReadParser(const char* xpath, ReadEventHandler*);
    ReadParser& operator << (const ReadParser&);
};

/*

  ReadParser("library/padStyleDef",new PadStyleHandler)
   << ReadParser("holeDiam", new GetHoleDiament)
   <<
    (ReadParser("padShape", new GetPadShape)
      << ReadParser("padShapeType", new GetPadShapeType)
      << ReadParser("shapeWidth", new GetShapeWidth)
      << ReadParser("shapeHeight", new GetShapeHeight)
    )
   << ReadParser("viaStyleDef", new ViaStyleHandler)

   class InpPadShape : public ParserHandle {
   public:
        virtual void start();
        virtual void stop();

        int shape;
        int width, height;
   };

   ReadParser()
    .N("library/padStyleDef",  []() {new InpPadStyle} )
    .N("  padShape",           []() (new InpPadShape} )
    .A("    padShapeType",     &InpPasShape::shape }
    .A("    shapeWidth",       &InpPadShape::width )
    .A("    shapeHeight",      &InpPadShape::height )
    ...

*/

class NetListReader : public GrReader {
public:

};

#endif // INP_DEF_H

