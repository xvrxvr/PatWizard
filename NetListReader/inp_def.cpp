#include "inp_def.h"
#include "../gr_object.h" // DEF_GR
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStack>
#include <QMap>
#include <cassert>

DEF_GR(NetListReader); // Fabric registration

ReadParser::read_file(const QString &file_path, QMap<QString, LoadedList *> &source_map) {
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    this->in = QTextStream(&file);
    while (!this->in.atEnd()) {
        this->loaded_list = new LoadedList;
        lookUpStartOfList();
        parseList(this->loaded_list);
        source_map.insert(this->loaded_list->tag, this->loaded_list);
    }
}

void ReadParser::lookUpStartOfList() {
    while (this->current_str_list.isEmpty() || !hasOpenedBrace(this->current_str_list.front())) {
        QString line = this->in.readLine();
        this->current_str_list = line.split(" ", QString::SkipEmptyParts);
    }
    return;
}

ReadParser::parseList(LoadedList* loaded_list) {
    assert(hasOpenedBrace(this->current_str_list.front()));

    QString tag = this->current_str_list.takeFirst();
    tag = removeOpenBrace(tag);
    loaded_list->tag = tag;

    while (!this->in.atEnd() && !this->current_str_list.isEmpty()) {
        if (this->current_str_list.isEmpty()) {
            QString line = this->in.readLine();
            this->current_str_list = line.split(" ", QString::SkipEmptyParts);            
            this->is_new_line = true;
        }
        while (!this->current_str_list.isEmpty()) {
            LoadedValue value;
            value.O_NewLine = this->is_new_line;
            QString front = this->current_str_list.takeFirst();
            this->is_new_line = false;

            /* Collect quoted words into one word */
            if (front.count('"') == 1) { // One quotes
                assert(hasOpenedQuotes(front));
                QString phrase;
                // does not work with " something". quotes is a alone word
                // --/-- "something")
                do {
                    phrase.append(front);
                    phrase.append(" ");
                    assert(this->current_str_list.isEmpty());
                    front = this->current_str_list.takeFirst();
                } while (fron.count('"') == 0);
                assert(front.count('"') == 1);
                phrase.remove(phrase.size() - 1, 1); // remove last " "
                front = phrase;
            }
            if (hasOpenedBrace(front)) {
                value.list = new LoadedList;
                value.O_IsList = true;
                list->values.append(value);
                this->current_str_list.prepend(front); // push "(tag"
                parseList(value.list);
            } else if (hasClosedBrace(front)) {
                value.image = QString(removeEndBrace(front));
                list->values.append(value);
                return;
            } else {
                value.image = QString(front);
                list->values.append(value);
            }
        }
    }
    return;
}

QString ReadParser::removeOpenBrace(const QString &word) {
    assert(hasOpenedBrace(word));

    QString new_word = word.remove(0);
    return new_word;
}

QString ReadParser::removeEndBrace(const QString &word) {
    assert(hasClosedBrace(word));

    QString new_word = word.remove(word.size() - 1, 1);
    return new_word;
}

bool ReadParser::hasOpenedQuotes(const QString &str) {
    return;
}

bool ReadParser::hasClosedQuotes(const QString &str) {
    return;
}

bool ReadParser::hasOpenedBrace(const QString &str) {
    assert(!str.isEmpty());
    return (str.data()[0] == "(");
}

bool ReadParser::hasClosedBrace(const QString &str) {
    assert(!str.isEmpty());
    return str.endsWith(")");
}

ReadParser::ReadParser() {
    //TreeDefinition* treeDef = new TreeDefinition;

    return;
}

ReadParser* ReadParser::N(QString tag, std::function<void ()> objConstructor) {
//    QStack<QString> tags = this->parse_tag(tag);
//    while (!tags.isEmpty()) {
//        this->tree;
//    }

    return this;
}

ReadParser::A(QString tag, std::function<void ()> objConstructor) {

}

NetListReader::NetListReader(const QString& file_path) {
    this->file_name = file_path;
}

void NetListReader::read() {
    ReadParser parser;
    parser.read_file(this->file_name, this->source_map);


    // it is anonymous object
//    ReadParser()
//     .N("library/padStyleDef",  []() {new InpPadStyle})
//     .N("    padShape",         []() {new InpPadShape} )
//     .A("      padShapeType",   &InpPasShape::shape )
//     .A("      shapeWidth",     &InpPadShape::width )
//     .A("      shapeHeight",    &InpPadShape::height );
//     ReadParser().read_file(this->file_path);
}
