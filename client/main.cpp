#include <QApplication>

#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client window;
    window.setWindowTitle("QT Snake - version 1.0");
    window.show();

    return a.exec();
}
