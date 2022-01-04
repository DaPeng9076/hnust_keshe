#include<stdio.h>
#include<stdlib.h>

#define len 320  //��ҵָ����
#define nlen 4   //�ڴ����

int strs[len];   //���ָ���ַ
int pages[len];  //���ָ��ҳ
int count;  //ȱҳ����
int time[nlen];    //��¼�����ڴ�ʱ��
int flags[nlen];   //Clock�㷨����λ

//����һ������ѭ���б�����ʾ�ڴ��
typedef struct Block {  
    int block_num;  //���
    int page_num;   //װ���ڴ����ҵҳ��
    struct Block *next;
} Block, *BlockList;
BlockList blocks[nlen];
BlockList b_clock;

void init();    //��ʼ��
void option();  //ѡ��ʹ�������㷨
void exchange(int str, int page, int num);    //�û�ҳ��
int empty_or_in(int str, int page, int str_num);     //����ڴ��Ϊ�ջ�ָ�������ڴ���
void OPT(int str, int page, int str_num);     //����û��㷨
void FIFO(int str, int page, int str_num);    //�Ƚ��ȳ��û��㷨
void LRU(int str, int page, int str_num);     //������δ���û��㷨
void Clock(int str, int page, int str_num);   //ʱ���㷨

int main() {
    int flag1 = 1;  //�����������Ƿ����
    while(flag1) {
        init();
        option();
        printf("�Ƿ������(1��������0������)\n");
        scanf("%d", &flag1);
    }
    return 0;
}

void init() {
    int i, j, m;
     srand(1);  
    count = 0;

    //��ʼ���ڴ��
    for(i = 0; i < nlen; i++) {
    	blocks[i] = (BlockList)malloc(sizeof(Block));
    	blocks[i]->page_num = -1;
    	blocks[i]->block_num = i+1;
        flags[i] = 0;
	}
	for(i = 0; i < nlen; i++) 
		blocks[i]->next = blocks[(i+1)%nlen]; 

    b_clock = blocks[0];

    //����ָ������
 for(i = 0; i < 320; ) //��ʼ����ַ��
    {
        int m = rand() % 320;
        strs[i] = m + 1;
        pages[i] = strs[i] / 10;
        i++;

        int m1 = rand() % (m - 1);
        strs[i] = m1;
        pages[i] = m1 / 10;
        i++;

        strs[i] = m1 + 1;
        pages[i] = strs[i] / 10;
        i++;

        int m2 = rand() % (319 - m1 - 1) + m1 + 2;
        strs[i] = m2;
        pages[i] = m2 / 10;
        i++;

        strs[i] = m2 + 1;
        pages[i] = strs[i] / 10;
        i++;
    }
}

void option() {
    int i, choice, flag0 = 1;
    printf("��ѡ���û��㷨��1_OPT  |  2_FIFO  |  3_LRU  |  4_Clock\n");
    while(flag0) {
        scanf("%d", &choice);
        switch(choice) {
            case 1: {
                for(i = 0; i < len; i++) 
                    OPT(strs[i], pages[i], i+1);
                flag0 = 0;
                printf("------OPT-------\n");
                break;
            }
            case 2: {
                for(i = 0; i < len; i++)
                    FIFO(strs[i], pages[i], i+1);
                flag0 = 0;
                printf("------FIFO-------\n");
                break;
            }
            case 3: {
                for(i = 0; i < len; i++) 
                    LRU(strs[i], pages[i], i+1);
                flag0 = 0;
                printf("------LRU-------\n");
                break;
            }
            case 4: {
                for(i = 0; i < len; i++) 
                    Clock(strs[i], pages[i], i+1);
                flag0 = 0;
                printf("------Clock-------\n");
                break;
            }
            default:    
                printf("û�д�ѡ�������ѡ��\n");
                break;
        }        
    }
    printf("ȱҳ��%f\n", (double)count / len);
}

