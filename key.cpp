#include "key.h"

Key::Key()
{
    quint8 i = 0, j = 0;
    magic = "1911v2";

    do // SAAAAXXX Loop ;P
    {
        do
        {
            map[i][j] = j;
            j++;
        } while (j != 0);

        i++;
    } while (i != 0);
}

QString Key::getCode()
{
    quint8 i = 0, j = 0;
    QString s = "";

    do
    {
        do
        {
            s += map[i][j];
            j++;
        } while (j != 0);

        i++;
    } while (i != 0);

    return QString (mySHA.hashIt(s.toUtf8().data(), 256));
}
