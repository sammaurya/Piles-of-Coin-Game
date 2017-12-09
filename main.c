#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

struct pills
{
    int coins;
    int index;
    struct pills *next;
};
struct pills *first=NULL;

void GetNames();
void Print_Name(char []);
void Print_Pills(struct pills *[],int,int);
void Play(struct pills *[],int);
int Check(struct pills *);
char player1[80],player2[80];

int main()
{
    int cases,i,j,n;
    GetNames();
    printf("\nEnter Rounds : ");
    scanf("%d",&cases);
    struct pills *Round[cases];
    for(i=0;i<cases;i++)
    {
        printf("\nEnter no. of pills : ");
        scanf("%d",&n);
        struct pills *ptr;
        ptr=(struct pills *)malloc(sizeof(struct pills));
        first=ptr;
        printf("\nEnter no. of coins : ");
        for(j=1;j<=n;j++)
        {
            if(j==1)
            {
                scanf("%d",&ptr->coins);
                ptr->index=j;
            }
            else
            {
                struct pills *cpt;
                cpt=(struct pills *)malloc(sizeof(struct pills));
                scanf("%d",&cpt->coins);
                cpt->index=j;
                ptr->next=cpt;
                ptr=cpt;
            }
        }
        ptr->next=NULL;
        Round[i]=first;
    }
    Play(Round,cases);
    return 0;
}

void Print_Pills(struct pills *Round[],int x,int cases)
{
    int max,temp,num,i;
    for(i=x;i<cases;i++)
    {
        printf("\n\n\tPills : \n\n\t\t");
        struct pills *cpt,*ptr,*tpt;
        ptr=tpt=Round[i];
        max=tpt->coins;
        num=0;
        while(tpt!=NULL)
        {
            if(tpt->coins>=max)
            {
                max=tpt->coins;
            }
            printf("  %d  ",tpt->coins);
            num++;
            tpt=tpt->next;
        }
        temp=max;
        while(ptr->coins!=max)
        {
            ptr=ptr->next;
        }
        while(ptr->coins!=0)
        {
            printf("\n\n\t\t");
            cpt=Round[i];
            while(cpt->coins<ptr->coins)
            {
                printf("     ");
                cpt=cpt->next;
            }
            while(cpt!=NULL)
            {
                if(ptr->coins<=cpt->coins)
                {
                    printf("  *  ");
                }
                else
                {
                    printf("     ");
                }
                cpt=cpt->next;
            }
            temp--;
            ptr->coins=temp;
        }
        ptr->coins=max;
        printf("\n\t\t");
        cpt=Round[i];
        while(cpt!=NULL)
        {
            printf(" --- ");
            cpt=cpt->next;
        }
        printf("\n\t\t");
        cpt=Round[i];
        while(cpt!=NULL)
        {
            printf(" (%d) ",cpt->index);
            cpt=cpt->next;
        }
        printf("\n");
    }
}

void GetNames()
{
    int i;
    //flag=true;
    printf("\nEnter Player Names : ");
   // do
    //{
        i=0;
        printf("\n\tPlayer 1 : ");
        do
        {
            scanf("%c",&player1[i]);
            i++;
        }while(player1[i-1]!='\n');
        i=0;
        printf("\n\tPlayer 2 : ");
        do
        {
            scanf("%c",&player2[i]);
            i++;
        }while(player2[i-1]!='\n');
    /*    for(j=0;j<10;j++)
        {
            if(player1[0]==j||player2[0]==j)
            {
                printf("\nError : Names Can not start with numbers");
                printf("\nEnter again : ");
                flag=false;
                i=0;
            }
        } */

     //   while(getchar()!='\n');
 //   }while(flag==true);
}
void Print_Name(char name[])
{
    int a=0;
    while(name[a]!='\n')
    {
        printf("%c",name[a]);
        a++;
    }
}
void Play(struct pills *Round[],int cases)
{
    int k=cases,i,j;
    char ch;
    for(i=0;i<cases;i++)
    {
        int flag=true;
        j=1;
        printf("\nPress (Y/N) to Play next round or exit : ");
        scanf(" %c",&ch);
        if(ch=='n'||ch=='N')
        {
            cases=0;
            flag=false;
        }
        else
        {
            printf("\nRound %d ",i+1);
        }

        struct pills *ptr;
        ptr=Round[i];
        while(flag==true)
        {
            if(j%2!=0)
            {
                Print_Pills(Round,i,(cases-(k-i-1)));
                printf("\n\n");
                Print_Name(player1);
                printf("'s Turn : ");
                if(Check(ptr)==0)
                {
                    printf("\nYou have No Moves ");
                    printf("\n\n\t");
                    Print_Name(player2);
                    printf(" WON\n");
                    flag=false;
                }

            }
            else
            {
                Print_Pills(Round,i,(cases-(k-i-1)));
                printf("\n\n");
                Print_Name(player2);
                printf("'s Turn : ");
                if(Check(ptr)==0)
                {
                    printf("\nYou have No Moves ");
                    printf("\n\n\t");
                    Print_Name(player1);
                    printf(" WON\n");
                    flag=false;
                }
            }
            j++;
        }

    }
}
int Check(struct pills *ptr)
{
    int p,flag1=false,flag2=false;
    struct pills *cpt,*tpt;
    printf("\n\tSelect the Pill : ");
    do
    {
        tpt=cpt=ptr;
        scanf("%d",&p);
        while(tpt->index!=p)
        {
            tpt=tpt->next;
        }
        if((tpt->coins)%2==0)
        {
            tpt->coins=(tpt->coins)/2;
            flag1=true;
        }
        else
        {
            while(cpt!=NULL&&flag2==false)
            {
                if((cpt->coins)%2==0)
                {
                    flag2=true;
                }
                cpt=cpt->next;
            }
            if(flag2==true)
            {
                printf("\n\tPill %d contains Odd Coins\n\tSelect another Pill : ",p);
            }
        }
    }while(flag1!=true&&flag2==true);
    if(flag1==true)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
