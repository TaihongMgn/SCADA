#include "modbusdebugpage.h"
#include "ui_modbusdebugpage.h"

ModbusDebugPage::ModbusDebugPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModbusDebugPage)
{
    ui->setupUi(this);
}

ModbusDebugPage::~ModbusDebugPage()
{
    delete ui;
}
