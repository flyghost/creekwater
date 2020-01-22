#include "usbhid.h"

#include "CreekWater/code/hardware/usbhid/usbhid.h"
#include <QDebug>



USBHID::USBHID()
{
    //qDebug() << "usbhid create";
    //run();

    package.start();
    package.mystart();
}


USBHID::~USBHID()
{
    hid_close(handle);

    /* Free static HIDAPI objects. */
    hid_exit();
}


void USBHID::run()
{
    while (1)
    {

        while (!m_Stopped)
        {
            //qDebug() << "is doing";
            usb_hid_recvmesg();

        }
        while (m_Stopped);
            //qDebug() << m_Stopped;
        //m_Stopped = false;
    }

}

void USBHID::mystop()
{
    m_Stopped = true;


}
void USBHID::mystart()
{
    m_Stopped = false;
}

void USBHID::test()
{

//    int res;
//    unsigned char buf[256];
//    //#define MAX_STR 255
//    //wchar_t wstr[MAX_STR];
//    hid_device *handle;
//    int i;

//    struct hid_device_info *devs, *cur_dev;

//    devs = hid_enumerate(0x0, 0x0);
//    cur_dev = devs;
//    while (cur_dev) {
//        printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
//        printf("\n");
//        printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
//        printf("  Product:      %ls\n", cur_dev->product_string);
//        printf("  Release:      %hx\n", cur_dev->release_number);
//        printf("  Interface:    %d\n", cur_dev->interface_number);
//        printf("\n");
//        cur_dev = cur_dev->next;
//    }
//    hid_free_enumeration(devs);

//    // Set up the command buffer.
//    memset(buf, 0x00, sizeof(buf));
//    buf[0] = 0x01;
//    buf[1] = 0x81;


//    // Open the device using the VID, PID,
//    // and optionally the Serial number.
//    ////handle = hid_open(0x4d8, 0x3f, L"12345");
//    handle = hid_open(0x0483, 0xa005, L"0001A0000000");
//    if (!handle) {
//        //printf("unable to open device\n");
//        qDebug() << "unable to open device";
//        //return 1;
//    }



//    // Set the hid_read() function to be non-blocking.
//    hid_set_nonblocking(handle, 1);

//    // Try to read from the device. There shoud be no
//    // data here, but execution should not block.
//    res = hid_read(handle, buf, 17);

//    // Send a Feature Report to the device
//    buf[0] = 0x2;
//    buf[1] = 0xa0;
//    buf[2] = 0x0a;
//    buf[3] = 0x00;
//    buf[4] = 0x00;
//    res = hid_send_feature_report(handle, buf, 17);
//    if (res < 0) {
//        printf("Unable to send a feature report.\n");
//    }

//    memset(buf, 0, sizeof(buf));

//    // Read a Feature Report from the device
//    buf[0] = 0x2;
//    res = hid_get_feature_report(handle, buf, sizeof(buf));
//    if (res < 0) {
//        printf("Unable to get a feature report.\n");
//        printf("%ls", hid_error(handle));
//    }
//    else {
//        // Print out the returned buffer.
//        printf("Feature Report\n   ");
//        for (i = 0; i < res; i++)
//            printf("%02hhx ", buf[i]);
//        printf("\n");
//    }

//    memset(buf, 0, sizeof(buf));

//    // Toggle LED (cmd 0x80). The first byte is the report number (0x1).
//    buf[0] = 0x1;
//    buf[1] = 0x80;
//    res = hid_write(handle, buf, 17);
//    if (res < 0) {
//        printf("Unable to write()\n");
//        printf("Error: %ls\n", hid_error(handle));
//    }


//    // Request state (cmd 0x81). The first byte is the report number (0x1).
//    buf[0] = 0x1;
//    buf[1] = 0x81;
//    hid_write(handle, buf, 17);
//    if (res < 0)
//        printf("Unable to write() (2)\n");

//    // Read requested state. hid_read() has been set to be
//    // non-blocking by the call to hid_set_nonblocking() above.
//    // This loop demonstrates the non-blocking nature of hid_read().

//    while (1)
//    {
//        res = 0;
//        while (res == 0) {
//            res = hid_read(handle, buf, sizeof(buf));
//            if (res == 0)
//                printf("waiting...\n");
//            if (res < 0)
//                printf("Unable to read()\n");
////            #ifdef WIN32
////            Sleep(500);
////            #else
////            usleep(500*1000);
////            #endif
//        }

//        printf("Data read:\n   ");
//        // Print out the returned buffer.
//        for (i = 0; i < res; i++)
//            printf("%02hhx ", buf[i]);
//        printf("\n");
//    }
}