int empty_or_in(int str, int page, int str_num) {
    //����1��ʾָ����װ���ڴ�
    BlockList b = blocks[0];
    int i;

    for(i = 0; i < nlen; i++) {
        if(b->page_num == -1) {     //��Ϊ��
            b->page_num = page;
            time[b->block_num-1] = str_num;
            flags[b->block_num-1] =  1;
            count++;
            printf("ָ��δװ���ڴ棡ҳ���û����\n");
            printf("�û�ָ���%dҳ��%d���������ַΪ����%d���%d��\n\n", page, str % 10+1, b->block_num, str % 10+1);
            return 1;
        }
        if(b->page_num == page) {   //ָ�����ڴ���
            printf("ָ�������ڴ��У�\n");
            printf("�û�ָ���%dҳ��%d���������ַΪ����%d���%d��\n\n", page, str % 10+1, b->block_num, str % 10+1);
            flags[b->block_num-1] = 1;
            return 1;
        }

        b = b->next;
    }
    return 0;
}

void exchange(int str, int page, int num) {
    BlockList b = blocks[0];
    int i;
    for(i = 0; i < num; i++)
        b = b->next;
    b->page_num = page;
    count++;
    printf("ָ��δװ���ڴ����ڴ��������    ҳ���û���ɣ�\n");
    printf("�û�ָ���%dҳ��%d���������ַΪ����%d���%d��\n\n", page, str % 10+1, b->block_num, str % 10+1);
}

void OPT(int str, int page, int str_num) {
    BlockList b = blocks[0];
    int i, j, next[nlen], max = 0;     //next��ʾ�뵱ǰ�����ҳ��ַ

    printf("���ʵ�%d��ָ��  ָ���ַ��%d\n", str_num, str);
    if(empty_or_in(str, page, str_num))
        return ;

    //OPT
    for(i = 0; i < nlen; i++) {
        for(j = str_num; j < len; j++) {
            if(b->page_num == pages[j]) {
                next[i] = j;
                break;
            }
        }
        b = b->next;
        if(j == len)    //��ǰҳ����ʹ��
            next[i] = j;

        if(next[max] < next[i]) //ѡ����Ҫ���û������ڴ�ҳ
            max = i;
    }

    exchange(str, page, max);
}

void FIFO(int str, int page, int str_num) {
    BlockList b = blocks[0];
    int i, earliest = 0;

    printf("���ʵ�%d��ָ��  ָ���ַ��%d\n", str_num, str);
    if(empty_or_in(str, page, str_num))
        return ;

    // FIFO
    for(i = 0; i < nlen; i++) {
        if(time[earliest] > time[i])
            earliest = i;
    }

    exchange(str, page, earliest+1);
    time[b->block_num-1] = str_num;
}

void LRU(int str, int page, int str_num) {
    BlockList b = blocks[0];
    int i, j, prior[nlen], min = 0;

    printf("���ʵ�%d��ָ��  ָ���ַ��%d\n", str_num, str);
    if(empty_or_in(str, page,str_num))
        return ;

    // LRU
    for(i = 0; i < nlen; i++) {
        for(j = str_num-2; j >=0; j --) {
            if(b->page_num == pages[j]) {
                prior[i] = j;
                break;
            }
        }
        b = b->next;
        if(prior[min] > prior[i])
            min = i;
    }

    exchange(str, page, min);
}

void Clock(int str, int page, int str_num) {
    int i, index, temp = -1;	//temp������Ҫ�û���ҳ�� 

    printf("���ʵ�%d��ָ��  ָ���ַ��%d\n", str_num, str);
    if(empty_or_in(str, page,str_num))
        return ;

    //Clock
    while(temp == -1) {
        for(i = 0; i < nlen; i++) {
            index = b_clock->block_num - 1;
            if(flags[index] == 0) {
                temp = index;
                break;
            }
            flags[index] = 0;
            b_clock = b_clock->next;
        }
    }
    exchange(str, page, temp);
    flags[b_clock->block_num-1] = 1;
    b_clock = b_clock->next;

}

