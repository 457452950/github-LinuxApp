/*

 *  程序名：demo48.cpp，此程序演示多线程的网络服务端。

 *  作者：C语言技术网(www.freecplus.net) 日期：20190525

*/

#include "_freecplus.h"

void *pthmain(void *arg);

CTcpServer TcpServer; // 创建服务端对象。

vector<long> vpthid; // 存放线程id的容器。

void mainexit(int sig); // 信号2和15的处理函数。

// 线程清理函数。

void pthmainexit(void *arg);

CLogFile logfile;

int main(int argc, char *argv[])
{
  signal(2, mainexit);
  signal(15, mainexit); // 捕获信号2和15

  logfile.Open("demo48.log", "a+");

  if (TcpServer.InitServer(5858) == false) // 初始化TcpServer的通信端口。
  {

    logfile.Write("TcpServer.InitServer(5858) failed.\n");
    return -1;
  }

  while (true)
  {

    if (TcpServer.Accept() == false) // 等待客户端连接。
    {
      logfile.Write("TcpServer.Accept() failed.\n");
      return -1;
    }

    logfile.Write("客户端(%s)已连接。\n", TcpServer.GetIP());

    pthread_t pthid;

    if (pthread_create(&pthid, NULL, pthmain, (void *)(long)TcpServer.m_connfd) != 0)
    {
      logfile.Write("pthread_create failed.\n");
      return -1;
    }

    vpthid.push_back(pthid); // 把线程id保存到vpthid容器中。
  }

  return 0;
}

void *pthmain(void *arg)
{

  pthread_cleanup_push(pthmainexit, arg); // 设置线程清理函数。

  pthread_detach(pthread_self()); // 分离线程。

  pthread_setcanceltype(PTHREAD_CANCEL_DISABLE, NULL); // 设置取消方式为立即取消。

  int sockfd = (int)(long)arg; // 与客户端的socket连接。

  int ibuflen = 0;
  char strbuffer[1024]; // 存放数据的缓冲区。

  while (true)
  {
    memset(strbuffer, 0, sizeof(strbuffer));

    if (TcpRead(sockfd, strbuffer, &ibuflen, 300) == false)
      break; // 接收客户端发过来的请求报文。

    logfile.Write("接收：%s\n", strbuffer);

    strcat(strbuffer, "ok"); // 在客户端的报文后加上"ok"。

    logfile.Write("发送：%s\n", strbuffer);

    if (TcpWrite(sockfd, strbuffer) == false)
      break; // 向客户端回应报文。
  }

  logfile.Write("客户端已断开。\n"); // 程序直接退出，析构函数会释放资源。

  pthread_cleanup_pop(1);

  pthread_exit(0);
}

// 信号2和15的处理函数。
void mainexit(int sig)
{
  logfile.Write("mainexit begin.\n");

  // 关闭监听的socket。
  TcpServer.CloseListen();

  // 取消全部的线程。
  for (int ii = 0; ii < vpthid.size(); ii++)
  {
    logfile.Write("cancel %ld\n", vpthid[ii]);

    pthread_cancel(vpthid[ii]);
  }

  logfile.Write("mainexit end.\n");

  exit(0);
}

// 线程清理函数。
void pthmainexit(void *arg)
{

  logfile.Write("pthmainexit begin.\n");

  // 关闭与客户端的socket。
  close((int)(long)arg);

  // 从vpthid中删除本线程的id。
  for (int ii = 0; ii < vpthid.size(); ii++)
  {
    if (vpthid[ii] == pthread_self())
    {
      vpthid.erase(vpthid.begin() + ii);
    }
  }

  logfile.Write("pthmainexit end.\n");
}