bool USBHID::usb_hid_device_find()
{

    usb_hid_device_close();//关闭已经打开的设备

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;

    if_find = false;

    device_0x05 = false;
    device_0x10 = false;
    device_0x04 = false;


    while (cur_dev)
    {
        //printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
        //printf("\n");
        //printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
        //printf("  Product:      %ls\n", cur_dev->product_string);
        //printf("  Release:      %hx\n", cur_dev->release_number);
        //printf("  Interface:    %d\n", cur_dev->interface_number);
        //printf("\n");

        vendor_id = cur_dev->vendor_id;
        product_id = cur_dev->product_id;

        if (product_id == 0xa005)//匿名拓空者飞控
        {
            device_0x05 = true;
            qDebug() << "find tuokongzhe";
        }
        else if (product_id == 0xa010)//匿名数传模块
        {
            device_0x10 = true;
            qDebug() << "shuchuan";
        }
        else if (product_id == 0xa004)//匿名领航者
        {
            device_0x04 = true;
            qDebug() << "linghangzhe";
        }


        device_find = true;
        if_find = true;
        m_dev = cur_dev;

        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    if (if_find)
    {
        return true;
    }
    return false;
}

bool USBHID::usb_hid_device_open()
{
    // Open the device using the VID, PID,
    // and optionally the Serial number.
    ////handle = hid_open(0x0483, 0xa005, L"0001A0000000");//ANO Information
    //handle = hid_open(0x4d8, 0x3f, NULL);

    if (if_open)
    {
        return true;
    }

    if (if_find)
    {
        if (device_name == 0xa005)//匿名拓空者飞控
        {
            //handle = hid_open(0x0483, 0xa005, L"0001A0000000");
            handle = hid_open(0x0483, 0xa005, Q_NULLPTR);
            qDebug() << "open tuokongzhe";
            //handle = hid_open(vendor_id, product_id, L"0001A0000000");//ANO Information
        }
        else if (device_name == 0xa010)//匿名数传模块
        {
            handle = hid_open(0x0483, 0xa010, Q_NULLPTR);
            printf("open shuchuan\n");
            //handle = hid_open(vendor_id, product_id, NULL);//ANO Information
        }
        else if (device_name == 0xa004)//匿名领航者
        {
            //handle = hid_open(0x0483, 0xa004, '\0');
            handle = hid_open(0x0483, 0xa004, Q_NULLPTR);
            printf("open lihghangzhe\n");
            //handle = hid_open(vendor_id, product_id, NULL);//ANO Information
        }

        //handle = hid_open(0x0483, 0xa005, L"0001A0000000");//ANO Information
        //handle = hid_open(m_dev->vendor_id, m_dev->product_id, (wchar_t *)serial);
        if (!handle) {
            printf("unable to open device\n");
            if_open = false;
            return false;
        }
        else
        {
            if_open = true;
        }
        hid_set_nonblocking(handle, 1);
        return true;
    }

    return false;
}

void USBHID::usb_hid_device_close()
{
    if (if_open)
    {
        hid_close(handle);

        /* Free static HIDAPI objects. */
        hid_exit();

        if_open = false;
    }

}



void USBHID::usb_hid_recvmesg()
{
    if (if_open)
    {

        if (package.m_Get_Mesg == false)
        {
            if ((res = hid_read(handle, buf, sizeof(buf))) != 0)
            {
                //printf("Data read:\n   ");
                // Print out the returned buffer.
                for (int i = 0; i < res; i++)
                {
                    //if (buf[i] == 0xAA)
                        //printf("%02hhX ", buf[i]);
                    //package.Phantom_Data_Receive_Prepare(buf[i]);

                    package.buf[i] = buf[i];

                    //package.Phantom_Data_Receive_Anl_Task();
                }
                package.buf_len = res;
                package.m_Get_Mesg = true;
                //emit usbhid_get_mesg_signal();

                //printf("\n");
                res = 0;
            }
        }


    }
}
