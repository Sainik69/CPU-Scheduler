#include <stdio.h>
#include <stdlib.h>


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

int compare(const void *a, const void *b)
{
    struct process *p1 = (struct process *)a;
    struct process *p2 = (struct process *)b;
    return p1->a_t - p2->a_t;
}






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

        if (!executed)
            time++;
    }
}

// algo of SRJF
void sjrf(struct process data[], int n)
{
    int time = 0, completed = 0;
    int rem_bt[n];
    int started[n];

    // gantt chart storage (reference style)
    int g_s[100], g_e[100], g_p[100];
    int g_count = 0;

    for (int i = 0; i < n; i++)
    {
        rem_bt[i] = data[i].b_t;
        started[i] = 0;
    }

    while (completed < n)
    {
        int idx = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++)
        {
            if (data[i].a_t <= time && rem_bt[i] > 0)
            {
                if (rem_bt[i] < min_bt)
                {
                    min_bt = rem_bt[i];
                    idx = i;
                }
            }
        }

        // CPU idle
        if (idx == -1)
        {
            time++;
            continue;
        }

        // start time (only once)
        if (started[idx] == 0)
        {
            data[idx].s_t = time;
            started[idx] = 1;
        }

        // record gantt start
        if (g_count == 0 || g_p[g_count - 1] != idx)
        {
            g_s[g_count] = time;
            g_p[g_count] = idx;
            g_count++;
        }

        // execute for 1 unit
        rem_bt[idx]--;
        time++;

        // record gantt end
        g_e[g_count - 1] = time;

        // completion
        if (rem_bt[idx] == 0)
        {
            data[idx].c_t = time;
            data[idx].tat = data[idx].c_t - data[idx].a_t;
            data[idx].w_t = data[idx].tat - data[idx].b_t;
            data[idx].r_t = data[idx].s_t - data[idx].a_t;
            completed++;
        }
    }

    // Gantt Chart
    printf("\nGANTT Chart -:\t");
    for (int i = 0; i < g_count; i++)
    {
        printf("%d|%s|%d| ",
               g_s[i],
               data[g_p[i]].p_id,
               g_e[i]);
    }
}

// algo of LJF
void ljf(struct process data[], int n)
{
    int time = 0, completed = 0;
    int done[n];

    for (int i = 0; i < n; i++)
        done[i] = 0;

    while (completed < n)
    {
        int idx = -1;
        int max_bt = -1;

        for (int i = 0; i < n; i++)
        {
            if (data[i].a_t <= time && done[i] == 0)
            {
                if (data[i].b_t > max_bt)
                {
                    max_bt = data[i].b_t;
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
            data[idx].s_t = time;
            time += data[idx].b_t;

            data[idx].c_t = time;
            data[idx].tat = data[idx].c_t - data[idx].a_t;
            data[idx].w_t = data[idx].tat - data[idx].b_t;

            done[idx] = 1;
            completed++;
        }
    }
}

int main()
{
    printf("Team Name: Electrocube \n ");
    printf("Team Members\tRegistration No.\n");
    printf("Himaneesh Singh\t 20254072 (Team Leader)\n");
    printf("Nikhil Saini\t 20254099 \n");
    printf("Srivatsan Karthikeyan\t 20254507 \n");
    printf("Shambhav Chaudhary\t 20254141 \n");

    int n;
    printf("Number of Processes: ");
    scanf("%d", &n);
    struct process data[n];
    // Taking Inputs from User
    for (int i = 0; i < n; i++)
    {

        printf("Process ID :\t ");
        scanf("%6s", data[i].p_id);
        printf("Arrival Time: \t ");
        scanf("%d", &data[i].a_t);
        printf("Burst Time: \t ");
        scanf("%d", &data[i].b_t);
    }
    // Sorting based on Arrival Time
    qsort(data, n, sizeof(struct process), compare);
    // Asking which Algorithm to Run
    void (*algo[])(struct process[], int) = {fcfs, sjf, round_robin, ljf, sjrf};
    int choice; // 0 = FCFS, 1 = SJF, 2 = RR, LJF  = 3
    printf(" 0 = FCFS, 1 = SJF, 2 = RR, 3 = LJF, 4 = SJRF:\n");
    scanf("%d", &choice);

    // Run selected Algorithm
    algo[choice](data, n);

    // Print Gantt Chart
    printf("GANTT Chart -: \t");
    for (int i = 0; i < n; i++)
    {
        printf("%d|%s|%d|", data[i].s_t, data[i].p_id, data[i].c_t);
    }

    // Print Table of Matrices
    printf("\np_id\ta_t\tb_t\tc_t\ttat\tw_t\tr_t\n");
    for (int i = 0; i < n; i++)
    {
        printf("%6s\t %d \t %d \t  %d \t %d \t %d \t %d\n", data[i].p_id, data[i].a_t, data[i].b_t, data[i].c_t, data[i].tat, data[i].w_t, data[i].r_t);
    }

    return 0;
}