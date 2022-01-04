#include<iostream>
using namespace std;

const int m = 3, n = 5;
int request[m + 1];
struct state {
    int resource[m];    //表示 m 种资源的总量
    int available[m];   //表示未分配的各种可用资源数量
    int claim[n][m];    //表示 n 个进程对 m 类资源的最大需求
    int alloc[n][m];    //表示 n 个进程已分配的各种资源数
    int need[n][m];     //表示n个进程仍需要的各种资源数
} state;

void init();    //初始化state
void m_print(); //输出state
int distribute();  //分配资源
int safe();     //判断分配完后是否为安全状态
void recycle();    //当不安全时回收分配出的资源

int main() {
    int i, flag = 0;

    //初始化
    init();
    printf("初始化成功\n");
    m_print();
    
    while(1) {
        //申请资源
        printf("请依次输入申请的进程和所需资源数量：");
        for(i = 0; i < m+1; i++) {
            scanf("%d", &request[i]);                         
            if(request[0] == -1)
                return 0;
        }

        //尝试分配
        if(!distribute())
            continue;
        
        //检查是否安全
        if(!safe()) {
            cout << "分配失败。分配资源后，系统将进入不安全状态。" << endl;
            recycle();
        }
    }


    return 0;
}

void init() {
    int i_resource[m] = {10, 5, 7};
    int i_available[m] = {3,3,2};
    int i_claim[n][m] = {{7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3}};
    int i_alloc[n][m] = {{0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2}};

    for(int i = 0; i < m; i ++) {
        state.resource[i] = i_resource[i];
        state.available[i] = i_available[i];
        for(int j = 0; j < n; j ++) {
            state.claim[j][i] = i_claim[j][i];
            state.alloc[j][i] = i_alloc[j][i]; 
            state.need[j][i] = state.claim[j][i] - state.alloc[j][i];
        }
    }
}

void m_print() {
    int i, j;
    printf("资源总数：(");
    for(i = 0; i < m; i++) {
        printf("%d%c", state.resource[i], i == m-1 ? ')' : ',');
    }
    printf("\n剩余资源数：(");
    for(i = 0; i < m; i++) {
        printf("%d%c", state.available[i], i == m-1 ? ')' : ',');
    }
    printf("\n进程\t最大需求\t已分配\t\n");
    for(i = 0; i < n; i++) {
        printf("%d\t(", i+1);
        for(j = 0; j < m; j++) {
            printf("%d%c", state.claim[i][j], j == m-1 ? ')':',');
        }
        printf(" \t(");
        for(j = 0; j < m; j++) {
            printf("%d%c", state.alloc[i][j], j == m-1 ? ')':',');
        }
        printf(" \t\n");
    }    

    //     //need
    //     for(int i = 0; i < n; i ++) {
    //     for(int j = 0; j < m; j ++) {
    //         printf("%d,",state.need[i][j]);
    //     }
    //     printf("\n");
    // }
}

int distribute() {
    //如果分配失败，返回0，成功则返回1
    int i, j, flag, index;
    i = j = flag = 0;
    index = request[0] - 1;

    //检查申请加已分配的资源是否超过之前声明的最大需求
    //检查此时系统剩余的可用资源是否还能满足这次请求
    for(i = 0; i < m; i++) {
        if(state.alloc[index][i] + request[i+1] > state.claim[index][i] || state.available[i] < request[i+1] || request[i+1] < 0) {
            cout << "申请+已分配的资源超过之前声明的最大需求" << endl;
            cout << "或，此时系统剩余的可用资源是否还能满足这次请求" << endl;
            cout << "或，申请的资源数小于0" << endl;
            return 0;
        }
    }

    //分配资源，更改各数据结构
    for(i = 0; i < m; i++) {
        state.available[i] -= request[i+1];
        state.alloc[index][i] += request[i+1];
        state.need[index][i] -= request[i+1];
    }
    
    m_print();

    return 1;
}

int safe() {
    //返回值为0代表不安全，反之安全

    int i, j, len = 0;     //num表示安全序列长度
    int flag0, flag;    //flag0=0表示没有能加入安全序列的进程； flag=1表示可以加入安全序列；
    int remaining[m], safe_list[n];     //剩余资源数、加入安全序列的进程
    for(i = 0; i < m; i ++) {
        remaining[i] = state.available[i];
    }
    for(i = 0; i < n; i++) {
        safe_list[i] = 0;
    }

    while(len < n) {
        flag0 = 0;
        for(i = 0; i < n; i ++) {
            if(safe_list[i]) continue;

            flag = 1;
            for(j = 0; j < m; j++) {
                if(state.need[i][j] > remaining[j]) {
                    flag = 0;
                    break;
                }
            }
            if(flag) {
                for(j = 0; j < m; j++) {
                    remaining[j] += state.alloc[i][j];
                }
                safe_list[i] = 1;
                len++;
                flag0 = 1;
            }
        }
        if(!flag0)
            return 0;
    }
    return 1;
}

void recycle() {
    int i, index = request[0] - 1;
    for(i = 0; i < m; i++) {
        state.available[i] += request[i+1];
        state.alloc[index][i] -= request[i+1];
        state.need[index][i] += request[i+1];
    }

    m_print();
}
