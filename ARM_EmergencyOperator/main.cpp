#include "arm_emergency_operator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ARM_emergency_operator w;
    w.show();
    return a.exec();
}
