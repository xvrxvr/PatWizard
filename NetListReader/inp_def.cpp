#include "inp_def.h"
#include <QFile>
#include <QTextStream>

ReadParser::ReadParser(const char* xpath, ReadEventHandler*) {
    QFile file("xpath");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        this->content.append(line);
    }
}
