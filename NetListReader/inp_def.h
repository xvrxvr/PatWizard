#ifndef INP_DEF_H
#define INP_DEF_H

#include <QString>
#include <QStack>
#include <QMap>
#include <QTextStream>

class LoadedHandler : public GrObject {
public:
    virtual QString get_image(uint32_t);
    virtual void set_image(const char*, uint32_t);
};

struct LoadedValue {
    union {
        QString image;
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
    void read_file(const QString& file_path, QMap<QString,LoadedList*>& source_map);
    ReadParser* N(QString tag, std::function<void()> objConstructor);
    ReadParser* A(QString tag, std::function<void()> objConstructor);

private:
    LoadedList* loaded_list;       // image of source file
    QTextStream in;               // to fork with source file while reading
    QStringList current_str_list; // keeps the list of string splitted from read line
    bool is_new_line;             // flag to keep source structure of input file

    void parseList(LoadedList* list);
    void parse_line(QString line, LoadedList list);
    QString removeEndBrace(const QString& word);
    QString removeOpenBrace(const QString& word);
    void lookUpStartOfList();
    bool hasOpenedBrace(const QString& str);
    bool hasClosedBrace(const QString& str);
    bool hasOpenedQuotes(const QString& str);
    bool hasClosedQuotes(const QString& str);
//    QStack parse_tag(QString tag);
//    unsigned current_level;
//    TreeDefinition* tree;
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
    void read();
    NetListReader(const QString &file_name);
private:
    QString file_name;
    QMap<QString, LoadedList*> source_map;

};

class TreeDefinition {
public:
    QMap<QString, TreeDefinition*> children;
    TreeDefinition* parrent;
    void *();
};
#endif // INP_DEF_H

