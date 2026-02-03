#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process
{
    int level;
    int completed;
    char p_id[6];
    int a_t;
    int b_t;
    int c_t;
    int r_t;
    int tat; 
    int w_t; 
};

int compare(const void *a, const void *b)
{
    struct process *p1 = (struct process *)a;
    struct process *p2 = (struct process *)b;
    return p1->a_t - p2->a_t;
}
int available(int s, int e, int level, struct process data[], int time)
{
    for (int i = s; i < e; i++)
    {
        if (!data[i].completed && data[i].level == level && data[i].a_t <= time && data[i].r_t > 0)
            return i; // return actual index
    }
    return -1; // no ready process
}

int main()
{
    

    int Levels = 3;

    int total_proc = 0;

    int n_proc[Levels];
    for (int i = 0; i < Levels; i++)
    {

        int n;
        printf("Enter number of processes in Level %d: ", i + 1);
        scanf("%d", &n);
        n_proc[i] = n;
    }
    printf("now further you have to give details for each process in each level start from level 1 to %d \n", Levels);
    for (int i = 0; i < Levels; i++)
    {
        total_proc += n_proc[i];
    }
    // taking all process details
    struct process data[total_proc];

    int level_start[Levels];
    int level_end[Levels];

    level_start[0] = 0;
    for (int i = 0; i < Levels; i++)
    {
        if (i > 0)
            level_start[i] = level_end[i - 1];

        level_end[i] = level_start[i] + n_proc[i];
    }
    for (int i = 0; i < Levels; i++)
    {

        for (int j = level_start[i]; j < level_end[i]; j++)
        {
            printf("Enter details for process %d in Level %d\n", j - level_start[i] + 1, i + 1);
            printf("Process ID: "); // Process ID input
            scanf("%s", data[j].p_id);
            printf("Arrival Time: ");
            scanf("%d", &data[j].a_t);
            printf("Burst Time: ");
            scanf("%d", &data[j].b_t);
            data[j].r_t = data[j].b_t;
            data[j].level = i;
            data[j].completed = 0;
        }
    }
    // calculate level start and end indices

    // sort processes based on arrival time using qsort of each queue
    for (int i = 0; i < Levels; i++)
    {
        qsort(&data[level_start[i]], level_end[i] - level_start[i], sizeof(struct process), compare);
    }
    int complete = 0;
    int time = 0;
    char gantt[1000][6]; // store executed process ID per unit time
    int gantt_time = 0;

    while (complete < total_proc)
    {
        int idx = -1;

        // Level 0
        idx = available(level_start[0], level_end[0], 0, data, time);
        if (idx != -1)
        {
            data[idx].r_t--;
            strcpy(gantt[gantt_time], data[idx].p_id);
            gantt_time++;
            time++;

            if (data[idx].r_t == 0)
            {
                data[idx].completed = 1;
                data[idx].c_t = time;
                complete++;
            }
            continue;
        }

        // Level 1
        idx = available(level_start[1], level_end[1], 1, data, time);
        if (idx != -1)
        {
            data[idx].r_t--;
            strcpy(gantt[gantt_time], data[idx].p_id);
            gantt_time++;
            time++;

            if (data[idx].r_t == 0)
            {
                data[idx].completed = 1;
                data[idx].c_t = time;
                complete++;
            }
            continue;
        }

        // Level 2
        idx = available(level_start[2], level_end[2], 2, data, time);
        if (idx != -1)
        {
            data[idx].r_t--;
            strcpy(gantt[gantt_time], data[idx].p_id);
            gantt_time++;
            time++;

            if (data[idx].r_t == 0)
            {
                data[idx].completed = 1;
                data[idx].c_t = time;
                complete++;
            }
            continue;
        }

        // CPU idle
        strcpy(gantt[gantt_time], "IDLE");
        gantt_time++;
        time++;
    }
    for (int i = 0; i < total_proc; i++)
    {
        data[i].tat = data[i].c_t - data[i].a_t;
        data[i].w_t = data[i].tat - data[i].b_t;
    }
    // print process details
    for (int i = 0; i < total_proc; i++)
    {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               data[i].p_id,
               data[i].a_t,
               data[i].b_t,
               data[i].c_t,
               data[i].tat,
               data[i].w_t,
               data[i].level);
    }
    return 0;
}