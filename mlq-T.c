#include <stdio.h>
struct process
{
    
    int algo;
    char p_id[6];
    int a_t;
    int b_t;
    int c_t;
    int tat;
    int w_t;
    int s_t;
    int r_t;
};

// Algorithm Functions
void fcfs(struct process data[], int start , int end)
{
    int time = 0;
    for (int i = start; i < end; i++)
    {

        if (data[i].a_t <= time)
        {
            data[i].s_t = time;
            time += data[i].b_t;
        }
        else
        {
            time = data[i].a_t;

            data[i].s_t = time;
            time += data[i].b_t;
        }
        data[i].c_t = time;
        data[i].tat = data[i].c_t - data[i].a_t;
        data[i].w_t = data[i].tat - data[i].b_t;
        data[i].r_t = data[i].w_t;
    }
}

void sjf(struct process data[], int start , int end)
{
    int time = 0, completed = 0;
    int n = end - start ;
    int done[n];

    for (int i = 0; i < n; i++)
        done[i] = 0;

    while (completed < n)
    {
        int idx = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++)
        {
            if (data[start + i].a_t <= time && done[i] == 0)
            {
                if (data[start + i].b_t < min_bt)
                {
                    min_bt = data[start + i].b_t;
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            time++;
        }
        else
        {
            data[start + idx].s_t = time;
            time += data[start + idx].b_t;

            data[start + idx].c_t = time;
            data[start + idx].tat = data[start + idx].c_t - data[start + idx].a_t;
            data[start + idx].w_t = data[start + idx].tat - data[start + idx].b_t;

            done[idx] = 1;
            completed++;
        }
    }
}

void rr(struct process data[], int start , int end) {
    int time = 0, completed = 0;
    int n = end - start ;
    int done[n];
    int quantum = 2; // Time quantum

    for (int i = 0; i < n; i++)
        done[i] = 0;

    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = data[start + i].b_t;

    while (completed < n)
    {
        int executed = 0;

        for (int i = 0; i < n; i++)
        {
            if (data[start + i].a_t <= time && done[i] == 0)
            {
                if (rem_bt[i] > 0)
                {
                    executed = 1;

                    if (rem_bt[i] > quantum)
                    {
                        time += quantum;
                        rem_bt[i] -= quantum;
                    }
                    else
                    {
                        time += rem_bt[i];
                        data[start + i].s_t = time - rem_bt[i];
                        rem_bt[i] = 0;

                        done[i] = 1;
                    }
                }
            }
        }
    }
}

int main() {
    int Levels  ;
    int (*algo_out[3])(struct process *data ,int start , int end )={0,0,0} ;
    int total_proc = 0;
    printf("Enter number of Levels: \n");
    scanf("%d", &Levels);
    int n_proc[Levels];
    for(int i=0; i<Levels; i++) {
        
        int n;
        printf("Enter number of processes in Level %d: ", i+1);
        scanf("%d", &n);
        n_proc[i] = n;
    }
    printf("now further you have to give details for each process in each level start from level 1 to %d \n", Levels);
    for(int i=0; i<Levels; i++) {
        total_proc += n_proc[i];
    }
    // taking all process details
    struct process data[total_proc];
    int complete = 0;
    int algo_in[Levels];
    for(int i=0; i<Levels; i++) {
        
        printf("select algorithm for Level %d\n", i+1);
        printf("1. FCFS\n2. SJF\n3. Round Robin\n");
        scanf("%d", &algo_in[i]);
        for(int j = complete ; j < complete + n_proc[i]; j++) {
            printf("Enter details for process %d in Level %d\n", j - complete + 1, i + 1);
            printf("Process ID: ");    // Process ID input
            scanf("%s", data[j].p_id); 
            printf("Arrival Time: "); 
            scanf("%d", &data[j].a_t);
            printf("Burst Time: ");
            scanf("%d", &data[j].b_t);
            data[j].algo = algo_in[i]; // storing algorithm choice
        }
        complete += n_proc[i];

    }
    complete = 0;
    for (int i = 0 ; i <Levels ; i++)
   {
    int start = complete ;
    int end = complete + n_proc[i];
    algo_out[algo_in[i]](data , start , end ) ;}
    return 0; 
}