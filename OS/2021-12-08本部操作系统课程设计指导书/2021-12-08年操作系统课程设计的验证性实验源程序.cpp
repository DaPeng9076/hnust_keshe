/*  实验一源程序 */
//清单1-1  一个简单的Windows控制台应用程序
// hello项目
# include <iostream>
void main()
{
	std::cout << "Hello, Win32 Consol Application" << std::endl;
	getchar();
}


//清单1-2  创建子进程
#include <windows.h>
#include <iostream>
#include <stdio.h>

// 创建传递过来的进程的克隆过程并赋于其ID值
void StartClone(int nCloneID)
{
    // 提取用于当前可执行文件的文件名
    TCHAR szFilename[MAX_PATH] ;
    GetModuleFileName(NULL, szFilename, MAX_PATH) ;
	
    // 格式化用于子进程的命令行并通知其EXE文件名和克隆ID
    TCHAR szCmdLine[MAX_PATH];
	sprintf(szCmdLine,"\"%s\" %d",szFilename,nCloneID);

	// 用于子进程的STARTUPINFO结构
    STARTUPINFO si;
    ZeroMemory(&si , sizeof(si) ) ;
    si.cb = sizeof(si) ;				// 必须是本结构的大小

    // 返回的用于子进程的进程信息
    PROCESS_INFORMATION pi;

    // 利用同样的可执行文件和命令行创建进程，并赋于其子进程的性质
    BOOL bCreateOK=::CreateProcess(
        szFilename,					// 产生这个EXE的应用程序的名称
        szCmdLine,					// 告诉其行为像一个子进程的标志
        NULL,						// 缺省的进程安全性
        NULL,						// 缺省的线程安全性
        FALSE,						// 不继承句柄
        CREATE_NEW_CONSOLE,			// 使用新的控制台
        NULL,						// 新的环境
        NULL,						// 当前目录
        &si,						// 启动信息
        &pi) ;						// 返回的进程信息

    // 对子进程释放引用
    if (bCreateOK)
    {
        CloseHandle(pi.hProcess) ;
        CloseHandle(pi.hThread) ;
    }
}

int main(int argc, char* argv[] )
{
    // 确定派生出几个进程，及派生进程在进程列表中的位置
    int nClone=0;
//修改语句：int nClone;

//第一次修改：nClone=0;
    if (argc > 1)
    {
        // 从第二个参数中提取克隆ID
        :: sscanf(argv[1] , "%d" , &nClone) ; //用sscanf_s代替
    }

//第二次修改：nClone=0;
	// 显示进程位置
    std :: cout << "Process ID:" << :: GetCurrentProcessId()
                << ", Clone ID:" << nClone
                << std :: endl;
	// 检查是否有创建子进程的需要
    const int c_nCloneMax=5;
    if (nClone < c_nCloneMax)
    {
		// 发送新进程的命令行和克隆号
       StartClone(++nClone) ;
    }
    // 等待响应键盘输入结束进程
   	getchar();
    return 0;
}

//清单1-3  父子进程的简单通信及终止进程的示例程序
// procterm项目
# include <windows.h>
# include <iostream>
# include <stdio.h>
static LPCTSTR g_szMutexName = "w2kdg.ProcTerm.mutex.Suicide" ;

// 创建当前进程的克隆进程的简单方法
void StartClone()
{
    // 提取当前可执行文件的文件名
    TCHAR szFilename[MAX_PATH] ;
    GetModuleFileName(NULL, szFilename, MAX_PATH) ;

    // 格式化用于子进程的命令行，字符串“child”将作为形参传递给子进程的main函数
    TCHAR szCmdLine[MAX_PATH] ;
//实验1-3步骤3：将下句中的字符串child改为别的字符串，重新编译执行，执行前请先保存已经完成的工作
    sprintf(szCmdLine, "\"%s\"child" , szFilename) ;

    // 子进程的启动信息结构
    STARTUPINFO si;
    ZeroMemory(&si,sizeof(si)) ;
    si.cb = sizeof(si) ;		// 应当是此结构的大小

    // 返回的用于子进程的进程信息
    PROCESS_INFORMATION pi;

    // 用同样的可执行文件名和命令行创建进程，并指明它是一个子进程
    BOOL bCreateOK=CreateProcess(
        szFilename,				// 产生的应用程序的名称 (本EXE文件)
        szCmdLine,				// 告诉我们这是一个子进程的标志
        NULL,					// 用于进程的缺省的安全性
        NULL,					// 用于线程的缺省安全性
        FALSE,					// 不继承句柄
        CREATE_NEW_CONSOLE,		//创建新窗口
        NULL,					// 新环境
        NULL,					// 当前目录
        &si,					// 启动信息结构
        &pi ) ;					// 返回的进程信息
    // 释放指向子进程的引用
    if (bCreateOK)
    {
        CloseHandle(pi.hProcess) ;
        CloseHandle(pi.hThread) ;
    }
}

