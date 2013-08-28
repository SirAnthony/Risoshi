#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QList>

QString ucfirstsep( const QString str, const QString sep = " " )
{
    if (str.size() < 1)
        return "";

    QStringList tokens = str.split(sep);
    QList<QString>::iterator tokItr = tokens.begin();

    for (tokItr = tokens.begin(); tokItr != tokens.end(); ++tokItr) {
        (*tokItr) = (*tokItr).at(0).toUpper() + (*tokItr).mid(1);
    }

    return tokens.join(sep);
}


QString ucfirst(const QString str) {
    return ucfirstsep(ucfirstsep(str, ".").trimmed(), " ").trimmed();
}

#endif // UTILS_H
