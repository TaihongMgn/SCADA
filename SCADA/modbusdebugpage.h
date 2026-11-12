#ifndef MODBUSDEBUGPAGE_H
#define MODBUSDEBUGPAGE_H

#include <QWidget>

namespace Ui {
class ModbusDebugPage;
}

class ModbusDebugPage : public QWidget
{
    Q_OBJECT

public:
    explicit ModbusDebugPage(QWidget *parent = nullptr);
    ~ModbusDebugPage();

private:
    Ui::ModbusDebugPage *ui;
};

#endif // MODBUSDEBUGPAGE_H