void Parent()
{
    // 创建“自杀”互斥程序体
    HANDLE hMutexSuicide=CreateMutex(
        NULL,					// 缺省的安全性
        TRUE,					// 最初拥有的
        g_szMutexName) ;		// 互斥体名称
    if (hMutexSuicide != NULL)
    {
        // 创建子进程
        std :: cout << "Creating the child process." << std :: endl;
        StartClone() ;
        // 指令子进程“杀”掉自身
        std :: cout << "Telling the child process to quit. "<< std :: endl;
		//等待父进程的键盘响应
        getchar() ;
		//释放互斥体的所有权，这个信号会发送给子进程的WaitForSingleObject过程
		ReleaseMutex(hMutexSuicide) ;
        // 消除句柄
        CloseHandle(hMutexSuicide) ;
    }
}

void Child()
{
    // 打开“自杀”互斥体
    HANDLE hMutexSuicide = OpenMutex(
        SYNCHRONIZE,			// 打开用于同步
        FALSE,					// 不需要向下传递
        g_szMutexName) ;		// 名称
    if (hMutexSuicide != NULL)
    {
        // 报告我们正在等待指令
        std :: cout <<"Child waiting for suicide instructions. " << std :: endl;
       
		//子进程进入阻塞状态，等待父进程通过互斥体发来的信号
	    WaitForSingleObject(hMutexSuicide, INFINITE) ;
//实验1-3步骤4：将上句改为WaitForSingleObject(hMutexSuicide, 0) ，重新编译执行

        // 准备好终止，清除句柄
        std :: cout << "Child quiting." << std :: endl;
        CloseHandle(hMutexSuicide) ;
    }
}

int main(int argc, char* argv[] )
{
    // 决定其行为是父进程还是子进程
    if (argc>1 && :: strcmp(argv[1] , "child" )== 0)
    {
        Child() ;
    }
    else
    {
        Parent() ;
    }
return 0;

}


/*  实验二源程序 */
//清单2-1  创建进程
#include <stdio.h>
#include <stdlib.h>
main()
{
  int x;
  srand((unsigned)time(NULL));
  while((x=fork())==-1);
  if (x==0)
  {	
	sleep(rand() % 2);
	printf("a");
  }
  else
  {
	sleep(rand() % 3);
	printf("b");
  }
  printf("c");
}

//清单2-2 子进程执行新任务
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
  pid_t pid;
  /* fork a child process */
  pid = fork();
  if (pid < 0) 
  { /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  else if (pid == 0) 
  { /* 子进程 */
    execlp("/bin/ls","ls",NULL);
  }
  else { /* 父进程 */
  /* 父进程将一直等待，直到子进程运行完毕*/
    wait(NULL);
    printf("Child Complete");
  }
  return 0;
}



