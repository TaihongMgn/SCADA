#include "deviceconfigpage.h"
#include "ui_deviceconfigpage.h"

DeviceConfigPage::DeviceConfigPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeviceConfigPage)
{
    ui->setupUi(this);
}

DeviceConfigPage::~DeviceConfigPage()
{
    delete ui;
}
