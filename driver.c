#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include "headers.h"



int main(int argc, char const *argv[])
{
	initialize();
	current_job = pickFirstJob();
	
	printf("Schedule of Jobs:\n\n");
	while(jobs_complete <= n)
	{
		printf("_____________________________\n");
		printf("current time is %d\n",cur_time );		
		
		printf("\nTime: %d 	Executing job %d\n", cur_time, current_job+1);

		printf("Job %d holds resource 1\n", R[0]+1);
		printf("Job %d holds resource 2\n", R[1]+1);
		
		updateTimeUnit();
	}

	return 0;
}


// FILE *fp;
	// fp = fopen("input file","r");

	// char ch= fgetc(fp);
	// n = atoi(ch);
	// while(ch == ' ' || ch == '\t')
	// 	ch = fgetc(fp);
	// m = atoi(ch);

	// for(int i=0; i<n; i++)
	// {
	// 	printf("running\n");
	// 	while(ch == ' ' || ch == '\t')
	// 		ch = fgetc(fp);
	// 	job[i].release = atoi(ch);
	// 	while(ch == ' ' || ch == '\t')
	// 		ch = fgetc(fp);
	// 	job[i].exec = atoi(ch);
	// 	while(ch == ' ' || ch == '\t')
	// 		ch = fgetc(fp);
	// 	job[i].priority = atoi(ch);
	// 	for(int j=0; j<m; j++){
	// 		while(ch == ' ' || ch == '\t')
	// 			ch = fgetc(fp);
	// 		job[i].start_resource[j] = atoi(ch);
	// 		while(ch != ' '){
	// 			job[i].start_resource[j] = job[i].start_resource[j] * 10 + atoi(ch);
	// 			ch = fgetc(fp);
	// 		}
	// 		while(ch == ' ' || ch == '\t')
	// 			ch = fgetc(fp);
	// 		job[i].end_resource[j] = atoi(ch);
	// 		while(ch != ' '){
	// 			job[i].end_resource[j] = job[i].end_resource[j] * 10 + atoi(ch);
	// 			ch = fgetc(fp);
	// 		}
	// 	}
	// }