/*  实验三源程序 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#define MSGKEY 75
struct msgform
{
	long mtype;
	char mtext[1030];
}msg;
int msgqid,i;
void CLIENT()
{
  int i;
  msgqid=msgget(MSGKEY,0777);
  for (i=10;i>=1;i--)
  { 
	msg.mtype=i;
	printf("(client) sent \n");
	msgsnd(msgqid,&msg,1024,0);
  }
  exit(0);
}
void SERVER()
{
  msgqid=msgget(MSGKEY,0777|IPC_CREAT);
  do{
  	msgrcv(msgqid,&msg,1030,0,0);
	printf("(Server) recieved\n");

  } while(msg.mtype!=1);
  msgctl(msgqid,IPC_RMID,0);
  exit(0);
}
void main()
{
  while((i=fork())==-1);
  if(!i) SERVER();
  while((i=fork())==-1);
  if(!i) CLIENT();
  wait(0);
  wait(0);
}



/*  实验四源程序 */
//清单4-1 生产者消费者问题
#include <windows.h>
#include <iostream>

const unsigned short SIZE_OF_BUFFER = 2; //缓冲区长度
unsigned short ProductID = 0;    //产品号
unsigned short ConsumeID = 0;    //将被消耗的产品号
unsigned short in = 0;      //产品进缓冲区时的缓冲区下标
unsigned short out = 0;      //产品出缓冲区时的缓冲区下标

int buffer[SIZE_OF_BUFFER];    //缓冲区是个循环队列
bool p_ccontinue = true;      //控制程序结束
HANDLE Mutex;       //用于线程间的互斥
HANDLE FullSemaphore;     //当缓冲区满时迫使生产者等待
HANDLE EmptySemaphore;     //当缓冲区空时迫使消费者等待

DWORD WINAPI Producer(LPVOID);    //生产者线程
DWORD WINAPI Consumer(LPVOID);    //消费者线程

int main()
{
    //创建各个互斥信号
	//注意，互斥信号量和同步信号量的定义方法不同，互斥信号量调用的是CreateMutex函数，同步信号量调用的是CreateSemaphore函数，函数的返回值都是句柄。
    Mutex = CreateMutex(NULL,FALSE,NULL);
	EmptySemaphore = CreateSemaphore(NULL,SIZE_OF_BUFFER,SIZE_OF_BUFFER,NULL);
    //将上句做如下修改，看看结果会怎样
	//EmptySemaphore = CreateSemaphore(NULL,0,SIZE_OF_BUFFER-1,NULL);
    FullSemaphore = CreateSemaphore(NULL,0,SIZE_OF_BUFFER,NULL);

    //调整下面的数值，可以发现，当生产者个数多于消费者个数时，
    //生产速度快，生产者经常等待消费者；反之，消费者经常等待 
    const unsigned short PRODUCERS_COUNT = 3;  //生产者的个数
    const unsigned short CONSUMERS_COUNT = 1;  //消费者的个数

    //总的线程数
    const unsigned short THREADS_COUNT = PRODUCERS_COUNT+CONSUMERS_COUNT;

    HANDLE hThreads[THREADS_COUNT]; //各线程的handle
    DWORD producerID[PRODUCERS_COUNT]; //生产者线程的标识符
    DWORD consumerID[CONSUMERS_COUNT]; //消费者线程的标识符

	//创建生产者线程
    for (int i=0;i<PRODUCERS_COUNT;++i){
        hThreads[i]=CreateThread(NULL,0,Producer,NULL,0,&producerID[i]);
        if (hThreads[i]==NULL) return -1;
    }
    //创建消费者线程
    for (i=0;i<CONSUMERS_COUNT;++i){
        hThreads[PRODUCERS_COUNT+i]=CreateThread(NULL,0,Consumer,NULL,0,&consumerID[i]);
        if (hThreads[i]==NULL) return -1;
    }

    while(p_ccontinue){
        if(getchar()){ //按回车后终止程序运行
            p_ccontinue = false;
        }
    }
    return 0;
}

//生产一个产品。简单模拟了一下，仅输出新产品的ID号
void Produce()
{
    std::cout << std::endl<< "Producing " << ++ProductID << " ... ";
    std::cout << "Succeed" << std::endl;
}

//把新生产的产品放入缓冲区
void Append()
{
    std::cerr << "Appending a product ... ";
    buffer[in] = ProductID;
    in = (in+1)%SIZE_OF_BUFFER;
    std::cerr << "Succeed" << std::endl;

    //输出缓冲区当前的状态
    for (int i=0;i<SIZE_OF_BUFFER;++i){
        std::cout << i <<": " << buffer[i];
        if (i==in) std::cout << " <-- 生产";
        if (i==out) std::cout << " <-- 消费";
        std::cout << std::endl;
    }
}

