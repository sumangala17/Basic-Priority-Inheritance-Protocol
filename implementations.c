/* Implementations of all functions declared in headers.h */

#include "headers.h"
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>



int pickFirstJob()
{
	int j, firstJob = 0;
	for(j=0; j<n; j++)					
		if(job[j].release < job[firstJob].release)
			firstJob = j;
	return firstJob;
}


void initialize()
{
	int i,j;
	printf("Enter input\n");
	// printf("Enter the number of jobs and resources\t");
	scanf("%d", &n);
	scanf("%d", &m);
	
	job = (Job *)malloc(n * sizeof(Job));
	R = (int *)malloc(m * sizeof(int));	

	for(j=0;j<n;j++)
	{
		job[j].start_resource = (int *)malloc(m * sizeof(int));
		job[j].end_resource = (int *)malloc(m * sizeof(int));
		job[j].holdsResource = (_Bool *)malloc(m * sizeof(_Bool));

		job[j].timerunning = 0;
		job[j].blocked = -1;
		job[j].complete = false;
	}

	for(j=0;j<n;j++)
	{
		scanf("%d %d %d", &job[j].release, &job[j].exec, &job[j].priority);
		for(int i=0; i<m; i++){
			scanf("%d %d", &job[j].start_resource[i], &job[j].end_resource[i]);
			R[i] = -1;
		}
		job[j].inherited_prio = job[j].priority;
	}	

	jobs_complete = 0;
	cur_time = 0;
}


void releaseResource(int res) 	/*cur_job is releasing resource R*/
{
	printf("Job %d released resource %d\n", current_job + 1, res + 1);
	job[current_job].holdsResource[res] = false;
	R[res] = -1;
	int flag = 0;
	for(int i=0;i<m;i++)
		if(job[current_job].holdsResource[i])
			flag = 1;
	if(!flag)
		job[current_job].inherited_prio = job[current_job].priority;	/* back to original priority */
}


_Bool checkCurrentComplete()
{
	if(job[current_job].timerunning >= job[current_job].exec)
	{
		job[current_job].complete = true;
		
		for(int i=0;i<m;i++)
			if(job[current_job].holdsResource[i] == true)
				releaseResource(i);
		
		printf("Job %d completed!!\n", current_job+1);
		jobs_complete++;
		return true;
	}
	return false;
}

_Bool requestResource(int r)
{
	if(R[r] == -1)
	{
		R[r] = current_job;
		job[current_job].holdsResource[r] = true;
		printf("Job %d gets resource %d\n", current_job + 1, r+1);
		return true;
	}
	else if(R[r] == current_job){		/* already has resource r */
		job[current_job].holdsResource[r] = true;
		printf("Job %d gets resource %d\n", current_job + 1, r+1);
		return true;
	}
	else
	{
		printf("Job %d blocked due to unavailability of resource %d\n",current_job+1, r+1);
		/* the current job will be blocked */
		job[current_job].blocked = r;		/* R = job holding the resource demanded */
		job[R[r]].inherited_prio = job[current_job].inherited_prio;		/*implementing inheritance priority protocol*/
		printf("Job %d inherits priority %d\n", R[r]+1, job[current_job].inherited_prio );
		return false;
	}
}


void nextDecisionPoint()
{
	ndp = job[current_job].exec - job[current_job].timerunning + cur_time; /* end of current job */
	int s,e,i,j,rel;
	for(j=0; j<n; j++)		/* case 1: arrival of new job */
	{
		rel = job[j].release;
		if(rel > cur_time && rel < ndp)
			ndp = rel;
	}

	/* current job requests or releases a resource */
	for(i=0; i<m; i++)
	{
		if(job[current_job].start_resource[i] == job[current_job].end_resource[i])
			continue;
		s = cur_time + job[current_job].start_resource[i] - job[current_job].timerunning;
		if(s > cur_time && s < ndp)
			ndp = s;
		e = cur_time + job[current_job].end_resource[i] - job[current_job].timerunning;
		if(e > cur_time && e < ndp )
			ndp = e;
	}
	printf("ndp at end of fn is %d\n",ndp );

}


void scheduleNextJob()
{

	int r;
	printf("schedule next function\n");
	int newjob = current_job;
	for(int j=0; j<n; j++)
	{
		if(job[j].complete){
			job[j].inherited_prio = 9; 
			continue;
		}
		r = job[j].blocked;		/* blocked status: -1 for not blocked; resource number if blocked */
		if(job[j].release <= cur_time && job[j].inherited_prio <= job[newjob].inherited_prio )
			if(r == -1 || R[r] == -1)
				newjob = j;
	}

	r = job[newjob].blocked;
	if(r == -1)		/* job is not blocked */
	{
		current_job = newjob;
	}

	else if(R[r] == -1)		/* the resource has already been released by previous jobs and is now free */
	{
		current_job = newjob;
		job[current_job].blocked = -1;
		R[r] = current_job;		/* since this job needs the resource and was earlier blocked bcz of it */
	}
	nextDecisionPoint();
	job[current_job].timerunning += (ndp - cur_time);
	cur_time = ndp;
}


void updateTimeUnit()
{

	if(checkCurrentComplete()){
		scheduleNextJob();
		return;
	}

	for(int i=0;i<m;i++)
	{
		if(job[current_job].timerunning == job[current_job].start_resource[i])
		{
			if(!requestResource(i))
			{
				scheduleNextJob();
				return;
			}
		}
		if(job[current_job].timerunning == job[current_job].end_resource[i])
			releaseResource(i);
	}
	scheduleNextJob();
}