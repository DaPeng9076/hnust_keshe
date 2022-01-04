#include<stdio.h>
#include<math.h>

#define MAX 10000

#define MAX_LEN  100    //���������
int io[MAX_LEN], io_len = 0, now;    //io_len��ʾio��������now��ʾ��ǰ��ͷ���ڴŵ�

void m_printf();
void init();    //��ʼ��
void FIFO();    //�Ƚ��ȳ��㷨
void SSTF();    //��̷���ʱ�������㷨
void SCAN();    //�����㷨
void C_SCAN();  //ѭ��ɨ���㷨

int main() {
    int choice, flag = 0, flag0;   //flag0 = 0ʱ��ʾѡ��ɹ���

	do {
		flag0 = 1;
	    init(); 
	    while(flag0) {
	        printf("��ѡ��ʹ�õĴ��̵����㷨��1_FIFO  |  2_SSTF  |  3_SCAN  |  4_C-SCAN\n");
	        scanf("%d", &choice);
	        switch(choice) {
	            case 1: FIFO(); flag0 = 0; break;
	            case 2: SSTF(); flag0 = 0; break;
	            case 3: SCAN(); flag0 = 0; break;
	            case 4: C_SCAN(); flag0 = 0; break;
	            default:    
	                printf("û�д�ѡ��\n");
	        }
	    } 
	    printf("�Ƿ���������ǣ�1����0)��");
		scanf("%d", &flag); 
	} while(flag);

}

void init() {
    printf("������io����(����-1��ֹ)\n");
    int i = 0;
    while(i < MAX_LEN) {
        scanf("%d", &io[i]);
        if(io[i] == -1)
            break;
        i++;
    }
    io_len = i;
    printf("�����뵱ǰ��ͷλ�ã�");
    scanf("%d", &now);
}

void m_printf() {
	int i;
    for(i = 0; i < MAX_LEN; i++) {
        printf("%d, ", io[i]);
    }
}

void FIFO() {
    int i, len;    //len��ʾ���Ĵŵ���
    double sum = 0;

    printf("��һ�������ʵĴŵ�\t���Ĵŵ���\n");

    for(i = 0; i < io_len; i++) {
        len = abs(now - io[i]);
        now = io[i];
        sum += len;
        printf("%d\t\t\t%d\n", io[i], len);
    }

    printf("ƽ��Ѱ�����ȣ�%.1f\n", sum / io_len);
}

void SSTF() {
    int i, min = MAX, min_num, num = 0;    //min��ʾ��̷���ʱ�䣻num��ʾ�ѷ����io��������
    double sum = 0;

    printf("��һ�������ʵĴŵ�\t���Ĵŵ���\n");
    while(num < io_len) {
        for(i = 0; i < io_len; i++) {
            if(min > abs(now - io[i])) {
                min = abs(now -io[i]);
                min_num = i;
            }
        }
        sum += min;
        printf("%d\t\t\t%d\n", io[min_num], min);
        now = io[min_num];
        num ++;
        io[min_num] = min = MAX;
    }

    printf("ƽ��Ѱ�����ȣ�%.1f\n", sum / io_len);
}

void  SCAN() {
    int i, j, len, temp, now_index;    //now_index��ʾ��������now����Ĵŵ����������±�
    double sum = 0;

    printf("��һ�������ʵĴŵ�\t���Ĵŵ���\n");

    //��io[]����
    for(i = 0; i < io_len-1; i++) {
        for(j = i+1; j < io_len; j++) {
            if(io[i] > io[j]) {
                temp = io[i];
                io[i] = io[j];
                io[j] = temp;
            }
        }
    }

    //��now_index
    for(i = 0; i < io_len; i++) {
        if(io[i] >= now) {
            now_index = i;
            break;
        }
    }

    //������
    for(i = now_index; i < io_len; i++) {
        len = io[i] - now;
        now = io[i];
        sum += len;
        printf("%d\t\t\t%d\n", io[i], len);
    }
    for(i = now_index-1; i >= 0; i--) {
        len = now - io[i];
        now = io[i];
        sum += len;
        printf("%d\t\t\t%d\n", io[i], len);
    }

    printf("ƽ��Ѱ�����ȣ�%.1f\n", sum / io_len);
}

void C_SCAN() {
    int i, j, len, temp, now_index;    //now_index��ʾ��������now����Ĵŵ����������±�
    double sum = 0;

    printf("��һ�������ʵĴŵ�\t���Ĵŵ���\n");

    //��io[]����
    for(i = 0; i < io_len-1; i++) {
        for(j = i+1; j < io_len; j++) {
            if(io[i] > io[j]) {
                temp = io[i];
                io[i] = io[j];
                io[j] = temp;
            }
        }
    }

    //��now_index
    for(i = 0; i < io_len; i++) {
        if(io[i] >= now) {
            now_index = i;
            break;
        }
    }

    //������
    for(i = now_index; i < io_len; i++) {
        len = abs(io[i] - now);
        now = io[i];
        sum += len;
        printf("%d\t\t\t%d\n", io[i], len);
    }
    for(i = 0; i < now_index; i++) {
        len = abs(io[i] - now);
        now = io[i];
        sum += len;
        printf("%d\t\t\t%d\n", io[i], len);
    }

    printf("ƽ��Ѱ�����ȣ�%.1f\n", sum / io_len);
}

