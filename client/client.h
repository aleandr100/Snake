#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui>
#include <QDialog>
#include <QHBoxLayout>
#include <QTcpSocket>
#include <QDataStream>
#include <QUuid>

#include "scene.h"

class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);

    void recvData(QList<Point*> &_listPoint);

    void setColor(QColor _color);

    ~Client();
public slots:
    void connectToServer(void);
    void sendRequest(void);
    void lostConnection(void);

    void onConnected(void);
    void onReadyRead(void);

    void sendData(int _direction);

    QString getUuid(void);

    void setStyle(QWidget *_group, QString widget);

private:
    int pos;

    Scene *scene;

    QPushButton *connectButton;

    QPushButton *startButton;
    QPushButton *newGameButton;

    QPushButton *quitButton;

    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;

    QGroupBox *groupBox;
    QVBoxLayout *settingsLayout;

    QLineEdit *editSize;
    QLineEdit *editFine;

    QLabel *labelSize;
    QLabel *labelFine;

    QHBoxLayout *sizeLayout;
    QHBoxLayout *fineLayout;


    QRadioButton *radioHigh;
    QRadioButton *radioMedium;
    QRadioButton *radioLow;

    QHBoxLayout *paramLayout;

    QLabel *sizeLabel;
    QLabel *levelLabel;
    QLabel *msg;
    QStatusBar *status;

    QTcpSocket *tcpClient;
    quint16 _blockSize;

    QUuid uuid;

    int order;

    QList<int> sizes;

    QLabel *imageLabel;
    QLabel *colorLabel;

    QPixmap *pixmap;
};

#endif // CLIENT_H
