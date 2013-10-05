#include "filecrypto.h"

FileCrypto::FileCrypto(QString fileName, QString keyFile, QString mode, bool conservative, bool reduce, int level)
{
    this->mode = mode;
    this->reduce = reduce;
    this->level = level;
    this->keyFile = keyFile;
    stopIt = false;
    src.setFileName(fileName);
    length = src.bytesAvailable();
    basePath = QDir::homePath() + "/.V2";

    handler.loadKeyFromFile(keyFile);
    if (mode == "encrypt")
    {
        stat = "Encrypting";
        tag = "-encrypted";
        handler.setMode("encrypt", conservative);
    }
    else
    {
        stat = "Decrypting";
        tag = "-decrypted";
        handler.setMode("decrypt", conservative);
    }

    dest.setFileName(QFileInfo(src).absolutePath() + "/" + QFileInfo(src).baseName() + tag + "." + QFileInfo(src).completeSuffix());
}

void FileCrypto::reduceFile(QString path, int level, int mode)
{
    QFile inFile(path), outFile(basePath + "/OutFile");

    inFile.open(QIODevice::ReadOnly);
    outFile.open(QIODevice::WriteOnly);

    QByteArray input = inFile.readAll();

    switch (mode)
    {
    case 1:
        emit msg("Reducing file...");
        outFile.write(qCompress(input, level));
        break;

    case 2:
        emit msg("Expanding file...");
        outFile.write(qUncompress(input));
        break;
    }

    inFile.close();
    outFile.close();
}

void FileCrypto::run()
{
    qint64 done = 0;
    int read;
    float time;
    QString oStr, sp, oFile;
    QByteArray bArr;

    bufferSize = handler.getOptimumBufferSize();
    buffer = new char[bufferSize];

    timer.start();

    if (reduce)
    {
        if (mode == "encrypt")
        {
            reduceFile (QFileInfo(src).absoluteFilePath(), level, 1);

            oFile = QFileInfo(src).absoluteFilePath();
            src.setFileName(basePath + "/OutFile");
            length = src.bytesAvailable();
        }
        else
        {
            oFile = QFileInfo(dest).absoluteFilePath();
            dest.setFileName(basePath + "/OutFile1");
        }
    }

    QDataStream in(&src);
    in.setVersion(QDataStream::Qt_5_1);
    src.open(QIODevice::ReadOnly);

    QDataStream out(&dest);
    out.setVersion(QDataStream::Qt_5_1);
    dest.open(QIODevice::WriteOnly);

    while ((read = in.readRawData(buffer, bufferSize)) > 0 && !stopIt)
    {
        oStr = QString::fromLatin1(buffer, read);
        oStr = handler.process(oStr);
        bArr = oStr.toLatin1();
        buffer = bArr.data();
        out.writeRawData(buffer, read);
        done += read;
        time = timer.elapsed() / 1000.0;
        sp = QString::number((read / (1024.0 * 1024.0)) / time) + " MB/s";

        emit msg("Current Encryption/Decryption status: " + stat + " file at " + sp);
        emit completed(100 * done / length);
    }

    src.close();
    dest.close();

    if (stopIt)
    {
        dest.remove();
        QFile(keyFile).remove();
        QFile(basePath + "/Outfile").remove();
        QFile(basePath + "/Outfile1").remove();

        emit completed(0);
        emit okie("");

        this->terminate();
    }

    if (reduce)
    {
        if(mode == "encrypt")
        {
            src.remove();
            src.setFileName(oFile);
        }
        else
        {
            reduceFile(basePath + "/OutFile1");
            QFile(basePath + "/OutFile1").remove();
            dest.setFileName(basePath + "/OutFile");
            dest.copy(oFile);
            dest.remove();
            dest.setFileName(QFileInfo(src).absolutePath() + "/" + QFileInfo(src).baseName() + tag + "." + QFileInfo(src).completeSuffix());
        }
    }

    emit okie(QFileInfo(dest).absoluteFilePath());
}
