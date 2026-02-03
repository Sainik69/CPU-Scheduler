#include <stdio.h>

struct process
{
    char p_id[6];
    int a_t;   // Arrival Time
    int b_t;   // Burst Time
    int s_t;   // Start Time
    int c_t;   // Completion Time
    int tat;   // Turnaround Time
    int w_t;   // Waiting Time
};

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

            done[idx] = 1;
            completed++;
        }
    }
}

int main()
{
    int n;
    printf("Number of Processes: ");
    scanf("%d", &n);

    struct process data[n];

    for (int i = 0; i < n; i++)
    {
        printf("\nProcess ID: ");
        scanf("%5s", data[i].p_id);

        printf("Arrival Time: ");
        scanf("%d", &data[i].a_t);

        printf("Burst Time: ");
        scanf("%d", &data[i].b_t);
    }

    sjf(data, n);

    printf("\nGANTT CHART:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d | %s | %d  ",
               data[i].s_t,
               data[i].p_id,
               data[i].c_t);
    }

    printf("\n\nPID\tAT\tBT\tST\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               data[i].p_id,
               data[i].a_t,
               data[i].b_t,
               data[i].s_t,
               data[i].c_t,
               data[i].w_t,
               data[i].tat);
    }

    return 0;
}
