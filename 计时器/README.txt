本程序分为三个部分：
1.c++电路模拟
2.python图形化页面的交互与显示
3.c++服务端，用于c++电路和python页面的通信

1.电路设计
此部分不受任何编译器和操作系统限制。
文件已编译成circuit.exe可直接运行。
该程序一条线程会循环运行电路并以ASCII字符画的形式标准输出结果，另一条线程等待标准输入的指令，如开始、暂停、继续、置零

2.图形化页面
此部分已打包成draw.exe可直接运行
运行源代码需要tkinter库。
因为tkinter不允许除主线程以外的线程修改页面元素，所以这里采用了监听线程将输入存入到消息队列，主线程每隔50毫秒循环检测消息队列的方式实现。
而主线程通过tkinter的事件机制将开始、暂停、继续、置零等信息标准输出

3.服务端server.cpp
此部分已打包成MyTimer.exe
程序基于windows API实现。运行源代码需要visual studio环境并安装windowsSDK，并且需要将draw.exe和circuit.exe作为资源文件添加到项目中。
程序本质是创建两个子进程分别运行python程序和c++程序，然后通过匿名管道进行父子进程的通信，连接python和c++的输入输出。
存在两条线程一条读取c++标准输出并写入python的标准输入，另一条读取python标准输出并写入c++的标准输入

其实使用socket通信更直接。但我希望最大程度上减少三个程序的耦合度，以至于电路程序和画图程序只需要标准输入输出就行。