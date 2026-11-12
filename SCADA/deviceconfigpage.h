#ifndef DEVICECONFIGPAGE_H
#define DEVICECONFIGPAGE_H

#include <QWidget>

namespace Ui {
class DeviceConfigPage;
}

class DeviceConfigPage : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceConfigPage(QWidget *parent = nullptr);
    ~DeviceConfigPage();

private:
    Ui::DeviceConfigPage *ui;
};

#endif // DEVICECONFIGPAGE_H
