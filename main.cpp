
//  main.c
//  Shortest job first
//
//  Created by SWARA GUPTA on 18/03/18.
//  Copyright © 2018 SWARA GUPTA. All rights reserved.


/*
 Ques. 6. Design a scheduling program that is capable of scheduling many processes that comes
 in at some time interval and are allocated the CPU not more that 10 time units. CPU must
 schedule processes having short execution time first. CPU is idle for 3 time units and does not
 entertain any process prior this time. Scheduler must maintain a queue that keeps the order of
 execution of all the processes. Compute average waiting and turnaround time.
 */

#include <iostream>

struct process{
    int arr,burst,firstt,i,status,burl,compt,waitingt,turnaroundt;
}*run=NULL;
int n,tq=10,px=0;
struct node{
    struct process *q;
    struct node *next;
}*start=NULL,*last,*cn;

int main()
{
    printf("\nEnter total number of the processes you want to execute :");
    scanf("%d",&n);
    int pl=n; //process left
    struct process p[n];
    for(int i=0;i<n;i++)
    {
        printf("\nEnter the details of process %d ",i+1);
        printf("\n\tArrival Time : ");
        scanf("%d",&p[i].arr);
        printf("\tBurst Time : ");
        scanf("%d",&p[i].burst);
        p[i].burl=p[i].burst;
        p[i].i=i+1;
        p[i].status=0;
        p[i].firstt=-1;
        if(p[i].arr>3)
            px++;
    }
    printf("\n\n Details entered are following:");;
    printf("\n ___________________________________________________");
    printf("\n|\tPROCESS\t\t|\tARRIVAL TIME\t|\tBURST TIME\t|");
    printf("\n|_______________|___________________|_______________|");
    for(int i=0;i<n;i++)
    {
        printf("\n|\t\tP%d\t\t|\t\t%d\t\t\t|\t\t%d\t\t|",p[i].i,p[i].arr,p[i].burst);
        printf("\n|_______________|___________________|_______________|");
    }
    
    int time=4,y=1;
    while(pl!=0)
    {
        if(px!=0)
        {
        for(int i=0;i<n;i++)
        {
            if(p[i].arr>3 && p[i].arr<=time && p[i].status==0)                                                //in the queue
            {
                if(start==NULL)
                {
                    p[i].status=1;
                    cn=new node;
                    cn->q=&p[i];
                    cn->next=NULL;
                    last=cn;
                    start=cn;
                }
                else{
                    p[i].status=1;
                    cn=new node;
                    cn->q=&p[i];
                    node *x;
                    x=start;
                    if((start->q->burl)>(cn->q->burl))
                    {
                        cn->next=start;
                        start=cn;
                    }
                    else
                    {
                        while(x->next!=NULL && x->next->q->burl < cn->q->burl)
                        {
                            x=x->next;
                        }
                        cn->next=x->next;
                        x->next=cn;
                    }
                }
                px--;
            }
        }
        }
        if(px==0 && y==1)
        {
            for(int i=0;i<n;i++)
            {
                if(p[i].arr<=3 && p[i].status==0)                                                //in the queue
                {
                    if(start==NULL)
                    {
                        p[i].status=1;
                        cn=new node;
                        cn->q=&p[i];
                        cn->next=NULL;
                        last=cn;
                        start=cn;
                    }
                    else{
                        p[i].status=1;
                        cn=new node;
                        cn->q=&p[i];
                        node *x;
                        x=start;
                        if((start->q->burl)>(cn->q->burl))
                        {
                            cn->next=start;
                            start=cn;
                        }
                        else
                        {
                            while(x->next!=NULL && x->next->q->burl < cn->q->burl)
                            {
                                x=x->next;
                            }
                            cn->next=x->next;
                            x->next=cn;
                        }
                    }
                }
            }
            y--;
        }
        if(run==NULL)   //running of process
        {
            if(start!=NULL)
            {
                run=start->q;
                start=start->next;
                if(run->firstt==-1)
                {
                    run->firstt=time;
                }
                if(run->burl<=tq)
                {
                    printf("\nProcess P%d running from time= %d sec to time= %d sec.",run->i,time,time+run->burl);
                    time=time+run->burl;
                    run->burl=0;
                    run->compt=time;
                    run->status=2;
                    pl--;
                }
                else if(run->burl>tq)
                {
                    printf("\nProcess P%d running from time= %d sec to time= %d sec.",run->i,time,time+tq);
                    time=time+tq;
                    run->burl=run->burl-tq;
                    run->compt=time;
                    if(start==NULL)
                    {
                        cn=new node;
                        cn->q=run;
                        cn->next=NULL;
                        last=cn;
                        start=cn;
                    }
                    else
                    {
                        cn=new node;
                        cn->q=run;
                        node *x;
                        x=start;
                        if((start->q->burl)>(cn->q->burl))
                        {
                            cn->next=start;
                            start=cn;
                        }
                        else
                        {
                            while(x->next!=NULL && x->next->q->burl < cn->q->burl)
                            {
                                x=x->next;
                            }
                            cn->next=x->next;
                            x->next=cn;
                        }
                    }
                }
            }
            run=NULL;
        }
    }

    int awt=0,att=0;
    for(int i=0;i<n;i++)
    {
        p[i].turnaroundt=((p[i].compt)-(p[i].arr));
        p[i].waitingt=((p[i].turnaroundt)-(p[i].burst));
        awt=awt+p[i].waitingt;
        att=att+p[i].turnaroundt;
    }
    awt=awt/n;
    att=att/n;
    printf("\n\n\nDetails after scheduling are :");
    printf("\n _______________________________________________________________________________________________");
    printf("\n|\tPROCESS\t\t|\tARRIVAL TIME\t|\tBURST TIME\t|\tWAITING TIME  \t|\tTURN AROUND TIME  \t|");
    printf("\n|_______________|___________________|_______________|___________________|_______________________|");
    for(int i=0;i<n;i++)
    {
        printf("\n|\t\tP%d\t\t|\t\t%d\t\t\t|\t\t%d\t\t|\t\t\t%d\t\t|\t\t\t%d\t\t\t|",p[i].i,p[i].arr,p[i].burst,p[i].waitingt,p[i].turnaroundt);
        printf("\n|_______________|___________________|_______________|___________________|_______________________|");
    }

    printf("\nAverage  waiting time = %d ",awt);
    printf("\nAverage Turn Around Time = %d \n",att);
}
