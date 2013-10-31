#include "v2.h"
#include <QtDebug>

quint8 ltable[256] =
{
    0x00, 0xff, 0xc8, 0x08, 0x91, 0x10, 0xd0, 0x36,
    0x5a, 0x3e, 0xd8, 0x43, 0x99, 0x77, 0xfe, 0x18,
    0x23, 0x20, 0x07, 0x70, 0xa1, 0x6c, 0x0c, 0x7f,
    0x62, 0x8b, 0x40, 0x46, 0xc7, 0x4b, 0xe0, 0x0e,
    0xeb, 0x16, 0xe8, 0xad, 0xcf, 0xcd, 0x39, 0x53,
    0x6a, 0x27, 0x35, 0x93, 0xd4, 0x4e, 0x48, 0xc3,
    0x2b, 0x79, 0x54, 0x28, 0x09, 0x78, 0x0f, 0x21,
    0x90, 0x87, 0x14, 0x2a, 0xa9, 0x9c, 0xd6, 0x74,
    0xb4, 0x7c, 0xde, 0xed, 0xb1, 0x86, 0x76, 0xa4,
    0x98, 0xe2, 0x96, 0x8f, 0x02, 0x32, 0x1c, 0xc1,
    0x33, 0xee, 0xef, 0x81, 0xfd, 0x30, 0x5c, 0x13,
    0x9d, 0x29, 0x17, 0xc4, 0x11, 0x44, 0x8c, 0x80,
    0xf3, 0x73, 0x42, 0x1e, 0x1d, 0xb5, 0xf0, 0x12,
    0xd1, 0x5b, 0x41, 0xa2, 0xd7, 0x2c, 0xe9, 0xd5,
    0x59, 0xcb, 0x50, 0xa8, 0xdc, 0xfc, 0xf2, 0x56,
    0x72, 0xa6, 0x65, 0x2f, 0x9f, 0x9b, 0x3d, 0xba,
    0x7d, 0xc2, 0x45, 0x82, 0xa7, 0x57, 0xb6, 0xa3,
    0x7a, 0x75, 0x4f, 0xae, 0x3f, 0x37, 0x6d, 0x47,
    0x61, 0xbe, 0xab, 0xd3, 0x5f, 0xb0, 0x58, 0xaf,
    0xca, 0x5e, 0xfa, 0x85, 0xe4, 0x4d, 0x8a, 0x05,
    0xfb, 0x60, 0xb7, 0x7b, 0xb8, 0x26, 0x4a, 0x67,
    0xc6, 0x1a, 0xf8, 0x69, 0x25, 0xb3, 0xdb, 0xbd,
    0x66, 0xdd, 0xf1, 0xd2, 0xdf, 0x03, 0x8d, 0x34,
    0xd9, 0x92, 0x0d, 0x63, 0x55, 0xaa, 0x49, 0xec,
    0xbc, 0x95, 0x3c, 0x84, 0x0b, 0xf5, 0xe6, 0xe7,
    0xe5, 0xac, 0x7e, 0x6e, 0xb9, 0xf9, 0xda, 0x8e,
    0x9a, 0xc9, 0x24, 0xe1, 0x0a, 0x15, 0x6b, 0x3a,
    0xa0, 0x51, 0xf4, 0xea, 0xb2, 0x97, 0x9e, 0x5d,
    0x22, 0x88, 0x94, 0xce, 0x19, 0x01, 0x71, 0x4c,
    0xa5, 0xe3, 0xc5, 0x31, 0xbb, 0xcc, 0x1f, 0x2d,
    0x3b, 0x52, 0x6f, 0xf6, 0x2e, 0x89, 0xf7, 0xc0,
    0x68, 0x1b, 0x64, 0x04, 0x06, 0xbf, 0x83, 0x38
};

