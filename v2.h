#ifndef V2_H
#define V2_H

#include <QFile>
#include <QString>
#include <QList>
#include <QFileInfoList>
#include <QDir>
#include <QByteArray>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <time.h>

#include "key.h"

#ifdef _WIN32
#include <Windows.h>
#elif __APPLE__
#include <QProcess>
#elif __linux__
#include <QTextStream>
#endif

class V2
{

public:
    V2();
    void makeNewKey(QString path);
    void clearKeys();
    QString process(QString data);
    bool setMode(QString mode, bool conservative = true, bool reduce = false, int level = 0);
    int getOptimumBufferSize();
    bool loadKeyFromFile(QString path);
    void updateKey();

private:
    QSqlDatabase db;
    QDir dir;
    QString basePath, mode, keyFile;
    quint8 imap[256][256];
    bool conservative, reduce;
    int level;
    Key key;

    inline void writeKeyToFile(QString path);
    inline QString compressData(QString input, int);
    inline QString expandData(QString input);
    inline bool keyAlreadyExists();
    inline quint8 inverseGalois(quint8 value);
    inline quint8 sBoxOf(quint8 value);
    inline void getNextGenMatrix();
    inline qint8 getNextDirection(quint8 x, quint8 y);
    inline QString conEncrypt(QString input);
    inline QString conDecrypt(QString input);
    inline QString operate(QString input);

#ifdef __APPLE__
public slots:
    void readFromStdOut();

private:
    QProcess *proc;
#endif
};

#endif // V2_H
