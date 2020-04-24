## MarioTCP ##
### 以上为 Linux 版本( windows版本 在分支 windows_master分支) ###
**MarioTCP** 是使用libevent模型来建立的一个性能强大的TCP服务器.

### 1:Getting Started ###

用MarioTCP来建立一个性能强大的TCP服务器非常简易.工程源码下有一个非常简洁的例子：

- **mario.c**：是简单的main程序:
- 1:直接make编译出maritcp,一个TCP服务器； 
- 2:业务逻辑是：统计在线的socket的数量，每1分钟输出一次； 
- **test**文件夹：简陋的客户端测试程序:
- 1:与服务器建立连接、发送LOGIN包登陆服务器； 
- 2:maritcp服务器会使同时在线加1，客户端断开时服务器在线数减1； 

###2:如何定制一个自己业务逻辑的tcp服务器 ###
####2.1 初始化Server####
- SERVER *server = init_server(conf->port, conf->workernum, conf->connnum, conf->timeout, conf->timeout);
- 参数
- port：      服务器Listen端口；
- workernum： 工作线程数；
- connnum：   每个线程支持的连接数；
- timeout：   读超时时间；
- timeout：   写超时时间。
####2.2 实现业务逻辑函数并注册####
- 具体业务逻辑函数请见Function模块。可通过mario.h中定义的名为“regist_*”的函数来注册。
- 例子：
- **注册业务处理函数**
>`void regist_akg_func(uint16 id, FUNC_PTR func);`
>`typedef enum _CMD {
　　CMD_FUNCTION_BASE = 0x6100,
　　CMD_FUNCTION_LOGIN = 0x6101
　　} CMD`
>>id可以是0-65535的任意数，此id封装在MarioTCP的协议中（见本文最后）。
>>id的范围，可以根据业务逻辑来定制，例如maritcp通过protocol.h中定义的CMD结构体来设定,如上代码.

- **--你想为maritcp增加一个"say_hello"的服务**
- 1)在CMD中增加：`CMD_FUNCTION_SAY_HELLO = 0x602`
- 2)在function中增加函数:    
   `sint32 say_hello(CONN c) {
    I)通过CONN来解析客户端发过来请求的参数
    II）将“hello”设定到c->out_buf
    III)bufferevent_write(c->bufev, c->out_buf, hrsp->pkglen);
    IV)return 0;
    }`
- 3)在mario.c中增加：`regist_akg_func(CMD_FUNCTION_SAY_HELLO, say_hello);`


####2.3 启动日志线程####
- **maritcp增加一个线程start_log_thread()**


####2.4 启动服务器####
- OK，一个可以支持100万甚至更多长连接的TCP服务器，诞生了！



### 为什么高效 ###

>1:网络服务用到的所有结构体和内存都是启动程序时初始化的，无销毁，无回收。无销毁好理解，不解释。无回收，是指所有内存单元拿来即用，用完及可，不用做reset操作。


>2、一个master线程进行accept经过测试发现多进程或线程进行accept和一个进程或线程accept，在极限压力下区别不大。一个master比多个master好在不用再通过锁来解决同步问题。

> 3、master与worker时单一生产者消费者模式，完全无锁通信不光accept无锁，分配connection、后续的conncetion处理都是无锁的。甚至业务逻辑（见示例maritcp的统计在线数功能）、MarioTCP的日志系统（这也是日志系统抽象不够的一个原因，之前的设计太依赖于整体架构了）都是无锁处理的！

>4、一个worker一套libevent环境libevent处理10万长连接的网络读写事件，其性能达到最大化了。每个worker都独立一套libevent，这个结构经过测试，发现开销很小、性能很高。

### 测试环境的搭建 ###

#### 单机百万长连接、四万CPS（连接每秒）如何做测试 ####
1、设置系统最大文件数为unlimited

2、设置系统的tcp内存内核参数到256M以上

3、设置系统的ip到15个，那么可服务的长连接数理论上最少15*(65535-1024)个

4、用epoll或libevent开一个可同时连接5w的客户端程序；程序还要实现每秒随机挑选1000个连接断掉，并再新创建1000个连接。另外在随机挑选几千连接发包。

5、设置服务端可重用SYN_WAIT的连接；客户端断连接的方式是主动断掉（防止客户端程序端口堆积）