quint8 atable[256] =
{
    0x01, 0xe5, 0x4c, 0xb5, 0xfb, 0x9f, 0xfc, 0x12,
    0x03, 0x34, 0xd4, 0xc4, 0x16, 0xba, 0x1f, 0x36,
    0x05, 0x5c, 0x67, 0x57, 0x3a, 0xd5, 0x21, 0x5a,
    0x0f, 0xe4, 0xa9, 0xf9, 0x4e, 0x64, 0x63, 0xee,
    0x11, 0x37, 0xe0, 0x10, 0xd2, 0xac, 0xa5, 0x29,
    0x33, 0x59, 0x3b, 0x30, 0x6d, 0xef, 0xf4, 0x7b,
    0x55, 0xeb, 0x4d, 0x50, 0xb7, 0x2a, 0x07, 0x8d,
    0xff, 0x26, 0xd7, 0xf0, 0xc2, 0x7e, 0x09, 0x8c,
    0x1a, 0x6a, 0x62, 0x0b, 0x5d, 0x82, 0x1b, 0x8f,
    0x2e, 0xbe, 0xa6, 0x1d, 0xe7, 0x9d, 0x2d, 0x8a,
    0x72, 0xd9, 0xf1, 0x27, 0x32, 0xbc, 0x77, 0x85,
    0x96, 0x70, 0x08, 0x69, 0x56, 0xdf, 0x99, 0x94,
    0xa1, 0x90, 0x18, 0xbb, 0xfa, 0x7a, 0xb0, 0xa7,
    0xf8, 0xab, 0x28, 0xd6, 0x15, 0x8e, 0xcb, 0xf2,
    0x13, 0xe6, 0x78, 0x61, 0x3f, 0x89, 0x46, 0x0d,
    0x35, 0x31, 0x88, 0xa3, 0x41, 0x80, 0xca, 0x17,
    0x5f, 0x53, 0x83, 0xfe, 0xc3, 0x9b, 0x45, 0x39,
    0xe1, 0xf5, 0x9e, 0x19, 0x5e, 0xb6, 0xcf, 0x4b,
    0x38, 0x04, 0xb9, 0x2b, 0xe2, 0xc1, 0x4a, 0xdd,
    0x48, 0x0c, 0xd0, 0x7d, 0x3d, 0x58, 0xde, 0x7c,
    0xd8, 0x14, 0x6b, 0x87, 0x47, 0xe8, 0x79, 0x84,
    0x73, 0x3c, 0xbd, 0x92, 0xc9, 0x23, 0x8b, 0x97,
    0x95, 0x44, 0xdc, 0xad, 0x40, 0x65, 0x86, 0xa2,
    0xa4, 0xcc, 0x7f, 0xec, 0xc0, 0xaf, 0x91, 0xfd,
    0xf7, 0x4f, 0x81, 0x2f, 0x5b, 0xea, 0xa8, 0x1c,
    0x02, 0xd1, 0x98, 0x71, 0xed, 0x25, 0xe3, 0x24,
    0x06, 0x68, 0xb3, 0x93, 0x2c, 0x6f, 0x3e, 0x6c,
    0x0a, 0xb8, 0xce, 0xae, 0x74, 0xb1, 0x42, 0xb4,
    0x1e, 0xd3, 0x49, 0xe9, 0x9c, 0xc8, 0xc6, 0xc7,
    0x22, 0x6e, 0xdb, 0x20, 0xbf, 0x43, 0x51, 0x52,
    0x66, 0xb2, 0x76, 0x60, 0xda, 0xc5, 0xf3, 0xf6,
    0xaa, 0xcd, 0x9a, 0xa0, 0x75, 0x54, 0x0e, 0x01
};

QDataStream &operator <<(QDataStream &out, const Key &key)
{
    quint8 i = 0, j = 0;

    out << key.magic;
    do
    {
        do
        {
            out << key.map[i][j];
            j++;
        } while (j != 0);

        i++;
    } while (i != 0);

    out << key.start << key.x << key.y << key.directions.length();

    for (int i = 0; i < key.directions.length(); i++)
        out << key.directions[i];

    return out;
}

QDataStream &operator >>(QDataStream &in, Key &key)
{
    quint8 i = 0, j = 0;
    int toRead;

    in >> key.magic;
    do
    {
        do
        {
            in >> key.map[i][j];
            j++;
        } while (j != 0);

        i++;
    } while (i != 0);

    in >> key.start >> key.x >> key.y >> toRead;

    key.directions.clear();
    for (int i = 0; i < toRead; i++)
    {
        in >> j;
        key.directions.append(j);
    }

    return in;
}

V2::V2()
{
    qsrand(time(0));

    basePath = QDir::homePath() + "/.V2";

    if (!db.contains("QSQLITE"))
        db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(basePath + "/keys.keystore");

    dir.setPath(basePath);
    if (!dir.exists())
        dir.mkdir(basePath);

    QFile dbFile(basePath + "/keys.keystore");
    if (!dbFile.exists() || dbFile.size() == 0)
    {
        db.open();
        QSqlQuery query(db);
        query.exec("CREATE TABLE Keys (KeyHash VARCHAR(64) Primary key)");
    }

    if (!db.isOpen())
        db.open();
}

