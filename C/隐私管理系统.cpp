#include<stdio.h>
#include<string.h>
#include<iostream>
#define max 20 
typedef struct information{
    int num ;
    char href[50];
    char description[30];
    char name[30];
    char pw[15];
} INF;


void Printf(INF *infor , int i ){
     
    	printf("\n");
        printf("%d\t" , infor[i].num);
        printf("%-30s\t",infor[i].href);
        printf("%-30s\t",infor[i].description);
        printf("%-30s\t" , infor[i].name);
        printf("%-15s\t" , infor[i].pw);
        printf("\n");

}



void search01(INF *infor , int n ){
    int i ,num,flag;
    flag = 0 ;
    printf("��������Ҫ��ѯ�ı�ţ�") ; scanf("%d" , &num);
    for (i = 0 ; i < n ; i ++ ){
        if(infor[i].num==num){
			if(!flag)printf("���\t�˺�λ��\t                �˺�����\t                �˺���\t                        ����\n");
			Printf(infor ,i);	
			flag = 1;
		}
    }
    if(!flag){printf("�˺Ų�����");}
}

void search02(INF *infor , int n ){
    int i ,flag;
    flag = 0 ;
    char name[30];
    printf("��������Ҫ��ѯ���˺ţ�"); scanf("%s" , name);
    for( i = 0 ; i < n ; i ++ ){
        if(strstr(infor[i].name,name)!=NULL){
			if(!flag)printf("���\t�˺�λ��\t                �˺�����\t                �˺���\t                        ����\n");           
		    Printf(infor,i);
            flag = 1; 
        }
    }    
    if(flag==0) printf("��Ҫ���ҵ��˺Ų����ڣ�\n");
}




int menu()
{
    int n,i=0;  
    printf("\n--------------------���˵�-------------------\n\n");
	    printf("             1.¼����Ϣ\n");
	    printf("             2.�����Ϣ\n");
	    printf("             3.��ѯ��Ϣ\n");
	    printf("             4.ɾ����Ϣ\n");
	    printf("             5.�޸���Ϣ\n");
	    printf("             6.��Ϣ�����ļ�\n");
	    printf("             7.�ļ�������Ϣ\n");
	    printf("             8.�˳�ϵͳ\n");
    printf("\n---------------------------------------------\n");
    do
    {
    	if(i>0) {
			printf("û�д˲���~������ѡ��");
	        scanf("%d",&n);
		}else{
			printf("��ѡ�������");
	        scanf("%d",&n);
		}
		i++;
    }
    while(n<1||n>8);
    return (n);
}

int input (INF *infor,int n ){
    int i , j , num ,flag = 0 ;
    printf("���������������ݵ�������") ;
    scanf("%d",&num);
    printf("\n");
    for ( i = 0 ; i < num ; i ++ ){
        printf("��%d�飺\n",i+1);
        printf("��ţ�");scanf("%d" , &infor[n+i].num);
        while(!flag){
	        for( j = 0 ; j < n+i; j ++ ){
	        	if(infor[j].num==infor[n+i].num){
	        		printf("���б��Ϊ%d���˺ţ�����������!\n\n" , infor[i].num);
	        		printf("��ţ�") ;
					scanf("%d" , &infor[n+i].num);
					break;
				}
			}	
			if(j==n+i) flag = 1;
		}
        printf("�˺�λ�ã�");scanf("%s" , infor[n+i].href);
        printf("�˺�������");scanf("%s",infor[n+i].description);
        printf("�˺�����");scanf("%s" , infor[i+n].name);
        printf("���룺");scanf("%s" , infor[i+n].pw);
        printf("\n");
        flag = 0 ;
    }
    return num +n ;
    
}

void output( INF *infor , int n){
	if(!n){
		printf("û���˺���Ϣ��������!\n");
		return  ; 
	}
	
	int i ;
	printf("���\t�˺�λ��\t                �˺�����\t                �˺���\t                        ����\n"); 
    printf("-----------------------------------------------------------------------------------------------------------------\n	\n");
	for ( i = 0 ; i < n ; i ++ ){
        
        printf("%d\t" , infor[i].num);
        printf("%-30s\t",infor[i].href);
        printf("%-30s\t",infor[i].description);
        printf("%-30s\t" , infor[i].name);
        printf("%-15s\t" , infor[i].pw);
        printf("\n");
    }
}



void search(INF *infor , int n ){
    if(!n){
    	printf("û���˺���Ϣ��������!\n");
		return  ; 
	}
	
	int i , choice;        
	printf("-------------��ѯ�˵�-------------\n"); 
    printf("ѡ���ѯ��ʽ��\n");
    printf("           1������Ų�ѯ��\n");
    printf("           2�����˺�����ѯ��\n");
    printf("ѡ��"); scanf("%d" , &choice);

    switch (choice){
	    case 1:
	        search01(infor , n );
	        break;
	    case 2:
	        search02(infor , n );
	        break;
    }
}