//从缓冲区中取出一个产品
void Take()
{
    std::cerr << "Taking a product ... ";
    ConsumeID = buffer[out];
	buffer[out] = 0;
    out = (out+1)%SIZE_OF_BUFFER;
    std::cerr << "Succeed" << std::endl;

    //输出缓冲区当前的状态
    for (int i=0;i<SIZE_OF_BUFFER;++i){
        std::cout << i <<": " << buffer[i];
        if (i==in) std::cout << " <-- 生产";
        if (i==out) std::cout << " <-- 消费";
        std::cout << std::endl;
    }
}

//消耗一个产品
void Consume()
{
    std::cout << "Consuming " << ConsumeID << " ... ";
    std::cout << "Succeed" << std::endl;
}

//生产者
DWORD  WINAPI Producer(LPVOID lpPara)
{
    while(p_ccontinue){
        WaitForSingleObject(EmptySemaphore,INFINITE);	//p(empty);
        WaitForSingleObject(Mutex,INFINITE);	//p(mutex);
        Produce();
        Append();
        Sleep(1500);
        ReleaseMutex(Mutex);	//V(mutex);
        ReleaseSemaphore(FullSemaphore,1,NULL);	//V(full);
    }
    return 0;
}

//消费者
DWORD  WINAPI Consumer(LPVOID lpPara)
{
    while(p_ccontinue){
        WaitForSingleObject(FullSemaphore,INFINITE);	//P(full);
        WaitForSingleObject(Mutex,INFINITE);		//P(mutex);
        Take();
        Consume();
        Sleep(1500);
        ReleaseMutex(Mutex);		//V(mutex);
        ReleaseSemaphore(EmptySemaphore,1,NULL);		//V(empty);
    }
    return 0;
}



/*  实验五源程序 */
//清单5-1  了解和检测进程的虚拟内存空间
// 工程vmwalker
#include <windows.h>
#include <iostream>
#include <shlwapi.h>
#include <iomanip>
#pragma comment(lib, "Shlwapi.lib")

