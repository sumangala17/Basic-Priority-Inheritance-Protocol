struct Jobstruct
{
	int release;
	int exec;
	int priority;
	int inherited_prio;

	int *start_resource;		/*start and end time needed for resource if job has cpu to itself */
	int *end_resource;

	int timerunning;

	_Bool *holdsResource;      /*is job holding resource i */
	
	int blocked;		/* blocked = resource the job is blocked for. -1 implies job not blocked */
	_Bool complete;

};

typedef struct Jobstruct Job; 

int n,m;  /* no of jobs and resources*/
int *R;
Job *job;		/* jobs */
int current_job;
int cur_time;
int ndp;
int jobs_complete;

extern int pickFirstJob();

extern void initialize();

extern void releaseResource(int res);

extern _Bool checkCurrentComplete();

extern _Bool requestResource(int r);

extern void scheduleNextJob();

extern void updateTimeUnit();

extern void nextDecisionPoint();
