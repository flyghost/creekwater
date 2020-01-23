
USBHID关闭，开启需要重新编译ubuntu或者windows下的库



Ubuntu下需要给串口权限解决方法：
比如，串口 tty 设备所在组为 dialout 组，那么考虑添加当前用户到 dialout 组即可。指令如下：

sudo gpasswd -a $USER dialout

另外，需要重新登录才能生效。





解决qt不能输入中文的问题：
sudo cp /usr/lib/x86_64-linux-gnu/qt5/plugins/platforminputcontexts/libfcitxplatforminputcontextplugin.so /opt/Qt5.12.0/Tools/QtCreator/lib/Qt/plugins/platforminputcontexts/

