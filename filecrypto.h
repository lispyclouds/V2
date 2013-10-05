#ifndef FILECRYPTO_H
#define FILECRYPTO_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QTime>

#include "v2.h"

class FileCrypto : public QThread
{
    Q_OBJECT

public:
    FileCrypto(QString fileName, QString keyFile, QString mode, bool conservative = true, bool reduce = false, int level = 0);
    void reduceFile(QString path, int level = 0, int mode = 2);
    bool stopIt;

protected:
    void run();

signals:
    void completed(int);
    void msg(QString);
    void okie(QString);

private:
    QFile src, dest;
    QString tag, mode;
    int bufferSize, level;
    char *buffer;
    qint64 length;
    V2 handler;
    QTime timer;
    QString stat, keyFile, basePath;
    bool reduce, conservative;
};

#endif // FILECRYPTO_H
