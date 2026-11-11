#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusTcpClient>     // 新增：Modbus TCP 客户端
#include <QTimer>               // 新增：定时轮询用

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onStateChanged(QModbusDevice::State st);   // 连接状态变了
    void poll();                                    // 每秒问一次
    void onReadFinished();                          // 回信到了

private:
    Ui::MainWindow *ui;
    QModbusTcpClient *m_client;    // 客户端对象
    QTimer *m_timer;               // 轮询定时器
    bool m_pending;                // 上一次请求还在路上吗？
};

#endif // MAINWINDOW_H