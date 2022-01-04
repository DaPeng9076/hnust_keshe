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
    printf("请输入你要查询的编号：") ; scanf("%d" , &num);
    for (i = 0 ; i < n ; i ++ ){
        if(infor[i].num==num){
			if(!flag)printf("编号\t账号位置\t                账号描述\t                账号名\t                        密码\n");
			Printf(infor ,i);	
			flag = 1;
		}
    }
    if(!flag){printf("账号不存在");}
}

void search02(INF *infor , int n ){
    int i ,flag;
    flag = 0 ;
    char name[30];
    printf("请输入你要查询的账号："); scanf("%s" , name);
    for( i = 0 ; i < n ; i ++ ){
        if(strstr(infor[i].name,name)!=NULL){
			if(!flag)printf("编号\t账号位置\t                账号描述\t                账号名\t                        密码\n");           
		    Printf(infor,i);
            flag = 1; 
        }
    }    
    if(flag==0) printf("你要查找的账号不存在！\n");
}




int menu()
{
    int n,i=0;  
    printf("\n--------------------主菜单-------------------\n\n");
	    printf("             1.录入信息\n");
	    printf("             2.浏览信息\n");
	    printf("             3.查询信息\n");
	    printf("             4.删除信息\n");
	    printf("             5.修改信息\n");
	    printf("             6.信息存入文件\n");
	    printf("             7.文件导入信息\n");
	    printf("             8.退出系统\n");
    printf("\n---------------------------------------------\n");
    do
    {
    	if(i>0) {
			printf("没有此操作~请重新选择：");
	        scanf("%d",&n);
		}else{
			printf("请选择操作：");
	        scanf("%d",&n);
		}
		i++;
    }
    while(n<1||n>8);
    return (n);
}

int input (INF *infor,int n ){
    int i , j , num ,flag = 0 ;
    printf("输入你想输入数据的组数：") ;
    scanf("%d",&num);
    printf("\n");
    for ( i = 0 ; i < num ; i ++ ){
        printf("第%d组：\n",i+1);
        printf("编号：");scanf("%d" , &infor[n+i].num);
        while(!flag){
	        for( j = 0 ; j < n+i; j ++ ){
	        	if(infor[j].num==infor[n+i].num){
	        		printf("已有编号为%d的账号，请重新输入!\n\n" , infor[i].num);
	        		printf("编号：") ;
					scanf("%d" , &infor[n+i].num);
					break;
				}
			}	
			if(j==n+i) flag = 1;
		}
        printf("账号位置：");scanf("%s" , infor[n+i].href);
        printf("账号描述：");scanf("%s",infor[n+i].description);
        printf("账号名：");scanf("%s" , infor[i+n].name);
        printf("密码：");scanf("%s" , infor[i+n].pw);
        printf("\n");
        flag = 0 ;
    }
    return num +n ;
    
}

void output( INF *infor , int n){
	if(!n){
		printf("没有账号信息，请输入!\n");
		return  ; 
	}
	
	int i ;
	printf("编号\t账号位置\t                账号描述\t                账号名\t                        密码\n"); 
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
    	printf("没有账号信息，请输入!\n");
		return  ; 
	}
	
	int i , choice;        
	printf("-------------查询菜单-------------\n"); 
    printf("选择查询方式：\n");
    printf("           1：按编号查询；\n");
    printf("           2：按账号名查询；\n");
    printf("选择："); scanf("%d" , &choice);

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
    printf("请输入你要删除的账号编号："); scanf("%d" , &num);
    for( i = 0 ; i < n ; i ++ ){
        if(infor[i].num==num){
            printf("你确定要删除%s吗？是请输入1，不是请输入0:  ",infor[i].name); scanf("%d",&flag);
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
            printf("你已成功删除编号为%d的账号!\n",num);
            return n-1;
        }
        if(flag==0){
        	printf("已退出删除~\n");
		}
    
    }if(i==n) printf("不存在编号为%d的账号！\n" , num);
	return n ;
}


void modify ( INF *infor , int n ){
    int i , num,choice,flag1=0,flag2=0; 

    printf("请输入你想更改的账号编号:") ; scanf("%d" , &num);
    for( i = 0 ; i < n ; i ++ ){
        if(infor[i].num==num){
            flag1=1;
            break;
        }
    }
    if(!flag1){
        printf("没有此编号！将退出修改~");
        return ;
    }
    printf("将修改账号%s,确定请输入1，退出请输入0：" , infor[i].name);scanf("%d" , &flag2);
    if(!flag2){
        printf("  ---已退出~~"); 
        return ;
    }
    else{
        printf("请输入你想更改的信息：\n");
        printf("      1：修改编号；\n");
        printf("      2：修改账号位置；\n");
        printf("      3：修改账号描述；\n");
        printf("      4：修改账号名；\n");
        printf("      5：密码。\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("输入想要替换的编号：");
            scanf("%d",&infor[i].num);
            printf("  --已替换~"); 
            break;
        case 2:
            printf("输入想要替换的账号位置：");
            scanf("%s",infor[i].href);
            printf("  --已替换~");
			break;
        case 3:
            printf("输入想要替换的账号描述：");
            scanf("%s" , infor[i].description);
            printf("  --已替换~");
			break;
        case 4:
            printf("输入想要替换的账号名：");
            scanf("%s" , infor[i].name);
            printf("  --已替换~");
			break;
        case 5:
            printf("输入想要替换的密码：");
            scanf("%s" , infor[i].pw);
            printf("  --已替换~");
			break;
		default:
			printf("没有此操作~"); 
        }
    }    
}


void fileWrite ( INF *infor , int n ){
    FILE *fp ;
    int i , j ;
    char fileName[50] ;
    printf("请输入导入文件名，例如：G:\\f1\\message.txt:\n");
    scanf("%s" , fileName);
    if(NULL==(fp=fopen(fileName,"w"))){
        printf("文件打开失败!\n");
        return;
    }
    for( i = 0 ; i < n ; i ++ ){
        for( j = 0 ; j < strlen(infor[i].pw); j ++ ){
            infor[i].pw[j]++;
        }
        fprintf(fp,"%d %s %s %s %s\n" , infor[i].num , infor[i].href ,infor[i].description,infor[i].name,infor[i].pw);
    }
    if (i == n ) printf("已经成功将数据导入%s文件！！！\n" , fileName);
    if(fclose(fp)){
        printf("无法关闭文件!\n");
    }
}
int fileRead (INF *infor){
    int i,j;
    FILE *fp;
    char fileName[20];
    printf("请输入导入文件名，例如：G:\\f1\\message.txt:\n");
    scanf("%s" , fileName);
    if(NULL==(fp = fopen(fileName ,"rb"))){
        printf("文件打开失败！\n");
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
    printf("已经成功从文件%s导入数据！！！\n" , fileName);
    return i ;
}



int main(void){

    int i , n ,  flag;
	n = flag = 0 ; 
    INF infor[max] ;

    char password[20] = {"1"} , inputs[20];
    printf("                    隐私管理系统：\n");
    printf("---------------------------------------------------------\n	\n");
			    
	printf("请输入密码:\n");
    for ( i = 0 ; i < 3 ; i ++ ){
        scanf("%s" ,inputs);
        if (!strcmp(password,inputs)){
            printf("口令正确！\n");
            flag = 1 ;
            break;
        }
        else{
            if(i==2) printf("您是非法用户!\n");
            else printf("密码错误，请重新输入！\n");
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




