#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//global variable declaration

int n,i,WTsum,TATsum;
float TATavg,WTavg,wavg=0.0,tavg=0.0,tsum=0.0,wsum=0.0;

void swap(int *a,int *b)
{
	int t;
	t=*b;
	*b=*a;
	*a=t;
}

//structure to define process with arrival,burst,waiting,turnaround,remaining,completion time as attributes fow MLQ

struct process 
{
    int p;
    int AT,BT,WT,TAT,RT,CT;
}Q1[10],Q2[10]; 		//Two queues

int n;
void sortByArrival() 		//sort attribute arrays of structure
{
struct process temp;
int i,j;
for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
            {
                if(Q1[i].AT>Q1[j].AT)
                    {
                          swap(&Q1[i].AT,&Q1[j].AT);
                    }
            }
    }
}

//function for fcfs scheduling

int fcfs(int n)
{ 
TATsum,WTsum=0;		//initialization
TATavg,WTavg=0.0;	//initialization
printf("\t\t\tFirst Come First Serve Scheduling Algorithm\n");
int BT[n],AT[n],DUR[n],ET[n],TAT[n],WT[n];
for(i=0;i<n;i++) 	//taking input
{
	printf("Enter The Duration of Process Number %d \n",i+1);
	scanf("%d",&DUR[i]);
	printf("Enter Arrival Time of Process Number %d \n",i+1);
	scanf("%d",&AT[i]);
}
BT[0]=AT[0]; //The first process executes as soon as arriving, AT is same asBT
printf("\n Begining Time: \n");
printf("\t%d ",BT[0]);
for (i=1;i<n;i++) //calculating begining time
{  
        BT[i]=BT[i-1]+DUR[i-1];
	printf("\t%d ",BT[i]);
}
printf("\n Ending Time: \n");
for(i=0;i<n;i++) //calculatingendingtime
{
	ET[i]=BT[i]+DUR[i];
	printf("\t%d ",ET[i]);
}
printf("\n Turn Around Time: \n");
for(i=0;i<n;i++) //calculating turnaroundtime.
{
	TAT[i]=ET[i]-AT[i];
	printf("\t%d ",TAT[i]);
	TATsum=TATsum+TAT[i];
}
printf("\n Waiting Time: \n");
for(i=0;i<n;i++) //calculating waiting time
{
	WT[i]=TAT[i]-DUR[i];
	printf("\t%d ",WT[i]);
	WTsum=WTsum+WT[i];
}
printf("\nTATSum=%d\nWTSum=%d\n",TATsum,WTsum);	//printing results
TATavg=(float)TATsum/(float)n;
WTavg=(float)WTsum/(float)n;
printf("\nAverage Waiting Time is  %f\n",WTavg);
printf("\nAverage TurnAround Time is  %f\n",TATavg);
}

//sjf scheduling function

int sjf(int n) 
{
printf("\t\t\tShortest Job First Scheduling Algorithm\n");
int p[n],min,k=1,btime=0;
int bt[n],temp,j,arr[n],wait[n],turn[n],ta=0,sum=0;
for(int i=0;i<n;i++) //taking input
{ 
	p[i]=i+1;
	printf("Enter Duration of Process Number %d \n",i+1);
	scanf("%d",&bt[i]);
	printf("Enter Arrival Time of Process Number %d \n",i+1);
	scanf("%d",&arr[i]);
}
//sorting 3 arrays p,arr,bt
for(i=0;i<n;i++)
{
	for(j=0;j<n;j++)
	{
		if(arr[i]<arr[j])
		{
			swap(&p[i],&p[j]);
			swap(&arr[i],&arr[j]);
			swap(&bt[i],&bt[j]);
		}
	}
}
//sorting p,arr,bt according to the shortest job
for(j=0;j<n;j++)
{
	btime=btime+bt[j];
	min=bt[k];
	for(i=k;i<n;i++)
	{
		if (btime>=arr[i] && bt[i]<min)
		{
			swap(&p[i],&p[k]);
			swap(&arr[i],&arr[k]);
			swap(&bt[i],&bt[k]);
		}
	}
k++;
}
wait[0]=0; //calculating waiting time
for(i=1;i<n;i++)
{
	sum=sum+bt[i-1];
	wait[i]=sum-arr[i];
	wsum=wsum+wait[i];
}
wavg=(wsum/n);
for(i=0;i<n;i++) //calculating turn around time
{
	ta=ta+bt[i];
	turn[i]=ta-arr[i];
	tsum=tsum+turn[i];
}
tavg=(tsum/n);
printf("\n"); //printing results
printf("\nProcess\t\t Duration\tArrival\t\tWaiting\t\tTurnAround\n" );
for(i=0;i<n;i++)
	printf("\n Process%d\t %d\t\t %d\t\t %d\t\t%d",p[i],bt[i],arr[i],wait[i],turn[i]);
printf("\n\nAverage Waiting Time : %f",wavg);
printf("\nAverage TurnAround Time : %f",tavg);
return 0;
}