int V2::getOptimumBufferSize()
{
    int bufferSize;

#ifdef __linux__
    QFile cpuInfo ("/proc/cpuinfo");
    QTextStream in (&cpuInfo);
    cpuInfo.open (QIODevice::ReadOnly | QIODevice::Text);

    int fact;
    QString line;

    while (true)
    {
        line = in.readLine();
        if(line.contains ("cache size", Qt::CaseInsensitive))
        {
            line = line.mid (line.lastIndexOf(':') + 1).trimmed();

            if(line.contains ("KB", Qt::CaseInsensitive))
                fact = 1024;
            else if(line.contains ("MB", Qt::CaseInsensitive))
                fact = 1024 * 1024;
            else fact = 1024 * 1024 * 1024;

            bufferSize = line.mid(0, line.lastIndexOf(' ')).toInt() * fact;

            cpuInfo.close();
            break;
        }
    }
#elif _WIN32
    DWORD infoSize = 0, i = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION *info = 0;

    GetLogicalProcessorInformation(0, &infoSize);
    info = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *) malloc(infoSize);
    GetLogicalProcessorInformation(&info[0], &infoSize);

    for (i = 0; i != infoSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); i++)
    {
        if (info[i].Relationship == RelationCache && info[i].Cache.Level == 1)
            bufferSize = info[i].Cache.Size;
        if (info[i].Relationship == RelationCache && info[i].Cache.Level == 2)
            bufferSize = info[i].Cache.Size;
        if (info[i].Relationship == RelationCache && info[i].Cache.Level == 3)
            bufferSize = info[i].Cache.Size;
    }

    free(info);
#elif __APPLE__
    proc = new QProcess(this);
    QString program = "sysctl";
    QStringList args;

    args << "-a" << "hw";
    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(readFromStdOut()));

    proc->start(program, args);
#endif

    return bufferSize;
}

#ifdef __APPLE__
void V2::readFromStdOut()
{
    QByteArray output = proc->readAllStandardOutput();
    QString num = "";
    int loc = output.indexOf("hw.l1icachesize: ");
    loc += QString ("hw.l1icachesize: ").length();

    while(output[loc] != '\n')
        num += output[loc++];

    bufferSize = num.toInt();
    getOptimumBufferSize(bufferSize);
}
#endif

QString V2::compressData(QString input, int level)
{
    return qCompress(input.toUtf8(), level).toBase64();
}

QString V2::expandData(QString input)
{
    return QString(qUncompress(QByteArray::fromBase64(input.toUtf8())));
}

bool V2::setMode(QString mode, bool conservative, bool reduce, int level)
{
    this->conservative = conservative;
    this->reduce = reduce;
    this->level = level;
    this->mode = mode;

    if (mode == "decrypt")
    {
        quint8 i = 0, j = 0;

        do
        {
            do
            {
                imap[i][key.map[i][j]] = j;
                j++;
            } while (j != 0);

            i++;
        } while (i != 0);
    }

    return true;
}

void V2::clearKeys()
{
    QSqlQuery q(db);
    q.exec("DELETE FROM Keys");
}

bool V2::keyAlreadyExists()
{
    QSqlQuery q(db);
    QString query = "INSERT INTO Keys VALUES ('" + key.getCode() + "')";

    return !q.exec(query);
}

void V2::makeNewKey(QString path)
{
    quint8 i, j, index;

    key.start = qrand() % 256;
    key.x = qrand() % 256;
    key.y = qrand() % 256;

    do
    {
        i = 0;

        do // Fisher-Yates In-place Shuffle
        {
            for (j = 255; j > 0; j--)
            {
                index = qrand() % (j + 1);
                std::swap(key.map[i][index], key.map[i][j]);
            }

            i++;
        } while (i != 0);
    } while (keyAlreadyExists());

    writeKeyToFile(path);
}

void V2::writeKeyToFile(QString path)
{
    QFile f(path);
    QDataStream stream(&f);
    stream.setVersion(QDataStream::Qt_5_1);

    f.open(QIODevice::WriteOnly);
    stream << key;
    f.close();

    qDebug() << key.directions;
}

