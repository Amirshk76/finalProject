#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>


 typedef struct token{
    char *tok;
  struct token* next;
    int li;
    int tp;
}token;

typedef struct line
{
char *ls;
struct line *next;
int parent;
} line ;

typedef struct table
{
    /*name identifier*/
    char att[200][20];
    char typ[200][20];
    char value[200][20];
}table;

FILE* result;
char ide[100][50];/*identifier in table for IR Code*/
char numb[100][50];/*Number in Table For IR Code*/
int usedid[100],usednum[100];
token *tm;
table st;
int searchtan(token *a);
int searchtai(token *a);
bool ncheck(token *a);
bool used_id(token *a);
bool used_num(token *a);
int searchtan(token *a);
int state(int a);
int inat();
int typecast(token *a,token *b,char f[10]);
int searchtaatt(token *a);
int searchtatype(token *a);
int searchtaval(token *a);
int searchta(token *a);
int lin=1;
int error=0;
int block = 0;
int cblock = 0;
void IR_code(int a,token *b);
void showtan();
void showtai();
void writetan();
void writetai();
void nahaii(token *a);
void writeta();
void trueline();
void show();
void prp();
void delinc();
void insert(token *z);
void gettoken();
void add(token *a);
void type(token *a);
int machine(void);
FILE *inc,*p;
token* start;
char key[15][20]={{" "},{"main"},{"if"},{"else"},{"while"},{"int"},{"char"},{"bool"},{"NULL"},{"void"},{"float"}};
enum type{keyword=1,identifier,operate,chr,punc,num,bol};
int main()
{
    int e=1,time=0;
    for(time=0;time<2;time++)
    {
        printf("prosecing");
        usleep(500000);
        system("cls");
        printf("prosecing.");
        usleep(500000);
        system("cls");
        printf("prosecing..");
        usleep(500000);
        system("cls");
        printf("prosecing...");
        usleep(500000);
        system("cls");
    }
    start=(token *)malloc(sizeof(token));
    start->next=NULL;
    gettoken();
    e=inat();
    if(e!=1)
    trueline();
    tm=start->next;
    machine();
    writeta();
    javab();
    writetai();
    writetan();
  //  showtable();
    result=fopen("result.txt","w+");
    if(error!=-1)
    IR_make();
    else
    printf("\nWARNING : IR CODE can't be made.There should be some problems with code\ns");
//  showtai();
// showtan();
    //show();
 // handelmain();
 // handwhile();
}

void add(token* a)
{
    if(strcmp(a->tok," ")!=0)
    {
        token *p,*temp;
        p=(token*)malloc(sizeof(token));
        p->tok=strdup(a->tok);
        type(a);
        p->li=a->li;
        p->tp=a->tp;
        p->next=NULL;
        temp=start;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=p;
    }
}
void type(token *a)
{

    int digit=0,y=0;
    char s[20];
    strcpy(s,a->tok);
    int j;
    int dot=0;
    for(j=1;j<=10;j++)
    {
    if(strcmp(key[j],s)==0)
    {
    a->tp=keyword;
    y=1;
    }
    }
    for(j=0;j<=strlen(s)-1;j++)
    {
    if(!((isdigit(s[j])) || (s[j]=='.')))
    {
    break;
    }
    if(s[j]=='.')
    {
    dot++;
    }

    }
    if((j==strlen(s)) && (dot<=1)&&(s[0]!=NULL))
    {
    a->tp=num;
    digit=1;
    }

    if(strcmpi(s,"true")==0 || strcmpi(s,"false")==0)
    {
    a->tp=bol;
    }
    if((strcmpi(s,"{")==0)||(strcmpi(s,"}")==0)||(strcmpi(s,"(")==0)||(strcmpi(s,")")==0)||(strcmp(s,";")==0)||(strcmp(s,",")==0))
    {
    a->tp=punc;
    }

    if(digit!=1)
    {
    for(j=0;j<=strlen(s)-1;j++)
    {
    if(!((isupper(s[j]))||(islower(s[j]))||(isdigit(s[j]))))
    {
    break;
    }
    }
    if(j==strlen(s) && y!=1 && strcmpi(s,"true")!=0 && strcmpi(s,"false")!=0 && strcmp(s,"max")!=0 && strcmp(s,"min")!=0)
    {
    a->tp=identifier;
    }
    }

    if((strcmpi(s,"+")==0)||(strcmpi(s,"*")==0)||
       (strcmpi(s,"/")==0)||(strcmpi(s,"-")==0)||
       (strcmpi(s,"<")==0)||(strcmpi(s,">")==0)||
       (strcmpi(s,"&&")==0)||(strcmpi(s,"||")==0)||
       (strcmpi(s,"==")==0)||(strcmpi(s,"!=")==0)||(strcmpi(s,"=")==0)||(strcmpi(s,">=")==0)||(strcmpi(s,"<=")==0))
    {
    a->tp=operate;
    }

    if((strlen(s)==3)&&(s[0]=='\'')&&(s[2]=='\''))
    {
        a->tp=chr;
    }
    return 0;
}