//function for srtf scheduling algorithm

int srtf(int n)
{
printf("\t\t\tShortest Remaining Time First Scheduling Algorithm\n");
int ari[10], bur[10], total = 0, i, j, small, temp, procs[100], k, waiting[10], finish[10];
for(i=0;i<n;i++) //inputs
{
	printf("Enter Duration of Process Number %d \n",i+1);
	scanf("%d",&bur[i]);
	printf("Enter Arrival Time of Process Number %d \n",i+1);
	scanf("%d",&ari[i]);
	waiting[i]=0;
        total+=bur[i];
}
							//sorting arrival time and burst time
for(i=0;i<n;i++)
{
	for(j=i+1;j<n;j++)
	{
	        if(ari[i]>ari[j])
	        { 			
		swap(&ari[i],&ari[j]);			//swap arrival time				
		swap(&bur[i],&bur[j]);			//swap burst time
       		}
	}
} 
for(i=0;i<total;i++)					//calculating and selecting smallest remaining time and move to finish queue
{
	small=3200;
	for(j=0;j<n;j++)
	{
		if ((bur[j] != 0) && (ari[j] <= i) && (bur[j] < small))  
        	{
            		small=bur[j];
           		k=j;
        	}
	}
        bur[k]--;
        procs[i]=k;
}
k=0;
for(i=0;i<total;i++) //update finish queue and waiting queue
{
	for(j=0;j<n;j++)
        {
		if(procs[i]==j)
          	{
          	  finish[j]=i;
          	  waiting[j]++;
          	}
        }
}
//printing results
for(i=0;i<n;i++)
{
	printf("\n Process %d \t End Time: %d TAT: %d WT: %d\n",i+1,finish[i]+1,(finish[i]-ari[i])+1,(((finish[i]+1)-waiting[i])-ari[i]));  
	wavg=wavg+(((finish[i]+1)-waiting[i])-ari[i]);      
	tavg=tavg+((finish[i]-ari[i])+1);
}
printf("\nAverage WT\t:\t%f\nAverage TAT\t:\t%f\n", (wavg/n), (tavg/n));    
return 0;
}

//function for priority based sorting

