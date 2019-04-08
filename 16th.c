#include<stdio.h>
struct process
{
char name;
int at,bt,wt,tt,rt;
int completed;
}p[100];
int n;
int q[100];  //queue 
int front=-1,rear=-1;//initially
void enqueue(int i) // like push in stack
{
if(rear==100)
{
printf("overflow");
exit(0);
}
rear++;//increaments rear
q[rear]=i;// FIFO or LILO
if(front==-1)
{
front=0;
}
}

int dequeue()   //like pop in stack
{
if(front==-1)
{
printf("underflow");
exit(0);
}
int temp=q[front];
if(front==rear)
front=rear=-1;
else
{
front++;
}
return temp;
}
int isInQueue(int i)
{int k;
for(k=front;k<=rear;k++)
{
if(q[k]==i)
return 1;
}
return 0;

}
void sortByArrival()
{
struct process temp;
int i,j;
for(i=0;i<n-1;i++)
for(j=i+1;j<n;j++)
{
if(p[i].at>p[j].at)
{
temp=p[i];
p[i]=p[j];
p[j]=temp;
}
}
}

int main()
{
int i,j,time=0,sum_bt=0,tq;
char c;
float avgwt=0,avgtt=0;
printf("#################################Created By TASLIM:#####################\n");
printf("                  K17SM SECTION LPU. For more info contact at taslimarif600@gmail.com         ");
printf("\n\n####################################################################################################");
 printf("\n\nEnter no of processes:");
 scanf("%d",&n);
 for(i=0,c='A';i<n;i++,c++)
 {
 p[i].name=c;
 printf("\n\t#############   PROCESS %c   ################: ",p[i].name);
 printf("\n\nEnter Arrival Time:");
 scanf("%d",&p[i].at);
 printf("\nEnter Burst Time:");
 scanf("%d",&p[i].bt);
 p[i].rt=p[i].bt;
 p[i].completed=0;
 sum_bt+=p[i].bt;
 
}
printf("\n####################################################################################################");
printf("\nEnter TIME QUANTUM:");
scanf("%d",&tq);

sortByArrival();
enqueue(0);          // enqueue the first process
printf("\t\t\nProcess execution order: ");

for(time=p[0].at;time<sum_bt;) // run until the total burst time reached
{   i=dequeue();

if(p[i].rt<=tq)
{                          /* for processes having remaining time with less than                                             or  equal  to time quantum  */
                       
time+=p[i].rt;
p[i].rt=0;
p[i].completed=1;          
    printf(" %c ",p[i].name);
            p[i].wt=time-p[i].at-p[i].bt;
            p[i].tt=time-p[i].at;       
            for(j=0;j<n;j++)                /*enqueue the processes which have come                                         while scheduling */
            {
            if(p[j].at<=time && p[j].completed!=1&& isInQueue(j)!=1)
            {
            enqueue(j);
            
            }
           }
        }
    else               // more than time quantum
    {
    time+=tq;
    p[i].rt-=tq;
    printf(" %c ",p[i].name);
    for(j=0;j<n;j++)    //first enqueue the processes which have come while scheduling 
            {
            if(p[j].at<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
             {
            enqueue(j);
            
            }
           }
           enqueue(i);   // then enqueue the uncompleted process
           
    }

    
    
}

printf("\n\nPROCESS\t    ARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME");
for(i=0;i<n;i++)
{avgwt+=p[i].wt;
 avgtt+=p[i].tt;
printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d",p[i].name,p[i].at,p[i].bt,p[i].wt,p[i].tt);
}
printf("\nAverage waiting time:%f",avgwt/n);
printf("\nAverage Turnaround time:%f",avgtt/n);
return 0;
}
