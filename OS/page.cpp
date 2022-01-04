#include<stdio.h>
#include<stdlib.h>

#define len 320  //作业指令数
#define nlen 4   //内存块数

int strs[len];   //存放指令地址
int pages[len];  //存放指令页
int count;  //缺页次数
int time[nlen];    //记录进入内存时间
int flags[nlen];   //Clock算法访问位

//创建一个单向循环列表来表示内存块
typedef struct Block {  
    int block_num;  //块号
    int page_num;   //装进内存的作业页号
    struct Block *next;
} Block, *BlockList;
BlockList blocks[nlen];
BlockList b_clock;

void init();    //初始化
void option();  //选择使用哪种算法
void exchange(int str, int page, int num);    //置换页面
int empty_or_in(int str, int page, int str_num);     //检查内存块为空或指令已在内存中
void OPT(int str, int page, int str_num);     //最佳置换算法
void FIFO(int str, int page, int str_num);    //先进先出置换算法
void LRU(int str, int page, int str_num);     //最近最久未用置换算法
void Clock(int str, int page, int str_num);   //时钟算法

int main() {
    int flag1 = 1;  //控制主程序是否继续
    while(flag1) {
        init();
        option();
        printf("是否继续？(1：继续，0：结束)\n");
        scanf("%d", &flag1);
    }
    return 0;
}

void init() {
    int i, j, m;
     srand(1);  
    count = 0;

    //初始化内存块
    for(i = 0; i < nlen; i++) {
    	blocks[i] = (BlockList)malloc(sizeof(Block));
    	blocks[i]->page_num = -1;
    	blocks[i]->block_num = i+1;
        flags[i] = 0;
	}
	for(i = 0; i < nlen; i++) 
		blocks[i]->next = blocks[(i+1)%nlen]; 

    b_clock = blocks[0];

    //创建指令序列
 for(i = 0; i < 320; ) //初始化地址流
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
    printf("请选择置换算法：1_OPT  |  2_FIFO  |  3_LRU  |  4_Clock\n");
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
                printf("没有此选项，请重新选择\n");
                break;
        }        
    }
    printf("缺页率%f\n", (double)count / len);
}

int empty_or_in(int str, int page, int str_num) {
    //返回1表示指令已装入内存
    BlockList b = blocks[0];
    int i;

    for(i = 0; i < nlen; i++) {
        if(b->page_num == -1) {     //块为空
            b->page_num = page;
            time[b->block_num-1] = str_num;
            flags[b->block_num-1] =  1;
            count++;
            printf("指令未装入内存！页面置换完成\n");
            printf("用户指令第%d页第%d条的物理地址为：第%d块第%d条\n\n", page, str % 10+1, b->block_num, str % 10+1);
            return 1;
        }
        if(b->page_num == page) {   //指令在内存中
            printf("指令已在内存中！\n");
            printf("用户指令第%d页第%d条的物理地址为：第%d块第%d条\n\n", page, str % 10+1, b->block_num, str % 10+1);
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
    printf("指令未装入内存且内存块已满！    页面置换完成！\n");
    printf("用户指令第%d页第%d条的物理地址为：第%d块第%d条\n\n", page, str % 10+1, b->block_num, str % 10+1);
}

void OPT(int str, int page, int str_num) {
    BlockList b = blocks[0];
    int i, j, next[nlen], max = 0;     //next表示离当前最近的页地址

    printf("访问第%d条指令  指令地址：%d\n", str_num, str);
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
        if(j == len)    //当前页不再使用
            next[i] = j;

        if(next[max] < next[i]) //选出需要被置换出的内存页
            max = i;
    }

    exchange(str, page, max);
}

void FIFO(int str, int page, int str_num) {
    BlockList b = blocks[0];
    int i, earliest = 0;

    printf("访问第%d条指令  指令地址：%d\n", str_num, str);
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

    printf("访问第%d条指令  指令地址：%d\n", str_num, str);
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
    int i, index, temp = -1;	//temp代表需要置换的页面 

    printf("访问第%d条指令  指令地址：%d\n", str_num, str);
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