void gettoken()
{
    int i=1,o,j=0;
    p=fopen("input.c","r+");
    if(p==NULL)
    {
        printf("Can Not Open File");
        exit(1);
    }
    token *a;
    char str[100],b[15],c[15];
    for(o=0;o<15;o++)
        b[o]='\0';
    a=(token*)malloc(sizeof(token));
    a->next=NULL;

    while(!feof(p))
    {
        fgets(str,100,p);
       if(feof(p))
            break;
        for(j=0;j<strlen(str);j++)
            {
                if(str[j]!=' ' && str[j]!='\n' && str[j]!='\t')
                {
                        b[o]=str[j];
                        c[o]=b[o];
                        o++;
                    if(j==strlen(str)-1 && feof(p))
                    {
                        if(strcmp(a->tok," ")!=0)
                       {
                            strcpy(a->tok,b);
                            a->li=i;
                            add(a);
                        }
                    }
                }
                else
                {
                    if(strcmp(b," ")!=0 && strcmp(b,"\0")!=0)
                    {
                        strcpy(a->tok,b);
                        a->li=i;
                        add(a);
                        for(o=0;o<15;o++)
                        {b[o]=0;}
                        o=0;
                    }
                }
            }
        j=0;
        i++;
    }
}

void showtable()
{
    int i=0;
    while(strcmpi(st.att[i],"\0")!=0)
    {
        printf("%s\t",st.att[i]);
        printf("%s\t",st.typ[i]);
        printf("%s\n",st.value[i]);
        i++;
    }
}

void show()
{
    token *p;
    p=start->next;
    while(p!=NULL)
    {
        printf("%s\t",p->tok);
        printf("%d\t",p->li);
        printf("%d\n",p->tp);
        p=p->next;
    }
}

void prp(char b[])
{
    token *p,*q;
    int i,j=0,t=0,y=0;
    char f[25];
    for(i=0;i<25;i++)
        f[i]=0;
    p=start;
    while(p!=NULL)
    {
        if(strcmp(p->tok,"#include")==0)
        {
            q=p->next;
            y=1;
            break;
        }
        if(strcmp(p->tok,"include")==0)
        {
            error=-1;
            printf("ERROR : In Line %d Your include is not completed needed '#'\n",lin);
            break;
        }
        /*if(strcmp(p->next->tok,"<")!=0)
        {
            error=-1;
            printf("ERROR : Line %d expected see \" < \" ",p->next->tok);
            break;
        }*/
        p=p->next;
    }
    if(y==1)
    {
        for(i=1;i<strlen(q->tok)-1;i++,j++)
        {
            f[j]=q->tok[i];
        }
    }
    if(y==1)
    strcpy(b,f);
    else
    strcpy(b,"empety");
}

