#include<queue>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
#include<vector>
#include<time.h>
#include<map>
#define inf 0x3f3f3f3f
using namespace std;
const int maxn = 200;
typedef pair<int, int> P;

struct mess{
    int to;//�����
    double dis;
    mess(int t,double di):to(t),dis(di){}
};
struct ma{
    char city_str[maxn];
}number[maxn];
vector<mess> G[maxn];//�����ڽӱ�
int pre[maxn];//����
int tim[maxn];
priority_queue<P, vector<P>, greater<P> > que;//����С����
int star, en;

void menu();
void choice_1_enter();
void choice_2_enter();
void Dijkstra1();
vector<int> getpath(int t);

int main()
{
    char choice;
    while(1)
    {
        system("cls");
        menu();
        choice=getchar();
        switch(choice)
        {
            case '1':choice_1_enter();break;
            case '2':choice_2_enter();break;
            case '3':printf("\n\n\t\t\tллʹ��,�ټ�!\n\t\t\t��������˳�!\n");return 0;break;
            default:
                printf("\n\n\t\t\t������˵��е�����!(1~2)");
        }
    }
    return 0;
}

void menu()
{
    printf("\n\n\n\n\n\n");
    printf("\t\t*****************************************\n\t\t*\t\t\t\t\t*\n");
    printf("\t\t*\tУ԰����ϵͳ\t\t*\n");
    printf("\t\t*\t1.·������\t\t\t\t*\n");
    printf("\t\t*\t2.�鿴��Ϣ\t\t\t\t*\n");
    printf("\t\t*\t3.�˳�\t\t\t\t*\n\t\t*\t\t\t\t��ӭ����*\n");
    printf("\t\t*****************************************\n");
}

void choice_1_enter()
{
    FILE *fp2;
    int s, e;//��ʱ����
    double d;
    if((fp2=fopen("data.txt", "rb") ) ==NULL)//�򿪲������ɹ�
    {
        printf("The file can not be opened.\n");
        exit(1);//���������ִ��
    }
    while(!feof(fp2))
    {
        fscanf(fp2,"%d %d %d", &s, &e, &d);
        G[s].push_back(mess(e,d));
        G[e].push_back(mess(s,d));
    }
    fclose(fp2);
    FILE *fp3;
    if((fp3=fopen("map1.txt","rb"))==NULL)
    {
        printf("The file can not be opened.\n");
        exit(1);
    }
    int num = 0;
    while(!feof(fp3))
    {
        fscanf(fp3,"%s", number[++num].city_str);
    }
    fclose(fp3);
    while(1)
    {
        system("cls");
        printf("\n\n\n");
        FILE *fp1;
        char adr1[100], adr2[100];
        if((fp1=fopen("map.txt","rb"))==NULL)
        {
            printf("The file can not be opened.\n");
            exit(1);
        }
        while(!feof(fp1))
        {
            fscanf(fp1,"%s\n", adr1);
            fscanf(fp1,"%s\n", adr2);
            printf("\t%-40s%s", adr1, adr2);
            printf("\n");
        }
        fclose(fp1);
        printf("\t��������������������յ�\n");
        printf("\t�������:");
        while(1)
        {
            scanf("%d", &star);
            if(star>=1&&star<=32)
                break;
            else
            {
                continue;
            }
        }
        printf("\t�����յ�:");
        while(1)
        {
            scanf("%d", &en);
            if(en>=1&&en<=32)
                break;
            else
            {
                continue;
            }
        }
        printf("\t���·����ʾ:\n");
        Dijkstra1();
        printf("\n\n�Ƿ������ѯ?(Y/N)\n");
        char choice=getchar();
        while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n'){
            choice=getchar();
        }
        if(choice=='Y'||choice=='y')
            continue;
        else
            break;
    }
}

void choice_2_enter()
{

}
vector<int> getpath(int t) {//s -> t
    vector<int> path;
    while(t!=-1) {//�� t �����ߣ�һֱ�ߵ� s
        path.push_back(t);
        t=pre[t];
    }
    reverse(path.begin(),path.end());
    return path;
}

void Dijkstra1()
{
    int dis1[maxn];
    int last;
    fill(dis1, dis1+150, 0);
    dis1[star] = 0;
    que.push(P(0, star));
    while(!que.empty())
    {
        P p = que.top();
        que.pop();
        int tmp = p.second;
        if(p.first > dis1[tmp]) continue;
        for(unsigned int i = 0;i < G[tmp].size(); i++)
        {
            mess m = G[tmp][i];
            if(dis1[m.to] > dis1[tmp] + m.dis)
            {
                dis1[m.to] = dis1[tmp] + m.dis;
                pre[m.to] = tmp;
                que.push(P(dis1[m.to], m.to));
            }
        }
    }
    printf("\t��Ծ���%.d����\n\t\t·��:", dis1[en]);
    vector<int> path1 = getpath(en);
    vector<int>::iterator it=path1.begin();
    printf("%s",number[*it].city_str);
    last = *it;
    ++it;
    for(; it!=path1.end(); it++){
        printf("->");
        for(unsigned int i = 0;i < G[last].size(); i++)
        {
            mess me = G[last][i];
            if(me.to==*it)
            {
                break;
            }
        }
        printf("%s",number[*it].city_str);
        last = *it;
    }
}