int priority(int n)
{
printf("\t\t\tPriority Based Scheduling Algorithm\n");
int p[n],min,k=1,burst=0,pri[n];
int bt[n],temp,temp1,j,at[n],wt[n],tt[n],ta=0,sum=0;
for(int i=0;i<n;i++)                                                                           //input
{
	p[i]=i+1;
	printf("Enter Duration of Process Number %d \n",i+1);
	scanf("%d",&bt[i]);
	printf("Enter Arrival of Process Number %d \n",i+1);
	scanf("%d",&at[i]);
	printf("Enter Priority of Process Number %d \n",i+1);
	scanf("%d",&pri[i]);
}
//sort arrays: processes,arrival time and burst time
for(i=0;i<n;i++)
{
	for(j=0;j<n;j++)
	{
		if(at[i]<at[j])
		{
		swap(&p[i],&p[j]);
		swap(&at[i],&at[j]);
		swap(&bt[i],&bt[j]);
		}
	}
}
for(j=0;j<n;j++) //calculate the running queue and sort arrays: process,arrival time,burst time, priority
{
	burst=burst+bt[j];
	min=bt[k];
	for(i=k;i<n;i++)
	{
		min=pri[k];
		if (burst>=at[i])
		{
			if(pri[i]<min)
			{
				swap(&p[i],&p[k]);
				swap(&at[i],&at[k]);
				swap(&bt[i],&bt[k]);
				swap(&pri[i],&pri[k]);
			}
		}
	}
k++;
}
wt[0]=0;
for(i=1;i<n;i++) //calculate waiting time
{
	sum=sum+bt[i-1];
	wt[i]=sum-at[i];
}
for(i=0;i<n;i++) //calculate avg waiting time
	wsum=wsum+wt[i];
wavg=wsum/n;
for(i=0;i<n;i++) //calculate turnaround time and average turn around time
{
ta=ta+bt[i];
tt[i]=ta-at[i];
}
for(i=0;i<n;i++)
	tsum=tsum+tt[i];
tavg=tsum/n;
printf("\n Process \t Arrival Time \t Duration \t Waiting Time \t TurnAround time\n"); //print results
for(i=0;i<n;i++)
{
	printf(" %d",i+1);
	printf("\t \t%d",at[i]);
	printf("\t \t%d",bt[i]);
	printf("\t \t%d",wt[i]);
	printf("\t \t%d",tt[i]);
	printf("\n");
}
printf("\nAverage Waiting Time: %d ms",(int)wavg);
printf("\nAverage TurnAround Time: %d ms" ,(int)tavg);
}

//function for roundrobin sorting

int roundrobin(int n)
{
printf("\t\t\tRound Robin Scheduling Algorithm\n");
int wait_time=0,turnaround_time=0,at[n],bt[n],rt[n],Pri[n],remain,tq,time,count,flag=0;
for(i=0;i<n;i++) //input
{
	printf("Enter Duration of Process Number %d \n",i+1);
	scanf("%d",&bt[i]);
	rt[i]=bt[i];
	printf("Enter Arrival Time of Process Number %d \n",i+1);
	scanf("%d",&at[i]);
	printf("Enter Priority of Process Number %d \n",i+1);
	scanf("%d",&Pri[i]);
}
remain=n;
printf("\nEnter Time Quantum Value:\t\n");
scanf("%d",&tq);
printf("\nProcess\t\tTurnAround Time\t\tWaiting Time\n");
for(time=0,count=0;remain!=0;)
	{
	if(rt[count]<=tq && rt[count]>0) //calculate remaining time
	{
        	time+=rt[count];
      		rt[count]=0;
      		flag=1;
    	}
    	else if(rt[count]>0)
    	{
    		rt[count]-=tq;
      		time+=tq;
    	}
    	if(rt[count]==0 && flag==1) //calculate waiting time, turn around time and print results
    	{
      		remain--;
      		printf("\nProcess %d\t\t%d\t \t%d\n",count+1,time-at[count],time-at[count]-bt[count]);
      		wait_time+=time-at[count]-bt[count];
      		turnaround_time+=time-at[count];
      		flag=0;
    	}
    	if(count==n-1)
      		count=0;
    	else if(at[count+1]<=time)
      		count++;
    	else
      	count=0;
} 
printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n);		//calculate and print average waiting time and turnaround time
printf("\nAverage TurnAround Time = %f\n",turnaround_time*1.0/n);
return 0;
}

//function for multi level queueing

