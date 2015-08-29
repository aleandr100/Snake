#include <QCoreApplication>

#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpServer *server = new TcpServer(2);

    server->startServer();

    return a.exec();
}
