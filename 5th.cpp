#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


struct process
{
	char pid;
	int arrival_time,burst_time,waiting_time,turnaround_time,remaining_time;
	bool complete;
}p[10];

int n;
int queue[100];  									
int front=-1,rear=-1;

void sortByArrival()
{
	struct process temp;
	int i,j;
	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++)
		{
			if(p[i].arrival_time>p[j].arrival_time)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}	
}

int dequeue()
{
	if(front==-1)
	printf("\nUnderflow\n");
	int temp=queue[front];
	if(front==rear)
	front=rear=-1;
	else
	front++;
	return temp;
}

void enqueue(int i)
{
	if(rear==100)
	printf("\nOverflow\n");
	rear++;
	queue[rear]=i;
	if(front==-1)
	front=0;
}

bool search(int n)
{
	for(int i=front;n<=rear;n++)
	{
		if(queue[i]==n)
		return true;
	}
	return false;
}

int main()
{
	int i,j,time=0,total_time=0,t;
	char c;
    float avg_wait=0, avg_turnaround=0;
 	printf("\nEnter no of processes: ");
 	scanf("%d",&n);
 	for(i=0,c='A';i<n;i++,c++)
 	{
		p[i].pid=c;
 		printf("\nEnter the arrival time and burst time of process %c: ",p[i].pid);
 		scanf("%d%d",&p[i].arrival_time,&p[i].burst_time);
 		p[i].remaining_time=p[i].burst_time;
 		p[i].complete=false;
 		total_time+=p[i].burst_time;
 
	}

	printf("\nEnter the time quantum: ");
	scanf("%d",&t);

	sortByArrival();
	
	enqueue(0);
	         				 // enqueue the first process
	printf("\nProcess execution order: ");
	for(time=p[0].arrival_time;time<total_time;)       // run until the total burst time reached
	{  
		i=dequeue();
		if(p[i].remaining_time<=t)
		{                          /* for processes having remaining time with less than                                             or  equal  to time quantum  */
                       
			time+=p[i].remaining_time;
			p[i].remaining_time=0;
			p[i].complete=true;          
    		printf(" %c ",p[i].pid);
            p[i].waiting_time=time-p[i].arrival_time-p[i].burst_time;
            p[i].turnaround_time=time-p[i].arrival_time;       
            
            for(j=0;j<n;j++)                	/*enqueue the processes which have come                                         while scheduling */
            {
            	if(p[j].arrival_time<=time && p[j].complete!=true&& search(j)!=true)
            	{
            		enqueue(j);
            
          		}
           	}
        }
    	else               			
    	{	
    		time+=t;
    		p[i].remaining_time-=t;
    		printf(" %c ",p[i].pid);
    		for(j=0;j<n;j++)    	                                    
            {
            	if(p[j].arrival_time<=time && p[j].complete!=true&&i!=j&& search(j)!=true)
             	{
            		enqueue(j);
            
            	}
           	}
           	enqueue(i);  				
           
    	}

    
    
	}

	printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time");	
	
	for(i=0;i<n;i++)
	{
		avg_wait += p[i].waiting_time;
		avg_turnaround += p[i].turnaround_time;
		printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].waiting_time,p[i].turnaround_time);
	}
	printf("\nAverage waiting time:%f\n",avg_wait/n);
	printf("\nAverage turn around time:%f\n",avg_turnaround/n);

}
