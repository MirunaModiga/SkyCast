#include "tcpclient.h"
#include "QTcpSocket"
#include "QDebug"
#include "QMessageBox"
#include "QStringList"

tcpclient* tcpclient::instance = nullptr;
QString tcpclient::clientUsername;
QString tcpclient::readString;
bool tcpclient::readFlag = false;

tcpclient::tcpclient(QObject *parent)
    : QObject{parent}
{

}

QString tcpclient::readyRead()
{
    //activat cand exista date disponibile pentru citire de la server
    QByteArray message;
    message = socket->readAll();
    tcpclient::readFlag = true;//setez flagul ca am primit informatii noi
    tcpclient::readString = QString(message);//le actualizez
    QStringList toks=QString(message).split('/');

    return QString(message);
}

QString tcpclient::getData(QString requestMessage)
{
    //primeste mesajul de cerere si returneaza raspunsul de la server
    if(socket->isWritable()) //verifica daca socketul e pregatit pentru scriere
    {
        qDebug() << "request message: " << requestMessage;//contine mesajul pe care il trimit la server

        QByteArray msg = requestMessage.toLocal8Bit(); //converteste mesajul in biti
        socket->write(msg.data(),qint64(requestMessage.size()));

        socket->waitForBytesWritten(1000);//asteapta 1000 milisec ca toate datele sunt puse pe socket
    }
    while(tcpclient::readFlag == false)//verifica daca primeste raspuns de la server sau nu
    {
        socket->waitForReadyRead(5000);//asteapta 5 sec ca datele sa fie disponibile pt citire
    }
    QString msg = tcpclient::readString;
    tcpclient::readFlag = false;//raspunsul a fost primit si procesat

    qDebug() << "answer message: " << msg;
    return msg;
}

void tcpclient::start(QString ip, unsigned short port)
{
    //primestre adresa IP si portul serverului si initiaza conexiunea
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));//permite sa se apelezea automat readyRead cand sunt date disponibile de citit de la server

    socket->connectToHost(ip, port); // pune ip si port din parametri
    if (socket->waitForConnected(3000))
    {
        qDebug() << "Connected...";
    }
    else
    {
        qDebug() << "Connection to server failed...";
        QMessageBox endMessage;
        endMessage.setIcon(QMessageBox::Critical);
        endMessage.setText("Can't connect to server...");
        endMessage.setInformativeText("Application will close. Press button.");
        endMessage.setStandardButtons(QMessageBox::Close);
        endMessage.setDefaultButton(QMessageBox::Close);

        endMessage.exec();
        exit(0);
    }
}

void tcpclient::stop()
{
    if (this->socket->isOpen())
    {
        this->socket->close();
        qDebug() << "Socket closed...";
    }
}

tcpclient& tcpclient::getInstance()
{
    if( tcpclient::instance == nullptr )
    {
       tcpclient::instance = new tcpclient;
    }
    return *tcpclient::instance;
}

void tcpclient::destroyInstance()
{
    if( tcpclient::instance != nullptr )
    {
        delete tcpclient::instance;
    }
   tcpclient::instance = nullptr;
}