// 以可读方式对用户显示保护的辅助方法。
// 保护标记表示允许应用程序对内存进行访问的类型
// 以及操作系统强制访问的类型
inline bool TestSet(DWORD dwTarget, DWORD dwMask)
{
    return ((dwTarget &dwMask) == dwMask) ;
}
# define SHOWMASK(dwTarget, type) \
if (TestSet(dwTarget, PAGE_##type) ) \
    {std :: cout << ", " << #type; }

void ShowProtection(DWORD dwTarget)
{
    SHOWMASK(dwTarget, READONLY) ;
    SHOWMASK(dwTarget, GUARD) ;
    SHOWMASK(dwTarget, NOCACHE) ;
    SHOWMASK(dwTarget, READWRITE) ;
    SHOWMASK(dwTarget, WRITECOPY) ;
    SHOWMASK(dwTarget, EXECUTE) ;
    SHOWMASK(dwTarget, EXECUTE_READ) ;
    SHOWMASK(dwTarget, EXECUTE_READWRITE) ;
    SHOWMASK(dwTarget, EXECUTE_WRITECOPY) ;
    SHOWMASK(dwTarget, NOACCESS) ;
}

// 遍历整个虚拟内存并对用户显示其属性的工作程序的方法
void WalkVM(HANDLE hProcess)
{
    // 首先，获得系统信息
    SYSTEM_INFO si;
    :: ZeroMemory(&si, sizeof(si) ) ;
    :: GetSystemInfo(&si) ;

    // 分配要存放信息的缓冲区
    MEMORY_BASIC_INFORMATION mbi;
    :: ZeroMemory(&mbi, sizeof(mbi) ) ;

    // 循环整个应用程序地址空间
    LPCVOID pBlock = (LPVOID) si.lpMinimumApplicationAddress;
    while (pBlock < si.lpMaximumApplicationAddress)
    {
        // 获得下一个虚拟内存块的信息
        if (:: VirtualQueryEx(
            hProcess,						// 相关的进程
            pBlock,                         // 开始位置
			&mbi,                           // 缓冲区
            sizeof(mbi))==sizeof(mbi) )		// 大小的确认
        {
            // 计算块的结尾及其大小
            LPCVOID pEnd = (PBYTE) pBlock + mbi.RegionSize;
			TCHAR szSize[MAX_PATH];
            :: StrFormatByteSize(mbi.RegionSize, szSize, MAX_PATH) ;

            // 显示块地址和大小
            std :: cout.fill ('0') ;
            std :: cout
                << std :: hex << std :: setw(8) << (DWORD) pBlock
                << "-"
                << std :: hex << std :: setw(8) << (DWORD) pEnd
                << (:: strlen(szSize)==7? " (" : " (") << szSize
                << ") " ;

            // 显示块的状态
            switch(mbi.State)
            {
                case MEM_COMMIT :
					std :: cout << "Committed" ;
					break;
                case MEM_FREE :
					std :: cout << "Free" ;
					break;
                case MEM_RESERVE :
					std :: cout << "Reserved" ;
					break;
            }
            // 显示保护
			if(mbi.Protect==0 && mbi.State!=MEM_FREE)
            {    mbi.Protect=PAGE_READONLY;     }
			ShowProtection(mbi.Protect);
            // 显示类型
            switch(mbi.Type){
                case MEM_IMAGE :
					std :: cout << ", Image" ;
					break;
				case MEM_MAPPED:
					std :: cout << ", Mapped";
					break;
                case MEM_PRIVATE :
					std :: cout << ", Private" ;
					break;
			}
            // 检验可执行的影像
            TCHAR szFilename [MAX_PATH] ;
            if (:: GetModuleFileName (
                (HMODULE) pBlock,		// 实际虚拟内存的模块句柄
				szFilename,             //完全指定的文件名称
				MAX_PATH)>0)            //实际使用的缓冲区大小
            {
                // 除去路径并显示
                :: PathStripPath(szFilename) ;
                std :: cout << ", Module: " << szFilename;
			}
            std :: cout << std :: endl;
			// 移动块指针以获得下一下个块
            pBlock = pEnd;
        }
    }
}

void ShowVirtualMemory()
{
    // 首先，让我们获得系统信息
    SYSTEM_INFO si;
    :: ZeroMemory(&si, sizeof(si) ) ;
    :: GetSystemInfo(&si) ;
    // 使用外壳辅助程序对一些尺寸进行格式化
    TCHAR szPageSize[MAX_PATH];
    ::StrFormatByteSize(si.dwPageSize, szPageSize, MAX_PATH) ;
    DWORD dwMemSize = (DWORD)si.lpMaximumApplicationAddress -
          (DWORD) si.lpMinimumApplicationAddress;
    TCHAR szMemSize [MAX_PATH] ;
    :: StrFormatByteSize(dwMemSize, szMemSize, MAX_PATH) ;
    // 将内存信息显示出来
    std :: cout << "Virtual memory page size: " << szPageSize << std :: endl;

    std :: cout.fill ('0') ;
    std :: cout << "Minimum application address: 0x"
            << std :: hex << std :: setw(8)
            << (DWORD) si.lpMinimumApplicationAddress
            << std :: endl;
    std :: cout << "Maximum application address: 0x"
            << std :: hex << std :: setw(8)
            << (DWORD) si.lpMaximumApplicationAddress
            << std :: endl;

    std :: cout << "Total available virtual memory: "
            << szMemSize << std :: endl ;
}
void main()
{
	//显示虚拟内存的基本信息
	ShowVirtualMemory();
    // 遍历当前进程的虚拟内存
	::WalkVM(::GetCurrentProcess());
	getchar();
}



/*  附录的源程序 */
/*  Remove newlines */
#include <stdio.h>
main()
{
  int c,n=0,max=1;
  while((c=getchar())!=EOF)
  {
     if (c=='\n')
       n++;
     else
       n=0;
     if (n<=max)
       putchar( c);
   }
}