int mlq(int n)
{
int count,j,remain,tq;
int i,k=0,r=0,time=0,tq1=5,tq2=8,flag=0,q1ws=0,q2ws=0,q1ts=0,q2ts=0;
int c;
for(i=0,c=0;i<n;i++,c++)
{
        Q1[i].p=c;   //assign process numbers
        printf("\nEnter The Arrival Time of Process %d: ",Q1[i].p);
        scanf("%d",&Q1[i].AT);
	printf("\nEnter the Duration of Process %d: ",Q1[i].p);
        scanf("%d",&Q1[i].BT);
        Q1[i].RT=Q1[i].BT; //save burst time in remaining time for each process
}
sortByArrival();
time=Q1[0].AT;
printf("Process in first queue");
printf("\nProcess\t\tDuration\tWT\t\tTAT\t\t");
for(i=0;i<n;i++)
{
	if(Q1[i].RT<=tq1)
  	{
	        time+=Q1[i].RT;
       		Q1[i].RT=0;
       		Q1[i].WT=time-Q1[i].AT-Q1[i].BT; //waiting time in queue1
       		Q1[i].TAT=time-Q1[i].AT;
       		printf("\n%d\t\t%d\t\t%d\t\t%d",Q1[i].p,Q1[i].BT,Q1[i].WT,Q1[i].TAT);
		q1ws+=Q1[i].WT;
		q1ts+=Q1[i].TAT;
	}
  	else //process moves to queue 2
  	{
      		Q2[k].WT=time;
      		time+=tq1;
      		Q1[i].RT-=tq1;
      		Q2[k].BT=Q1[i].RT;
      		Q2[k].RT=Q2[k].BT;
      		Q2[k].p=Q1[i].p;
      		k=k+1;
      		flag=1;
   	}
}
if(flag==1)
{
	printf("\nProcess in second queue");
	printf("\nProcess\t\tDuration\tWT\t\tTAT\t\t");
}
for(i=0;i<k;i++)
{
    	if(Q2[i].RT<=tq2)
    	{
       		time+=Q2[i].RT; //waiting time
       		Q2[i].RT=0;
       		Q2[i].WT=time-tq1-Q2[i].BT;
       		Q2[i].TAT=time-Q2[i].AT; //time to execute the process
       		printf("\n%d\t\t%d\t\t%d\t\t%d",Q2[i].p,Q2[i].BT,Q2[i].WT,Q2[i].TAT);
		q2ws+=Q2[i].WT;
		q2ts+=Q2[i].TAT;
    	}
    	else //process moves to queue 3
    	{
    		time+=tq2;
    	  	Q2[i].RT-=tq2;
    	  	r=r+1;
    	}
}
//printing results
printf("\nQ1 Waiting time:%d\n",q1ws);
printf("\nQ2 Waiting time:%d\n",q2ws);
printf("\nTotal Waiting time:%d\n",(q1ws+q2ws));
printf("\nQ1 Turn Around time:%d\n",q1ts);
printf("\nQ2 Turn Around time:%d\n",q2ts);
printf("\nTotal TurnAround time:%d\n",(q1ts+q2ts));

printf("\nAverage Waiting Time= %d\n",(q1ws+q2ws)/n);
printf("\nAverage TurnAround Time = %d\n",(q1ts+q2ts)/n);
}

//main function
int main()
{
int choice;
printf("\t\t  --PROCESS SCHEDULING ALGORITHMS IMPLEMENTATION--  \t\t");
label:printf("\n\nEnter the Choice: \n 1.FCFS \n 2.SJF \n 3.SRTF \n 4.Priority Based \n 5.Round Robin \n 6.Multi-Level Queue \n 7.Exit \n\n");
scanf("%d",&choice);	//input choice
switch(choice) //call algorithm function based on choice
{
	case 1:
	{
		printf("\nEnter The Number of Processes \n");
		scanf("%d",&n);
		fcfs(n);
		goto label;
	}
	case 2:
	{
		printf("\nEnter The Number of Processes \n");
		scanf("%d",&n);
		sjf(n);
		goto label;
	}
	case 3:
	{
		printf("\nEnter The Number of Processes \n");
		scanf("%d",&n);
		srtf(n);
		goto label;
	}
	case 4:
	{
		printf("\nEnter The Number of Processes \n");
		scanf("%d",&n);
		priority(n);
		goto label;
	}
	case 5:
	{
		printf("\nEnter The Number of Processes \n");
		scanf("%d",&n);
		roundrobin(n);
		goto label;
	}
	case 6:
	{
		mlq(n);
		printf("\nEnter The Number of Processes \n");
		scanf("%d",&n);
		goto label;
	}
	case 7: 
		exit;
}
return 0;
}
/*Operating System Assignment by Vinay Karthik M B*/