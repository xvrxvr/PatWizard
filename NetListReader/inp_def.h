#ifndef INP_DEF_H
#define INP_DEF_H

#include <QString>

class LoadedHandler : public GrObject {
public:
    QString get_image(uint32_t opaque);
    void set_image(const char*, uint32_t opaque);
};

struct LoadedValue {
    union {
        const char* image;
        LoadedList* list;
    };
    uint32_t options;
    LoadedHandler* handler;
    uint32_t handler_opaque; // number send to handler to handle different ways

    enum { // bit field
        O_IsList   = 0x00000001, // union contain list
        O_NewLine  = 0x00000002  // for lists started at new line to draw initial structure of source file
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
/* it was for previous implementation used "<<"
    ReadParser(const char* xpath, ReadEventHandler*);
    ReadParser& operator << (const ReadParser&);
*/
private:
    QVector<QString> content;
};

/*
// previous implementation

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
*/

class NetListReader : public GrReader {
public:
    read() {

        // it is anonymous object
           ReadParser()
            .N("library/padStyleDef",  []() {new InpPadStyle}, int opaque = 0 )
            .N("  padShape",           []() (new InpPadShape} )
            .A("    padShapeType",     &InpPasShape::shape }
            .A("    shapeWidth",       &InpPadShape::width )
            .A("    shapeHeight",      &InpPadShape::height )
            .read_file
            ...
}
};

#endif // INP_DEF_H

