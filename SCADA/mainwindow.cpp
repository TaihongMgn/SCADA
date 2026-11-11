#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidget>
#include <QStackedWidget>
#include <QDebug>
#include <QModbusReply>
#include <QModbusDataUnit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // UI导航
    connect(ui->navList,&QListWidget::currentRowChanged,
            ui->pages,&QStackedWidget::setCurrentIndex);

    ui->navList->setCurrentRow(0);

    //modbus
    m_client  = new QModbusTcpClient(this);
    m_timer   = new QTimer(this);
    m_pending = false;

    m_client->setTimeout(1000);
    m_client->setNumberOfRetries(2);
    m_client->setConnectionParameter(QModbusDevice::NetworkAddressParameter,QStringLiteral("127.0.0.1"));
    m_client->setConnectionParameter(QModbusDevice::NetworkPortParameter,1502);
    connect(m_client,&QModbusClient::stateChanged,this,&MainWindow::onStateChanged);

    //轮询
    connect(m_timer,&QTimer::timeout,this,&MainWindow::poll);
    m_timer->start(1000);

    m_client->connectDevice();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStateChanged(QModbusDevice::State st)
{
    if (st == QModbusDevice::ConnectedState) {
        qDebug() << "已连接 BMS 模拟器 127.0.0.1:1502";
    } else if (st == QModbusDevice::UnconnectedState) {
        qDebug() << "未连接:" << m_client->errorString();
    }
}

void MainWindow::poll()
{
    if (m_client->state() != QModbusDevice::ConnectedState)
        return;                          // 没连上就别发
    if (m_pending)
        return;                          // 上一次还没回来，别叠着发

    // 从站 1（1 号电池簇），起始 0x0100，读 20 个保持寄存器
    QModbusDataUnit req(QModbusDataUnit::HoldingRegisters, 0x0100, 20);
    QModbusReply *reply = m_client->sendReadRequest(req, 1);
    if (!reply) {
        qDebug() << "发送读请求失败:" << m_client->errorString();
        return;
    }
    if (reply->isFinished()) {           // 极少数情况：立即失败
        delete reply;
        return;
    }
    m_pending = true;
    connect(reply, &QModbusReply::finished,
            this, &MainWindow::onReadFinished);
}

void MainWindow::onReadFinished()
{
    QModbusReply *reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    m_pending = false;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit res = reply->result();

        const quint16 uVol    = res.value(0);    // 0x0100 簇电压 ×0.1V
        const qint16  iCur    = static_cast<qint16>(res.value(2));  // 0x0102 电流 ×0.1A，正=充电
        const quint16 soc     = res.value(4);    // 0x0104 SOC %
        const quint16 soh     = res.value(5);    // 0x0105 SOH %
        const qint16  tMax    = static_cast<qint16>(res.value(6));  // 0x0106 最高温 ℃
        const quint16 cellMax = res.value(8);    // 0x0108 最高单体 mV
        const quint16 cellMin = res.value(9);    // 0x0109 最低单体 mV
        const quint16 cycle   = res.value(10);   // 0x010A 循环次数
        const quint16 status  = res.value(12);   // 0x010C 状态字

        qDebug().noquote()
            << QStringLiteral("电压 %1 V | 电流 %2 A | SOC %3% | SOH %4% | 温度 %5℃ | 单体 %6/%7 mV | 循环 %8 | 状态 0x%9")
                   .arg(uVol * 0.1f, 0, 'f', 1)
                   .arg(iCur * 0.1f, 0, 'f', 1)
                   .arg(soc).arg(soh).arg(tMax)
                   .arg(cellMax).arg(cellMin).arg(cycle)
                   .arg(status, 4, 16, QLatin1Char('0'));
    } else {
        qDebug() << "读取错误:" << reply->errorString();
    }

    reply->deleteLater();     // 用完必须释放，否则每秒漏一个对象
}