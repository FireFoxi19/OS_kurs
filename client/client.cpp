#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(socket,&QTcpSocket::readyRead,this,&client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlocksSize = 0;
}

client::~client()
{
    delete ui;
}

void client::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1", 2301);
}
void client::SendToServer(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << quint16(0) <<QTime::currentTime()<< str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
    ui->lineEdit->clear();
}

void client::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_10);
    if(in.status() == QDataStream::Ok)
    {
//        QString str;
//        in >> str;
//        ui->textBrowser->append(str);
        for(;;)
        {
            if(nextBlocksSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    break;
                }
                in >> nextBlocksSize;
            }
            if(socket->bytesAvailable() < nextBlocksSize)
            {
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nextBlocksSize = 0;
            ui->textBrowser->append(time.toString() + " " + str);
        }
    }
    else
    {
        ui->textBrowser->append("read error");
    }
}

void client::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text());
}

void client::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text());
}
