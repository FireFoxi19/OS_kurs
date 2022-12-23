#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>

namespace Ui {
class client;
}

class client : public QMainWindow
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = 0);
    ~client();

private slots:
    void on_pushButton_clicked();
    void slotReadyRead();

    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::client *ui;
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(QString str);
    quint16 nextBlocksSize;
};

#endif // CLIENT_H
