#include<windows.h>
#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

const int READER_COUNT = 3; //���߸���
const int WRITER_COUNT = 1; //д�߸���
const int THREADS_COUNT = READER_COUNT + WRITER_COUNT;	//�ܵ��߳��� 
int count = 0;  //��¼��ǰ�м������߳��ڷ����ļ�
int flag = 1, flag0[THREADS_COUNT];    //flag��ʶ���߳������У�flag0��ʶ���߳����һ�β���
HANDLE Mutex;   //���ڱ�֤��count�����Ļ������
HANDLE rw;      //����ʵ�ֶԹ����ļ��Ļ������
typedef struct {
	int id;
} threadP;

DWORD WINAPI reader(LPVOID);  //�����߳�
DWORD WINAPI writer(LPVOID);  //д���߳�

int main() {
    int i;
    //�������������ź�
    Mutex = CreateMutex(NULL, FALSE, NULL);
    rw = CreateSemaphore(NULL, 1, INT_MAX, NULL);

    HANDLE hThreads[THREADS_COUNT];    //���̵߳�handle
    DWORD readerID[READER_COUNT];   //�������̵߳ı�ʶ��
    DWORD writerID[WRITER_COUNT];   //�������̵߳ı�ʶ��

	threadP tp[THREADS_COUNT]; 
    //���������߳�
    for(i = 0; i < READER_COUNT; i++) {
    	tp[i].id = i+1;
        hThreads[i] = CreateThread(NULL, 0, reader, &tp[i], 0, &readerID[i]);
        if(hThreads[i] == NULL) return -1;
    }
    //����д���߳�
    for(i = 0; i < WRITER_COUNT; i++) {
    	tp[i].id = i+1;
        hThreads[READER_COUNT + i] = CreateThread(NULL, 0, writer, &tp[i], 0, &writerID[i]);
        if(hThreads[READER_COUNT + i] == NULL) return -1;
    }

    while(flag){
        if(getchar()){ //�����������ֹ��������
            flag = 0;
        }
    }
	for(i = 0; i < THREADS_COUNT; i++) {
		while(flag0[i]){}
	}
    printf("�����������\n");

    return 0;
}

DWORD WINAPI reader(LPVOID lpPara) {
	threadP *tp = (threadP*)lpPara;
	int id = tp->id;
    while(flag) {
    	srand((unsigned)time(NULL));
        flag0[id-1] = 1;
        WaitForSingleObject(Mutex, INFINITE);       //P(Mutex)
        count++;
        if(count == 1)  //��һ�����̸߳������ļ�����
			WaitForSingleObject(rw, INFINITE);      //P(rw)
        if(!flag) {     //����������ֹʱ����û��ʼ�������߳���ֹ
            flag0[id-1] = 0;
            return 0;
        } 
        printf("���߳�%d���ļ���...\n", id);
        ReleaseMutex(Mutex);                        //V(Mutex)

        //ģ����ļ�����
        Sleep(rand() % 3000);

        WaitForSingleObject(Mutex, INFINITE);       //P(Mutex)
        printf("���߳�%d���ļ�����\n", id);
        count--;
        if(count == 0)  //��û�ж��߳�ʱ�������ļ�����
            ReleaseSemaphore(rw, 1, NULL);          //V(rw)
        ReleaseMutex(Mutex);                        //V(Mutex)
        flag0[id-1] = 0;
    }
    return 0;
}

DWORD WINAPI writer(LPVOID lpPara) {
	threadP *tp = (threadP*)lpPara;
	int id = tp->id;
    while(flag) {
        srand((unsigned)time(NULL));
        flag0[id+READER_COUNT-1] = 1;
        WaitForSingleObject(rw, INFINITE);          //P(rw)
        if(!flag) {     //����������ֹʱ����û��ʼ�������߳���ֹ
            flag0[id+READER_COUNT-1] = 0;
            return 0;
        } 
        //ģ��д�ļ�
        printf("д�߳�%dд�ļ���...\n", id);
        Sleep(rand() % 5000);
        printf("д�߳�%dд�ļ�����\n", id);

        ReleaseSemaphore(rw, 1, NULL);              //V(rw)
        flag0[id+READER_COUNT-1] = 0;
    }
    return 0;
}