bool V2::loadKeyFromFile(QString path)
{
    QFile f(path);
    QDataStream in(&f);
    in.setVersion(QDataStream::Qt_5_1);

    f.open(QIODevice::ReadOnly);
    in >> key;
    f.close();

    keyFile = path;

    return (key.magic == "1911v2");
}

QString V2::conEncrypt(QString input)
{
    QString output = "";
    quint8 value, start = key.start;

    if (reduce)
        input = compressData(input, level);

    for (int i = 0; i < input.length(); i++)
    {
        value = input.at(i).toLatin1();
        output += key.map[start++][value];
    }

    return output;
}

QString V2::conDecrypt(QString input)
{
    QString output = "";
    quint8 value, start = key.start;

    for (int i = 0; i < input.length(); i++)
    {
        value = input.at(i).toLatin1();
        output += imap[start++][value];
    }

    if (reduce)
        output = expandData(output);

    return output;
}

quint8 V2::inverseGalois(quint8 value)
{
    if (value == 0)
        return 0;
    else
        return atable[(255 - ltable[value])];
}

quint8 V2::sBoxOf(quint8 value)
{
    quint8 c, s, x;

    s = x = inverseGalois(value);

    for (c = 0; c < 4; c++)
    {
        s = (s << 1) | (s >> 7);
        x ^= s;
    }

    x ^= 99;
    return x;
}

qint8 V2::getNextDirection(quint8 x, quint8 y)
{
    bool full = false;
    qint8 low, high;
    QList<qint8> directions;

    if (x == 0 && y == 0)
        low = 2, high = 4;
    else if (x == 255 && y == 0)
        low = 4, high = 6;
    else if (x == 255 && y == 255)
        low = 6, high = 0;
    else if (x == 0 && y == 255)
        low = 0, high = 2;
    else if (x == 0)
        low = 0, high = 4;
    else if (x == 255)
        low = 4, high = 0;
    else if (y == 0)
        low = 2, high = 6;
    else if (y == 255)
        low = 6, high = 2;
    else
        low = 0, high = 7, full = true;

    if (full)
    {
        while (low <= 7)
            directions.append(low++);
    }
    else
    {
        do
        {
            directions.append(low);
            low = (low + 1) % 8;
        } while (low <= high);
    }

    return directions[qrand() % directions.length()];
}

void V2::getNextGenMatrix()
{
    quint8 i = 0, j = 0;

    do
    {
        do
        {
            key.map[i][j] = sBoxOf(key.map[i][j]);
            j++;
        } while (j != 0);

        i++;
    } while (i != 0);
}

QString V2::operate(QString input)
{
    QString output = "";
    quint8 value, px = key.x, py = key.y, direction, what;
    int where = 0;

    if (mode == "encrypt")
    {
        what = 0;
        key.directions.clear();
    }
    else
        what = 1;

    switch (what)
    {
    case 0:
        direction = getNextDirection(px, py);
        qDebug() << direction;
        key.directions.append(direction);
        break;

    case 1:
        direction = key.directions[where++];
        break;
    }

    qDebug() << input;

    for (int j = 0; j < input.length(); j++)
    {
        value = input.at(j).toLatin1();
        qDebug() << value;
        output += value ^ key.map[px][py];
        qDebug() << (value ^ key.map[px][py]);

        switch (direction)
        {
        case 0:
            py--;
            break;

        case 1:
            px++;
            py--;
            break;

        case 2:
            px++;
            break;

        case 3:
            px++;
            py++;
            break;

        case 4:
            py++;
            break;

        case 5:
            px--;
            py++;
            break;

        case 6:
            px--;
            break;

        case 7:
            px--;
            py--;
            break;
        }

        if (px <= 0 || px >= 255 || py <= 0 || py >= 255)
        {
            getNextGenMatrix();

            switch (what)
            {
            case 0:
                direction = getNextDirection(px, py);
                qDebug() << direction;
                key.directions.append(direction);
                break;

            case 1:
                direction = key.directions[where++];
                break;
            }
        }
    }

    return output;
}

void V2::updateKey()
{
    if (!conservative)
        writeKeyToFile(keyFile);
}

QString V2::process(QString data)
{
    if (conservative)
    {
        if (mode == "encrypt")
            return conEncrypt(data);
        else
            return conDecrypt(data);
    }

    return operate(data);
}
