#include <NetListReader/inp_def.h>

void ReadParser::read_file(const QString &file_path, QMap<QString, LoadedList *> &source_map) {
    this->file_path = file_path;
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    this->in = new QTextStream(&file);
    while (!this->in->atEnd()) {
        this->loaded_list = new LoadedList;
        lookUpStartOfList();
        parseList(this->loaded_list);
        source_map.insert(this->loaded_list->tag, this->loaded_list);
    }
}

void ReadParser::lookUpStartOfList() {
    while (this->current_str_list.isEmpty() || !hasOpenedBrace(this->current_str_list.front())) {
        QString line = this->in->readLine();
        this->current_str_list = line.split(" ", QString::SkipEmptyParts);
    }
    return;
}

void ReadParser::parseList(LoadedList* loaded_list) {
    assert(hasOpenedBrace(this->current_str_list.front()));

    QString tag = this->current_str_list.takeFirst();
    tag = removeOpenBrace(tag);
    loaded_list->tag = tag;

    while (!this->in->atEnd() || !this->current_str_list.isEmpty()) {
        if (this->current_str_list.isEmpty()) {
            QString line = this->in->readLine();
            this->current_str_list = line.split(" ", QString::SkipEmptyParts);            
            this->is_new_line = true;
        }
        while (!this->current_str_list.isEmpty()) {
            LoadedValue value;
            value.options = 0;
//            value.O_NewLine = this->is_new_line;
            if (this->is_new_line) {
                value.options |= value.O_NewLine;
                this->is_new_line = false;
            }
            QString front = this->current_str_list.takeFirst();

            /* Collect quoted words into one word */
            if (front.count('"') == 1) { // One quotes
                assert(hasOpenedQuotes(front));
                QString phrase;
                // does not work with " something". quotes is a alone word
                // --/-- "something")
                do {
                    phrase.append(front);
                    phrase.append(" ");
                    assert(!this->current_str_list.isEmpty());
                    front = this->current_str_list.takeFirst();
                } while (front.count('"') == 0);
                assert(front.count('"') == 1);
                phrase.append(front);
                front = phrase;
            }
            if (hasOpenedBrace(front)) {
                value.list = new LoadedList;
                value.options |= value.O_IsList;
                loaded_list->values.append(value);
                this->current_str_list.prepend(front); // push "(tag"
                parseList(value.list);
            } else if (hasClosedBrace(front)) {
                front = removeEndBrace(front);
                while (!front.isEmpty() && hasClosedBrace(front)) {
                    front = removeEndBrace(front);
                    this->current_str_list.prepend(")");
                }
                value.image = new QString(front);
                value.options |= value.O_End;
                loaded_list->values.append(value);
                return;
            } else {
                value.image = new QString(front);
                loaded_list->values.append(value);
            }
        }
    }
    return;
}

QString ReadParser::removeOpenBrace(QString &word) {
    assert(hasOpenedBrace(word));

    QString new_word = word.remove(0, 1);
    return new_word;
}

QString ReadParser::removeEndBrace(QString &word) {
    assert(hasClosedBrace(word));

    QString new_word = word.remove(word.size() - 1, 1);
    return new_word;
}

bool ReadParser::hasOpenedQuotes(const QString &str) {
    return (str[0] == '"');
}

//bool ReadParser::hasClosedQuotes(const QString &str) {
//    return;
//}

bool ReadParser::hasOpenedBrace(const QString &str) {
    assert(!str.isEmpty());
    return (str[0] == '(');
}

bool ReadParser::hasClosedBrace(const QString &str) {
    assert(!str.isEmpty());
    return str.endsWith(')');
}

//ReadParser::ReadParser() {
//    //TreeDefinition* treeDef = new TreeDefinition;

//    return;
//}

//ReadParser* ReadParser::N(QString tag, std::function<void ()> objConstructor) {
//    QStack<QString> tags = this->parse_tag(tag);
//    while (!tags.isEmpty()) {
//        this->tree;
//    }

//    return this;
//}

//ReadParser::A(QString tag, std::function<void ()> objConstructor) {

//}

//NetListReader::NetListReader() {
//    this->file_name = file_path;
//}

void NetListReader::read(QMap<QString, QString> config) {
    ReadParser parser;
    this->file_name = config["file"];
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
void NetListReader::destroy() {
    return;
}

void NetListReader::update() {
    QString file_name = this->file_name + "_updated";
    printToFile(file_name);
    return;
}

QVector<GrObject*> NetListReader::get_objects() {
    return QVector<GrObject*>();
}

void NetListReader::printToFile(const QString &file_path) const {
    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (QMap<QString, LoadedList*>::const_iterator it = this->source_map.begin();
         it != this->source_map.end();
         ++it) {
        out << it.value()->dump("") << endl
            << endl;
    }
}

QString LoadedValue::dump(QString indent = "") const {
    QString out_str;
    QTextStream out(&out_str);
    if (this->options & this->O_NewLine)
        out << endl << indent;
    else
        out << " ";

    if (this->options & this->O_IsList)
        out << this->list->dump(indent);
    else
        out << *this->image;

    if (this->options & this->O_End)
        out << ")";

    // TODO set the following flags while reading
//    if (this->options & this->O_EndWithSpace)
//        out << " )";

    // TODO indent--
//    if (this->options & this->O_EndWithNewLine)
//        out << endl << indent << ")";

    return out_str;
}

QString LoadedList::dump(QString indent = "") const {
    QString out_str;
    QTextStream out(&out_str);
    out << "(" << this->tag;
    for (QVector<LoadedValue>::ConstIterator it = this->values.begin();
         it != this->values.end();
         ++it) {
        out << it->dump(indent + "  ");
    }

    return out_str;
}

GrReaderFabric* GrReaderFabric::root;

DEF_GR(NetListReader); // Fabric registration
