#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject> //clasa predefinita fundamentala in QT

class QTcpSocket;//clasa pentru realizarea comunicarii prin TCP/IP

class tcpclient : public QObject
{
    Q_OBJECT
public:
    static tcpclient& getInstance();
    static void destroyInstance();

    void start(QString ip, unsigned short port);//primestre adresa IP si portul serverului si initiaza conexiunea
    void stop();//inchide conexiunea cu serverul

    QString getData(QString requestMessage);//primeste mesajul de cerere si returneaza raspunsul de la server

    //aici setez username-ul curent
    static void setUsername(QString str) { tcpclient::clientUsername = str; }
    static QString getUsername() { return tcpclient::clientUsername; }

signals:
    void realtimemessage(QString message);

private slots:
    QString readyRead();//activat cand exista date disponibile pentru citire de la server


private:
    static tcpclient* instance;
    QTcpSocket* socket; //pentru gestiunea conexiunii cu serverul prin protocolul TCP/IP
    static QString clientUsername;
    static QString readString;
    static bool readFlag;

    explicit tcpclient(QObject *parent = nullptr);//nu permite ca un tip diferit sa fie convertit automat in tipul constructorului respectiv
};

#endif // TCPCLIENT_H