int inat()
{
    int j,o=0;
    char f[20];
    prp(f);
    if(!strcmp(f,"empety"))
        return 1;
    inc=fopen((const char*)f,"r+");
    if(inc==NULL)
    {
        printf("Can Not Open Your include\n");
        return 1;
    }
    token *a,*temp,*m;
    m->tok="*end*";
    temp=start;
    char str[100],b[15],c[15];
    for(o=0;o<15;o++)
    b[o]=0;
    a=(token*)malloc(sizeof(token));
    a->next=NULL;
    delinc();
    while(!feof(inc))
    {
    fgets(str,100,inc);
    if(feof(inc))
        break;
    for(j=0;j<strlen(str);j++)
        {
            if(str[j]!=' ' && str[j]!='\n')
            {
            b[o]=str[j];
            c[o]=b[o];
            o++;
            }

            else
            {
                if(strcmp(b," ")!=0 && strcmp(b,"\0")!=0)
                    {
                        a->tok=strdup(b);
                        a->li=lin;
                        addafadr(a,temp);
                        temp=temp->next;
                        for(o=0;o<15;o++)
                        {b[o]=0;}
                        o=0;
                    }
            }
        }
        lin++;
        j=0;
    }
addafadr(m,temp);
    return 5;
}

void addafadr(token *c,token *e)
{
    token *p,*temp;
    p=(token*)malloc(sizeof(token));
    p->tok=strdup(c->tok);
    type(c);
    p->li=c->li;
    p->tp=c->tp;
    p->next=NULL;
    temp=e->next;
    e->next=p;
    p->next=temp;
}

void delinc()
{
    token *a,*b,*c;
    a=start->next;
    b=a->next;
    start->next=b->next;

}

void trueline()
{
    int c=0,d=0,fla=0;
    token *z,*befor,*aval;
    z=start->next;

    while(strcmpi(z->tok,"*end*")!=0)
    {
        befor=z;
        z=z->next;
    }
    aval=z->next;
    befor->next=aval;
    c=aval->li;

    while(aval!=NULL)
    {

        while(aval->li==c)
        {
            aval->li=lin;
            if(aval->next!=NULL)
            aval=aval->next;
            else
                {fla=1;
                break;
                }

        }
        if(fla==1)
            break;
        c++;
        lin++;
    }
}

void writeta()
{
    int i=0;
    int d;
    token *a;
    char r[10];
    a=start->next;
    while(a->next!=NULL)
    {
        if(strcmp(a->tok,"char")==0 || strcmp(a->tok,"float")==0 || strcmp(a->tok,"int")==0 || strcmp(a->tok,"bool")==0)
         {
            strcpy(r,a->tok);
            if(a->next==NULL && a->next->next==NULL)
            break;
            a=a->next;
            if(ncheck(a->next))
            {
                break;
            }
            while(strcmp(a->tok,";")!=0 && ( strcmp(a->tok,"=")!=0 || !strcmp(a->next->next->tok,",")!=0 ) )
            {
                if(a->tp==identifier)
                {
                    if(searchta(a)==-1 || strcmp(r,"char")==0)
                    {
                        for(d=0;d<strlen(a->tok);d++)
                        {
                            st.att[i][d]=a->tok[d];
                        }
                        for(d=0;d<strlen(r);d++)
                        {
                            st.typ[i][d]=r[d];
                        }

                        if(strcmp(a->next->tok,"=")==0)
                        {
                            {
                                if(strcmp(a->next->next->tok,"'")==0 && strcmp(r,"char")==0)
                                {
                                    for(d=0;d<strlen(a->next->next->tok);d++)
                                    st.value[i][d]=a->next->next->next->tok[d];
                                    a=a->next->next->next->next;
                                }
                                else
                                {
                                    for(d=0;d<strlen(a->next->next->tok);d++)
                                    st.value[i][d]=a->next->next->tok[d];
                                }
                            }
                        }
                    i++;
                    }
                }
                if(a->next==NULL)
                    {
                        break;
                    }
                a=a->next;
            }
         }
         if(a->next==NULL)
            break;
    a=a->next;
    }
}

int searchta(token *a)
{
    int i=0;
    while(strcmpi(st.att[i],"\0")!=0)
    {
        if(strcmp(a->tok,st.att[i])==0)
            {
                error=-1;
                printf("ERROR : In Line %d This identifier '%s' Used  Repeated\n",a->li,a->tok);
                return i;
            }
            i++;
    }
    i=0;
    return -1;
}

int searchtaatt(token *a)
{
    int i=0;
    while(strcmpi(st.att[i],"\0")!=0)
    {
        if(strcmp(a->tok,st.att[i])==0)
            {
                return i;
            }
            i++;
    }
    i=0;
    return -1;
}

