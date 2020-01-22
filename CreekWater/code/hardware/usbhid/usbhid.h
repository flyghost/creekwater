#ifndef USBHID_H
#define USBHID_H


#include <QThread>

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"
#include "CreekWater/code/package/package.h"

class USBHID : public QThread
{
    Q_OBJECT
public:
    USBHID();
    ~USBHID();

protected:
    void run();


public:
    void mystart();
    void test();
    void mystop();
    bool usb_hid_device_find();
    bool usb_hid_device_open();
    void usb_hid_device_close();
    void usb_hid_recvmesg();

    unsigned short vendor_id, product_id;
    //wchar_t * serial_number;

    QString Device;
    QString Manufacturer;
    QString Product;
    QString Release;
    QString Interface;

    Package package;

private:
    volatile bool m_Stopped = true;

    bool if_open = false;
    bool if_find;
    qint32 res;
    unsigned char buf[256];
    #define MAX_STR 255
    wchar_t wstr[MAX_STR];
    hid_device *handle;
    struct hid_device_info *devs, *cur_dev, *m_dev;

};

#endif // USBHID_H
