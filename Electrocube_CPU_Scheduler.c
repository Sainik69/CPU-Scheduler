#include <stdio.h>

struct process
{
    char p_id[6];
    int a_t;
    int b_t;
    int c_t;
    int tat;
    int w_t;
    int s_t;
    int r_t;
};
// algo of FCFS
void fcfs(struct process data[], int n)
{
    int time = 0;
    for (int i = 0; i < n; i++)
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
// algo of sjf
void sjf(struct process data[], int n)
{
    int time = 0, completed = 0;
    int done[n];

    for (int i = 0; i < n; i++)
        done[i] = 0;

    while (completed < n)
    {
        int idx = -1;
        int min_bt = 9999;

        // Select shortest job among arrived processes
        for (int i = 0; i < n; i++)
        {
            if (data[i].a_t <= time && done[i] == 0)
            {
                if (data[i].b_t < min_bt)
                {
                    min_bt = data[i].b_t;
                    idx = i;
                }
            }
        }

        // If no process has arrived
        if (idx == -1)
        {
            time++;
        }
        else
        {
            data[idx].s_t = time;
            time += data[idx].b_t;

            data[idx].c_t = time;
            data[idx].tat = data[idx].c_t - data[idx].a_t;
            data[idx].w_t = data[idx].tat - data[idx].b_t;
            data[idx].r_t = data[idx].w_t;

            done[idx] = 1;
            completed++;
        }
    }
}
// algo of round robin
void round_robin(struct process data[], int n)
{
    int tq = 2;
    int time = 0, completed = 0;
    int rem_bt[n];

    // Initialize remaining burst time
    for (int i = 0; i < n; i++)
        rem_bt[i] = data[i].b_t;

    while (completed < n)
    {
        int executed = 0;

        for (int i = 0; i < n; i++)
        {
            if (data[i].a_t <= time && rem_bt[i] > 0)
            {
                executed = 1;

                // Set start time only once
                if (rem_bt[i] == data[i].b_t)
                    data[i].s_t = time;

                if (rem_bt[i] > tq)
                {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else
                {
                    time += rem_bt[i];
                    rem_bt[i] = 0;

                    data[i].c_t = time;
                    data[i].tat = data[i].c_t - data[i].a_t;
                    data[i].w_t = data[i].tat - data[i].b_t;
                    data[i].r_t = data[i].s_t - data[i].a_t;

                    completed++;
                }
            }
        }

        // CPU idle case
        if (!executed)
            time++;
    }
}

int main()
{
    printf("team name_-: Electro cube \n ");
    printf("team members\tregistration_no.\n");
    printf("himaneesh singh\t 20254072 (leader)\n");
    printf("Nikhil saini\t 20254099 \n");
    printf("Srivatsan karthikeyan\t 20254507 \n");
    printf("Shambhav chaudary\t 20254141 \n");
     


    int n;
    printf("Number of Processes: ");
    scanf("%d", &n);
    struct process data[n];
    // taking inputs from user
    for (int i = 0; i < n; i++)
    {

        printf("Process ID :\t ");
        scanf("%6s", data[i].p_id);
        printf("Arrival Time: \t ");
        scanf("%d", &data[i].a_t);
        printf("Burst Time: \t ");
        scanf("%d", &data[i].b_t);
    }
    // asking algo to run
    void (*algo[])(struct process[], int) = {fcfs, sjf, round_robin};
    int choice; // 0 = FCFS, 1 = SJF, 2 = RR
    printf(" 0 = FCFS, 1 = SJF, 2 = RR -:\n");
    scanf("%d", &choice);

    // run selected algorithm
    algo[choice](data, n);
    // print gantt chart
    printf("GANTT Chart -: \t");
    for (int i = 0; i < n; i++)
    {
        printf("%d|%s|%d|", data[i].s_t, data[i].p_id, data[i].c_t);
    }
    // print table of metrices
    printf("\np_id\ta_t\tb_t\tc_t\ttat\tw_t\tr_t\n");
    for (int i = 0; i < n; i++)
    {
        printf("%6s\t %d \t %d \t  %d \t %d \t %d \t %d\n", data[i].p_id, data[i].a_t, data[i].b_t, data[i].c_t, data[i].tat, data[i].w_t, data[i].r_t);
    }
    return 0;
}
