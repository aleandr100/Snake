#include "client.h"

Client::Client(QWidget *parent) : QDialog(parent) {
    scene = new Scene;

    scene->setFixedSize(805,375);

    connectButton = new QPushButton(tr("Connect"));

    newGameButton = new QPushButton(tr("New game"));
    newGameButton->setEnabled(false);

    startButton = new QPushButton(tr("Start"));
    startButton->setEnabled(false);

    quitButton = new QPushButton(tr("Quit"));

    connectButton->setFixedHeight(35);

    newGameButton->setFixedHeight(35);
    startButton->setFixedHeight(35);

    quitButton->setFixedHeight(35);

    mainLayout = new QHBoxLayout;

    leftLayout = new QVBoxLayout;

    msg = new QLabel;
    msg->setText(tr("Disconnect..."));

    leftLayout->addWidget(scene);

    paramLayout = new QHBoxLayout;

    sizeLabel = new QLabel("Current size is: " + QString::number(0));
    sizeLabel->setFixedWidth(160);
    levelLabel = new QLabel("The level is: None");
    levelLabel->setFixedWidth(160);

    setStyle(sizeLabel,"QLabel.css");
    setStyle(levelLabel,"QLabel.css");

    paramLayout->addWidget(sizeLabel);
    paramLayout->addStretch(1);

    paramLayout->addWidget(levelLabel);
    paramLayout->addStretch(1);

    pixmap = new QPixmap(15,15);

    colorLabel = new QLabel(tr("Color: "));
    setStyle(colorLabel,"QLabel.css");
    imageLabel = new QLabel;
    setColor(QColor (204,204,204));

    paramLayout->addWidget(colorLabel);
    paramLayout->addWidget(imageLabel);

    paramLayout->addStretch(1);

    status = new QStatusBar;
    status->addWidget(msg,1);

    leftLayout->addLayout(paramLayout);

    leftLayout->addWidget(status);

    rightLayout = new QVBoxLayout;

    rightLayout->addWidget(connectButton);
    rightLayout->addWidget(newGameButton);
    rightLayout->addWidget(startButton);

    groupBox = new QGroupBox(tr("Settings:"));
    groupBox->setFixedWidth(135);

    setStyle(groupBox,"QGroupBox.css");

    radioHigh = new QRadioButton(tr("High"));
    radioMedium = new QRadioButton(tr("Medium"));
    radioLow = new QRadioButton(tr("Low"));

    radioLow->setChecked(true);

    editSize = new QLineEdit;
    editFine = new QLineEdit;

    editSize->setText(QString::number(15));
    editFine->setText(QString::number(1));

    editSize->setFixedSize(25, 25);
    editFine->setFixedSize(25, 25);

    labelSize = new QLabel(tr("Max size"));
    labelFine = new QLabel(("Fine"));

    sizeLayout = new QHBoxLayout;
    fineLayout = new QHBoxLayout;

    sizeLayout->addWidget(editSize);
    sizeLayout->addWidget(labelSize);

    fineLayout->addWidget(editFine);
    fineLayout->addWidget(labelFine);

    settingsLayout = new QVBoxLayout;

    settingsLayout->addWidget(radioHigh);
    settingsLayout->addWidget(radioMedium);
    settingsLayout->addWidget(radioLow);

    settingsLayout->addLayout(sizeLayout);
    settingsLayout->addLayout(fineLayout);

    groupBox->setLayout(settingsLayout);

    rightLayout->addWidget(groupBox);

    rightLayout->addStretch(1);

    rightLayout->addWidget(quitButton);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    tcpClient = new QTcpSocket(this);

    this->_blockSize = 0;
    sizes.reserve(2);

    connect(tcpClient, SIGNAL(disconnected()), this, SLOT(lostConnection()));

    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    connect(connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(tcpClient, SIGNAL(connected()), this, SLOT(onConnected()));

    connect(newGameButton, SIGNAL(clicked()), this, SLOT(sendRequest()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(sendRequest()));


    connect(scene, SIGNAL(setValue(int)), this, SLOT(sendData(int)));

    this->setLayout(mainLayout);
}

void Client::connectToServer(void) {

    tcpClient->connectToHost("127.0.0.1", 3425);

    if (!tcpClient->waitForConnected(30000)) {
        qDebug() << "Error: " << tcpClient->errorString();

    } else {
        status->showMessage("Connected to: 127.0.0.1.");
    }
}

void Client::onConnected(void) {

    QByteArray block;
    QDataStream stream(&block, QIODevice::WriteOnly);

    stream << "+REGISTER\r\n";

    connectButton->setEnabled(false);
    newGameButton->setEnabled(true);

    tcpClient->write(block);
}

void Client::sendRequest(void) {

    QByteArray block;
    QDataStream outStream(&block, QIODevice::WriteOnly);

    if (QObject::sender() == startButton) {
        outStream << "+START_GAME\r\n";
        startButton->setEnabled(false);
    } else {
        outStream << "+NEW_GAME\r\n";

        bool ok;
        int size = editSize->text().toInt(&ok,10);
        outStream << size;

        int fine = editFine->text().toInt(&ok,10);
        outStream << fine;

        if (radioLow->isChecked()) {
            outStream << radioLow->text();
        } else if (radioMedium->isChecked()) {
            outStream<< radioMedium->text();
        } else if (radioHigh->isChecked()) {
            outStream << radioHigh->text();
        }
        newGameButton->setEnabled(false);
        startButton->setEnabled(true);
    }

    scene->setFocus();
    tcpClient->write(block);
}

void Client::onReadyRead(void) {

    QDataStream inStream(tcpClient);

    if (this->_blockSize == 0) {
        if (tcpClient->bytesAvailable() < (int)sizeof(quint16)) {
            inStream >> this->_blockSize;

            if (this->_blockSize == 0x0000) {
                this->_blockSize = quint16(0);
                scene->setState(false);
            }
            return;
        }
    }

    if (scene->getState()) {                           /* start game */
        scene->clearList(); sizes.clear();
        recvData(scene->getList());

        scene->updateGL();
        sizeLabel->setText("Current size is: " + QString::number(sizes.at(this->order)));

    } else {
        QString msgData;
        QByteArray block;

        inStream >> block;
        msgData = block.constData();

        if (msgData == "+OK\r\n") {                    /* register client */
            inStream >> block;
            this->uuid = block.constData();

        } else if (msgData == "+TRANSMIT\r\n") {
            inStream >> block;
            levelLabel->setText("The level is: " + QString(block.constData()));

            block.clear();
            inStream >> block;

            if (QString(block.constData()) == "PURPLE") {
                setColor(QColor(239,5,239));
            } else {
                setColor(QColor(26,53,230));
            }

            block.clear();
            inStream >> this->order;

            scene->setState(true);
        } else if (msgData == "+GAME_OVER\r\n") {
            QString _msgResult;
            block.clear(); inStream >> block;
            _msgResult = (getUuid() == block.constData()) ? "You win":"You lose";

            QMessageBox msgBox;

            msgBox.setIcon(QMessageBox::Information);
            msgBox.setWindowTitle("Game over");
            msgBox.setText(_msgResult+". You can start a new game.");
            msgBox.setInformativeText("Current score is: " + QString::number(sizes[0]) + ':' + QString::number(sizes[1]));
            msgBox.setDefaultButton(QMessageBox::Ok);

            newGameButton->setEnabled(true);
            levelLabel->setText(tr("The level is: None"));

            scene->setState(false);

            msgBox.exec();
        } else if (msgData == "+CRASH_GAME\r\n") {
            QMessageBox msgBox;

            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Connection lost");
            msgBox.setText("Rival was disconnected.");
            msgBox.setDefaultButton(QMessageBox::Ok);

            msgBox.exec();
        }
    }
}

void Client::recvData(QList<Point*> &_listPoint) {

    int COUNT;

    QDataStream inStream(tcpClient);

    scene->resetCount(0);

    forever {
        inStream >> this->_blockSize;

        if (this->_blockSize == 0xFFFF) {
            this->_blockSize = quint16(0);
            _listPoint.removeLast();
            break;
        }

        COUNT = this->_blockSize/(sizeof(int));
        if (this->sizes.size() != 2) {
            this->sizes << COUNT;
        }

        for (int index = 0; index < COUNT; index++) {
            Point *point = new  Point();

            inStream >> point->xPos;
            inStream >> point->yPos;

            _listPoint.append(point);
        }

        _listPoint.append(NULL);

        scene->setCount(1);

        this->_blockSize = quint16(0);
    }
}

void Client::sendData(int _direction) {

    QByteArray buffer;
    QDataStream outStream(&buffer, QIODevice::WriteOnly);

    outStream << quint16(_direction);
    outStream << this->uuid.toString().toStdString().c_str();

    tcpClient->write(buffer);
}

void Client::lostConnection(void) {

    QMessageBox msgBox;

    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Connection lost");
    msgBox.setText("The connection to the server was lost");
    msgBox.setStandardButtons(QMessageBox::Ok);

    connectButton->setEnabled(true);
    newGameButton->setEnabled(false);

    if (startButton->isEnabled()) {
        startButton->setEnabled(false);
    }

    scene->setState(false);
    tcpClient->close();

    msgBox.exec();
}

void Client::setStyle(QWidget *_group, QString widget) {
    QFile styleF;

    styleF.setFileName(QDir::homePath() + "/Snake/client/Style/" + widget.toStdString().c_str());
    styleF.open(QFile::ReadOnly);

    QString qssStr = styleF.readAll();

    _group->setStyleSheet(qssStr);
}

void Client::setColor(QColor _color) {
    QBrush brush;
    brush.setColor(_color);
    brush.setStyle(Qt::SolidPattern);

    QPolygon poly;
    poly << QPoint(0,0) << QPoint(0,15) << QPoint(15,15) << QPoint(15,0);

    QPainterPath path;
    path.addPolygon(poly);

    QPainter painter(this->pixmap);

    painter.drawPolygon(poly);
    painter.fillPath(path, brush);

    imageLabel->setPixmap(*pixmap);
}

QString Client::getUuid(void) {
    return this->uuid.toString();
}

Client::~Client() {
    /**/
}