int Delete(INF *infor , int n ){
    int i ,j,num , flag=-1;
    printf("��������Ҫɾ�����˺ű�ţ�"); scanf("%d" , &num);
    for( i = 0 ; i < n ; i ++ ){
        if(infor[i].num==num){
            printf("��ȷ��Ҫɾ��%s����������1������������0:  ",infor[i].name); scanf("%d",&flag);
            printf("\n");
        }
        if(flag==1){
            if(n-1!=0)
            for(j=i; j<n-1; j++)
            {
                infor[j]=infor[j+1];
                strcpy(infor[j].href,infor[j+1].href);
                strcpy(infor[j].description,infor[j+1].description);
                strcpy(infor[j].name,infor[j+1].name);
                strcpy(infor[j].pw,infor[j+1].pw);
            }
            printf("���ѳɹ�ɾ�����Ϊ%d���˺�!\n",num);
            return n-1;
        }
        if(flag==0){
        	printf("���˳�ɾ��~\n");
		}
    
    }if(i==n) printf("�����ڱ��Ϊ%d���˺ţ�\n" , num);
	return n ;
}


void modify ( INF *infor , int n ){
    int i , num,choice,flag1=0,flag2=0; 

    printf("������������ĵ��˺ű��:") ; scanf("%d" , &num);
    for( i = 0 ; i < n ; i ++ ){
        if(infor[i].num==num){
            flag1=1;
            break;
        }
    }
    if(!flag1){
        printf("û�д˱�ţ����˳��޸�~");
        return ;
    }
    printf("���޸��˺�%s,ȷ��������1���˳�������0��" , infor[i].name);scanf("%d" , &flag2);
    if(!flag2){
        printf("  ---���˳�~~"); 
        return ;
    }
    else{
        printf("������������ĵ���Ϣ��\n");
        printf("      1���޸ı�ţ�\n");
        printf("      2���޸��˺�λ�ã�\n");
        printf("      3���޸��˺�������\n");
        printf("      4���޸��˺�����\n");
        printf("      5�����롣\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("������Ҫ�滻�ı�ţ�");
            scanf("%d",&infor[i].num);
            printf("  --���滻~"); 
            break;
        case 2:
            printf("������Ҫ�滻���˺�λ�ã�");
            scanf("%s",infor[i].href);
            printf("  --���滻~");
			break;
        case 3:
            printf("������Ҫ�滻���˺�������");
            scanf("%s" , infor[i].description);
            printf("  --���滻~");
			break;
        case 4:
            printf("������Ҫ�滻���˺�����");
            scanf("%s" , infor[i].name);
            printf("  --���滻~");
			break;
        case 5:
            printf("������Ҫ�滻�����룺");
            scanf("%s" , infor[i].pw);
            printf("  --���滻~");
			break;
		default:
			printf("û�д˲���~"); 
        }
    }    
}


void fileWrite ( INF *infor , int n ){
    FILE *fp ;
    int i , j ;
    char fileName[50] ;
    printf("�����뵼���ļ��������磺G:\\f1\\message.txt:\n");
    scanf("%s" , fileName);
    if(NULL==(fp=fopen(fileName,"w"))){
        printf("�ļ���ʧ��!\n");
        return;
    }
    for( i = 0 ; i < n ; i ++ ){
        for( j = 0 ; j < strlen(infor[i].pw); j ++ ){
            infor[i].pw[j]++;
        }
        fprintf(fp,"%d %s %s %s %s\n" , infor[i].num , infor[i].href ,infor[i].description,infor[i].name,infor[i].pw);
    }
    if (i == n ) printf("�Ѿ��ɹ������ݵ���%s�ļ�������\n" , fileName);
    if(fclose(fp)){
        printf("�޷��ر��ļ�!\n");
    }
}
int fileRead (INF *infor){
    int i,j;
    FILE *fp;
    char fileName[20];
    printf("�����뵼���ļ��������磺G:\\f1\\message.txt:\n");
    scanf("%s" , fileName);
    if(NULL==(fp = fopen(fileName ,"rb"))){
        printf("�ļ���ʧ�ܣ�\n");
        return 0 ;
    }
    i = 0 ; 
    while(!feof(fp)){
        fscanf(fp,"%d %s %s %s %s\n" , &infor[i].num , infor[i].href ,infor[i].description,infor[i].name,infor[i].pw);
        for( j = 0 ; j < strlen(infor[i].pw);j++){
            infor[i].pw[j]--;
        }
		i++;
    }
    fclose(fp);
    printf("�Ѿ��ɹ����ļ�%s�������ݣ�����\n" , fileName);
    return i ;
}



int main(void){

    int i , n ,  flag;
	n = flag = 0 ; 
    INF infor[max] ;

    char password[20] = {"1"} , inputs[20];
    printf("                    ��˽����ϵͳ��\n");
    printf("---------------------------------------------------------\n	\n");
			    
	printf("����������:\n");
    for ( i = 0 ; i < 3 ; i ++ ){
        scanf("%s" ,inputs);
        if (!strcmp(password,inputs)){
            printf("������ȷ��\n");
            flag = 1 ;
            break;
        }
        else{
            if(i==2) printf("���ǷǷ��û�!\n");
            else printf("����������������룡\n");
        }
    }

    while(flag){
        switch (menu())
        {
        case 1:
            n = input( infor , n );
            break;
        case 2:
            output( infor , n );
            break;
        case 3:
            search( infor , n );
            break;
        case 4:
            n=Delete( infor , n );
            break;
       case 5:
            modify( infor , n );
            break;
        case 6:
            fileWrite( infor , n );
            break;
         case 7:
            n=fileRead( infor  ); 
            break;
        case 8:
            exit(0);
        }
    }

    return 0 ;
}




