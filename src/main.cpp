#include <QtGui/QApplication>
#include "GroundZero.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   GroundZero z;
   z.show();

    return a.exec();
}