int searchtatype(token *a)
{
    int i=0;
    while(strcmpi(st.att[i],"\0")!=0)
    {
        if(strcmp(a->tok,st.typ[i])==0)
            {
                return i;
            }
            i++;
    }
    i=0;
    return 2;
}

int searchtaval(token *a)
{
    int i=0;
    while(strcmpi(st.att[i],"\0")!=0)
    {
        if(strcmp(a->tok,st.att[i])==0 && strcmp(st.value[i],"\0")!=0)
            {
                return i;
            }
            i++;
    }
    i=0;
    return 2;
}

void nahaii(token *a)
{
    char b[10],w[10],v[10];
    token *k;
    int i,g,u,j;
    i=searchtaatt(a);

    if(i==-1)
    {
        error=-1;
        printf("ERROR : In Line %d Unknow identifier '%s' \n",a->li,a->tok);
        return;
    }

    if(a->next==NULL || a->next->next==NULL)
    {
           return ;
    }
    k=a->next->next;

    if(k->next==NULL || k->next->next==NULL)
        {
            return;
        }

    if(strcmp(k->tok,"'")==0)
    {
        strcpy(st.value[i],k->next->tok);
        return;
    }

    if(k->tp==identifier)
    {
        u=searchtaatt(k);

        if(u==-1)
        {
            error=-1;
            printf("ERROR : In Line %d Unknow identifier '%s' \n",a->li,k->tok);
            return;
        }
    }

    if(k->next->next->tp==identifier && (strcmp(k->next->tok,";")!=0 && strcmp(k->next->tok,",")!=0))
    {
        u=searchtaatt(k->next->next);

        if(u==-1)
        {
            error=-1;
            printf("ERROR : In Line %d Unknow identifier '%s' \n",a->li,k->next->next->tok);
            return;
        }
    }

    if(k->tp==num && (strcmp(k->next->tok,";")==0 || strcmp(k->next->tok,",")==0))
        {
            if(typecast(a,k,v)!=-1)
            {
                strcpy(st.value[i],k->tok);
                return ;
            }
            else
            {
                error=-1;
                printf("ERROR : In Line %d type of  '%s' is %s BUT type of Num '%s(%s)' is different\n",a->li,a->tok,st.typ[i],k->tok,v);
                strcpy(st.value[i],"unknown");
                return;
            }
        }

    if(k->tp==identifier && (strcmp(k->next->tok,";")==0 || strcmp(k->next->tok,",")==0))
        {
            g=searchtaatt(k);

            if(strcmp(st.value[g],"\0")==0)
            {
                error=-1;
                printf("ERROR : In Line %d the value of '%s' is unknown now\n",a->li,k->tok);
                return;
            }

            if(!strcmp(st.typ[i],st.typ[g]))
            {
                strcpy(st.value[i],st.value[g]);
                return ;
            }

            else
                {
                    error=-1;
                    printf("ERROR : In Line %d type of  '%s' is %s BUT type of '%s' is '%s'\n",a->li,a->tok,st.typ[i],k->tok,st.typ[g]);
                    return ;
                }
        }


    if(k->next->next==NULL)
        {
            return;
        }

    if(k->tp==num)
       {
           if(typecast(a,k,v)!=-1)
            {
                strcpy(b,k->tok);
            }
            else
            {
                error=-1;
                printf("ERROR : In Line %d type of  '%s' is %s BUT type of Num '%s(%s)' is different\n",a->li,a->tok,st.typ[i],k->tok,v);
                strcpy(st.value[i],"unknown");
                return;
            }

       }

    if(k->tp==identifier)
        {
            j=searchtaatt(k);

            if(strcmp(st.value[j],"\0")==0)
                {
                    error=-1;
                    printf("ERROR : In Line %d the value of '%s' is unknown now\n",a->li,k->tok);
                    return ;
                }
            if(!strcmp(st.typ[i],st.typ[j]))
                {
                    strcpy(b,st.value[j]);
                }
            else
                {
                    error=-1;
                    printf("ERROR : In Line %d type of  '%s' is '%s' BUT type of '%s' is '%s'\n",a->li,a->tok,st.typ[i],k->tok,st.typ[j]);
                    return ;
                }

        }

    if(k->next->next->tp==num)
        {
            if(typecast(a,k->next->next,v)!=-1)
            {
                strcpy(w,k->next->next->tok);
            }
            else
            {
                error=-1;
                printf("ERROR : In Line %d type of  '%s' is %s BUT type of Num '%s(%s)' is different\n",a->li,a->tok,st.typ[i],k->next->next->tok,v);
                strcpy(st.value[i],"unknown");
                return;
            }
        }

    if(k->next->next->tp==identifier)
    {
        j=searchtaatt(k->next->next);
        if(strcmp(st.value[j],"\0")==0)
        {
            error=-1;
            printf("ERROR : In Line %d the value of '%s' is unknown now\n",a->li,k->tok);
            return;
        }
        if(!strcmp(st.typ[i],st.typ[j]))
            {
                strcpy(w,st.value[j]);
            }
        else
            {
                error=-1;
                printf("ERROR : In Line %d type of  '%s' is '%s' BUT type of '%s' is '%s'\n",a->li,a->tok,st.typ[i],k->next->next->tok,st.typ[j]);
                return ;
            }

    }

    if(strcmp(k->next->tok,"+")==0)
    {
        if(strcmp(st.typ[i],"float")==0)
        sprintf(st.value[i],"%f",atof(w)+atof(b));
        if(strcmp(st.typ[i],"int")==0)
        sprintf(st.value[i],"%d",atoi(w)+atoi(b));
        return;
    }

    if(strcmp(k->next->tok,"*")==0)
    {
        if(strcmp(st.typ[i],"float")==0)
        sprintf(st.value[i],"%f",atof(w)*atof(b));
        if(strcmp(st.typ[i],"int")==0)
        sprintf(st.value[i],"%d",atoi(w)*atoi(b));
        return;
    }

    if(strcmp(k->next->tok,"-")==0)
    {
        if(strcmp(st.typ[i],"float")==0)
        sprintf(st.value[i],"%f",atof(w)-atof(b));
        if(strcmp(st.typ[i],"int")==0)
        sprintf(st.value[i],"%d",atoi(w)-atoi(b));
        return;
    }

    if(strcmp(k->next->tok,"/")==0)
    {
        if(strcmp(st.typ[i],"float")==0)
        {
            if(strcmp(w,"0"))
            sprintf(st.value[i],"%f",atof(b)/atof(w));
            else
                {
                    error=-1;
                    printf("ERROR : In Line %d devision by zero isnot permited\n",a->li);
                    return;
                }
        }

        if(strcmp(st.typ[i],"int")==0)
        {
            if(strcmp(w,"0"))
            sprintf(st.value[i],"%d",atoi(b)/atoi(w));
            else
            {
                error=-1;
                printf("ERROR : In Line %d devision by zero isnot permited\n",a->li);
                return 0;
            }
        }
    }
}

