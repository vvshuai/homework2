#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
int Symbolword(string str);
int Englishword(char x);
int Figure(char x);
void deal();
string symbol[11]={"void","int","float","char","if","else","while","do","for","return","main"};//特殊英文字符串
int count=1;//当前所在行数
int arr[100],Count=0;//错误所在行数组，错误个数
char strs[1000];


int main()
{
    for(int i=0;;i++){
        scanf("%c",&strs[i]);
        if(strs[i]=='#'){
            break;
        }
    }
    deal();
    return 0;
}


int Symbolword(string str){  //判断特殊字符串返回种别码
    int i,m;
    for(i=0;i<11;i++){
        if(str==symbol[i]){
            m=i+3;
            return m;
        }
    }
    return 0;
}


int Englishword(char x){ //判断是否是英文字母
    if((x>='A'&&x<='Z')||(x>='a'&&x<='z')){
        return 1;
    }else{
        return 0;
    }
}
int Figure(char x){  //判断是否是数字
    if(x>='0'&&x<='9'){
        return 1;
    }else{
        return 0;
    }
}


void deal(){
    int n;
    int j=0;//计数str数组；
    char str[100];//输入连续字母；
    int i=-1;
    while(1){
        i++;
        if(strs[i]=='#')
            break;
        if(strs[i]==' '||strs[i]=='\t')
            continue;
        else if(strs[i]=='\n'&&strs[i-1]!='\n'&&strs[i-1]!=' '){
            printf("\n");
            count++;
        }
        else if(Figure(strs[i])){ //处理数字；
            while(Figure(strs[i])){
                str[j]=strs[i];
                j++;
                i++;
            }
            str[j]='\0';
            if(Englishword(strs[i])){ //处理字母；
                j=0;
                while(Englishword(strs[i])){
                    i++;
                }
                printf("LexicalError,");
                arr[Count]=count;
                Count++;
            }else{
                i--;
                printf("<2,");
                printf("%s",str);
                printf(">,");
            }
        }
        else if(Englishword(strs[i])){
            j=0;
            while(Englishword(strs[i])){
                str[j]=strs[i];
                j++;
                i++;
            }
            str[j]='\0';
            j=0;
            i--;
            n=Symbolword(str);  //判断是否是特殊字符；
            if(n){
                printf("<%d,->,",n);
            }else{
                printf("<1,");
                printf("%s",str);
                printf(">,");
            }
        }
        else{
            if(strs[i]=='/'){  //处理注释
                i++;
                if(strs[i]=='/'){
                    while(1){
                        i++;
                        if(strs[i]=='\n'){
                            break;
                        }
                    }
                   // printf("\n");
                    count++;
                }else if(strs[i]=='*'){
                    while(1){
                        i++;
                        if(strs[i]=='\n')
                            count++;
                        if(strs[i]=='*'){
                            i++;
                            if(strs[i]=='/'){
                                i++;
                                break;
                            }
                            else{
                                i--;
                            }
                        }
                    }
                    //printf("\n");
                    count++;
                }else{
                    i--;
                }
            }
            switch(strs[i]){
                case '+':
                    printf("<14,->,");break;
                case '-':
                    printf("<15,->,");break;
                case '*':
                    printf("<16,->,");break;
                case '/':
                    printf("<17,->,");break;
                case '%':
                    printf("<18,->,");break;
                case '<':
                    i++;
                    if(strs[i]!='='){
                        printf("<19,->,");
                        i--;
                        break;
                    }
                    else{
                        printf("<20,->,");break;
                    }
                case '>':
                    i++;
                    if(strs[i]!='='){
                        printf("<21,->,");
                        i--;
                        break;
                    }
                    else{
                        printf("<22,->,");break;
                    }
                case '=':
                    i++;
                    if(strs[i]!='='){
                        printf("<27,->,");
                        i--;
                        break;
                    }
                    else{
                        printf("<23,->,");break;
                    }
                case '!':
                    i++;
                    if(strs[i]!='='){
                         i--;
                        break;
                    }
                    else{
                        printf("<24,->,");break;
                    }
                case '&':
                    i++;
                    if(strs[i]!='&'){
                        i--;
                        break;
                    }
                    else{
                        printf("<25,->,");break;
                    }
                case '|':
                    i++;
                    if(strs[i]!='|'){
                         i--;
                        break;
                    }
                    else{
                        printf("<26,->,");break;
                    }
                case '(':
                    printf("<28,->,");break;
                case ')':
                    printf("<29,->,");break;
                case '[':
                    printf("<30,->,");break;
                case ']':
                    printf("<31,->,");break;
                case '{':
                    printf("<32,->,");break;
                case '}':
                    printf("<33,->,");break;
                case ';':
                    printf("<34,->,");break;
                case ',':
                    printf("<35,->,");break;
            }
        }
        if(strs[i]=='#'){
            break;
        }
    }
    if(Count!=0){ //输出错误行；
        printf("\nLexicalError(s) on line(s) ");
        for(int i=0;i<Count;i++){
            printf("%d,",arr[i]);
        }
    }
}
