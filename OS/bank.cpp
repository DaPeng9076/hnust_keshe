#include<iostream>
using namespace std;

const int m = 3, n = 5;
int request[m + 1];
struct state {
    int resource[m];    //��ʾ m ����Դ������
    int available[m];   //��ʾδ����ĸ��ֿ�����Դ����
    int claim[n][m];    //��ʾ n �����̶� m ����Դ���������
    int alloc[n][m];    //��ʾ n �������ѷ���ĸ�����Դ��
    int need[n][m];     //��ʾn����������Ҫ�ĸ�����Դ��
} state;

void init();    //��ʼ��state
void m_print(); //���state
int distribute();  //������Դ
int safe();     //�жϷ�������Ƿ�Ϊ��ȫ״̬
void recycle();    //������ȫʱ���շ��������Դ

int main() {
    int i, flag = 0;

    //��ʼ��
    init();
    printf("��ʼ���ɹ�\n");
    m_print();
    
    while(1) {
        //������Դ
        printf("��������������Ľ��̺�������Դ������");
        for(i = 0; i < m+1; i++) {
            scanf("%d", &request[i]);                         
            if(request[0] == -1)
                return 0;
        }

        //���Է���
        if(!distribute())
            continue;
        
        //����Ƿ�ȫ
        if(!safe()) {
            cout << "����ʧ�ܡ�������Դ��ϵͳ�����벻��ȫ״̬��" << endl;
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
    printf("��Դ������(");
    for(i = 0; i < m; i++) {
        printf("%d%c", state.resource[i], i == m-1 ? ')' : ',');
    }
    printf("\nʣ����Դ����(");
    for(i = 0; i < m; i++) {
        printf("%d%c", state.available[i], i == m-1 ? ')' : ',');
    }
    printf("\n����\t�������\t�ѷ���\t\n");
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
    //�������ʧ�ܣ�����0���ɹ��򷵻�1
    int i, j, flag, index;
    i = j = flag = 0;
    index = request[0] - 1;

    //���������ѷ������Դ�Ƿ񳬹�֮ǰ�������������
    //����ʱϵͳʣ��Ŀ�����Դ�Ƿ��������������
    for(i = 0; i < m; i++) {
        if(state.alloc[index][i] + request[i+1] > state.claim[index][i] || state.available[i] < request[i+1] || request[i+1] < 0) {
            cout << "����+�ѷ������Դ����֮ǰ�������������" << endl;
            cout << "�򣬴�ʱϵͳʣ��Ŀ�����Դ�Ƿ��������������" << endl;
            cout << "���������Դ��С��0" << endl;
            return 0;
        }
    }

    //������Դ�����ĸ����ݽṹ
    for(i = 0; i < m; i++) {
        state.available[i] -= request[i+1];
        state.alloc[index][i] += request[i+1];
        state.need[index][i] -= request[i+1];
    }
    
    m_print();

    return 1;
}

int safe() {
    //����ֵΪ0������ȫ����֮��ȫ

    int i, j, len = 0;     //num��ʾ��ȫ���г���
    int flag0, flag;    //flag0=0��ʾû���ܼ��밲ȫ���еĽ��̣� flag=1��ʾ���Լ��밲ȫ���У�
    int remaining[m], safe_list[n];     //ʣ����Դ�������밲ȫ���еĽ���
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