void javab()
{
    token *t,*befor;
    t=start->next;
    while(t->next!=NULL)
    {
        befor=t;
        t=t->next;
        if(!strcmp(t->tok,"="))
            {
                nahaii(befor);
            }
    }
}

int typecast(token *a,token *b,char f[15])
{
    int i,j,fla=1;
    i=searchtaatt(a);
    if(strcmp(st.typ[i],"int")==0)
    {
        strcpy(f,"float");
        for(j=0;j<strlen(b->tok);j++)
        {
            if(b->tok[j]=='.')
            {
                fla=-1;
                break;
            }
        }
    }
    if(strcmp(st.typ[i],"float")==0)
    {
        strcpy(f,"int");
        fla=-1;
        for(j=0;j<strlen(b->tok);j++)
        {
            if(b->tok[j]=='.')
            {
                fla=1;
                break;
            }
        }
    }
    if(strcmp(st.typ[i],"bool")==0)
    {
        if(strcmpi(b->tok,"true")==0 || strcmpi(b->tok,"false")==0)
        {
         fla=1;
        }
        else
        {
            strcpy(f,"int or float");
            fla=-1;
        }
    }

    return fla;
}

int state(int a)
{
int res;
if(tm->tp==a)
{
res=1;
}else
{
res=0;
}
return res;
}

bool ncheck(token *a)
{
bool res;
if(a==NULL)
{
res=true;
}else{
res=false;
}
return res;
}
