===更新日期：2015-02-06===== 
===更新内容：
增加win64工程配置，
win64  执行目录: x64\release
win64头文件目录: P2PClientTest\headfiles_x64
win64 lib库目录: P2PClientTest\depends_x64

P2P win64库：
Defs.h 
ProxyClientCWrap.h
TouProxymd.lib
TouProxymd.dll

P2P win64依赖库：
Inframd64.dll
NATTravermd.dll
TinyXmlmd.dll
============================

===更新日期：2014-12-15===== 
===更新内容：
P2P改为dll动态库,Demo可使用VS2010编译
P2P库：
Defs.h 
ProxyClientCWrap.h
TouProxy.lib
TouProxy.dll
============================

说明：P2P功能需要P2P服务(IP\PORT\密钥)、已连接P2P服务器（在线）的设备才能穿透访问
例如：
1.P2P库：
Defs.h ProxyClientCWrap.h
Infra.lib litepi.lib NATTraver.lib P2PSDK.lib TouProxy.lib

2.网络SDK库：
dhassistant.h dhnetsdk.h
dhnetsdk.lib

3.P2P环境（IP\PORT\密钥）：
172.23.1.120 8800 YXQ3Mahe-5H-R1Z_

4.P2P环境上已有两设备在线：
77
PZC4FA492W00413

本demo使用VC2005编写的，建议使用VC2005打开。