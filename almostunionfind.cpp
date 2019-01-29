// Devin Kim ddk3ev@virginia.edu
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <limits.h>

// Google implementations of union-find and work backwards from there
int parent[100005*2], cnt[100005*2], id[100005*2]; //we need to add a CNT and ID array to keep track
long long sum[100005*2];
int n_num, n_cmd, new_node; //we will use this new_node int to help with our moving

int find(int i)
{
    if (parent[i] == i)
        return i;
    else
        return parent[i] = find(parent[i]);
}

void merge(int p, int q)
{
    int set_p = find(id[p]), set_q = find(id[q]);

    if (set_p != set_q)
    {
        parent[set_p] = set_q;
        cnt[set_q] += cnt[set_p];
        sum[set_q] += sum[set_p];
    }
}

void move(int p) //we need this for operation 2
{
    int set_p = find(id[p]);

    sum[set_p] -= p;
    cnt[set_p]--;

    id[p] = ++new_node;
    sum[id[p]] = p;
    cnt[id[p]] = 1;
    parent[id[p]] = id[p];
}

int main()
{
    while(scanf("%d%d", &n_num, &n_cmd) != EOF)
    {
        //create tables
        for (int i = 0; i <= n_num; i++)
        {
            id[i] = parent[i] = sum[i] = i;
            cnt[i] = 1;
        }
        new_node = 100005 + 1;
        
        //input
        for (int i = 0; i < n_cmd; i++)
        {
            int op, p, q;
            scanf("%d", &op);

            if (op == 1)
            {
                scanf("%d%d", &p, &q);
                merge(p, q);
            }
            else if (op == 2)
            {
                scanf("%d%d", &p, &q);
                int set_p = find(id[p]), set_q = find(id[q]);
                if (set_p != set_q){
                    move(p);
                    merge(p, q);
                }
            }
            else if (op == 3)
            {
                scanf("%d", &p);
                printf("%d %lld\n", cnt[find(id[p])], sum[find(id[p])]);
            }
        }
    }

    return 0;
}
