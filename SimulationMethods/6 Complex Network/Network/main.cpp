

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int **adjacency;
int *degree;
int N;

void initialize_adj(int N_nodes);
void create_random_links(int N_links);

void initialize_adj(int N_nodes)
{
int i,j;
N = N_nodes;

adjacency = (int **)malloc(N*sizeof(int *));
for(i=0;i<N;i++)
    adjacency[i] = (int *)malloc(N*sizeof(int));

for(i=0;i<N;i++)
    for(j=0;j<N;j++)
        adjacency[i][j] = 0;


}

//create an Erdos-Renyi (random) network
void create_random_links(int N_links)
{
int i,j;
int N_links_placed;
    
//assume all nodes are present right from the start
    
N_links_placed = 0;
//printf("N=%d\n",N);fflush(stdout);
    while (N_links_placed<N_links)
        {
        i = (int)floor((double)N * rand()/(RAND_MAX+1.0));
        j = (int)floor((double)N * rand()/(RAND_MAX+1.0));
        //printf("%d %d\n",i,j);fflush(stdout);
        if ((i!=j)&&(adjacency[i][j]!=1))
            {
            adjacency[i][j] = 1;
            adjacency[j][i] = 1;
            N_links_placed++;
            }
        }
}

//Albert-Barabasi scale free network
void create_scale_free_links(int N_links)
{
int i,j;
int average_brought_in;
int N_nodes_added;
int total_sum_of_degrees;

int pick_number;
int sum_so_far;

average_brought_in = (int)floor(2.0*(double)N_links/(double)N);
printf("Each new node brings in an average of %d links\n",average_brought_in);

//make a small completely connected core
for(i=0;i<average_brought_in;i++)
    for(j=0;j<average_brought_in;j++)
    {
    adjacency[i][j] = 1;
    adjacency[j][i] = 1;
    }
    
//now we do preferential attachment
degree = (int *)malloc(N * sizeof(int));
total_sum_of_degrees = 0;
for(i=0;i<average_brought_in;i++)
    {
    degree[i] = average_brought_in;
    total_sum_of_degrees += degree[i];
    }
    
printf("Total sum at this point = %d\n",total_sum_of_degrees);
    
N_nodes_added = average_brought_in + 1;

printf("%d\n",N-1);

    while (N_nodes_added < (N-1) )
        {
            for(i=0;i<average_brought_in;i++)
                {
                //has to pick a node to connect to
                pick_number = (int)floor((double)total_sum_of_degrees*rand()/(RAND_MAX+1.0));
                
                //printf("picked number = %d of %d\n",pick_number,total_sum_of_degrees);fflush(stdout);
                //to figure out whom to link to I sum up the
                //ki until I find the node
                sum_so_far = 0;
                for(j=0;j<N_nodes_added-1;j++)
                    {
                    //printf("%d ",j);fflush(stdout);
                    sum_so_far +=degree[j];
                    if ((sum_so_far<pick_number)&&(sum_so_far+degree[j+1]>=pick_number)) break;
                    }
                //j is the node to link to
                printf("the node to link to is = %d\n",j);
                printf("N_nodes_added = %d\n",N_nodes_added);
                
                fflush(stdout);
                //N_nodes_added is linking
                adjacency[j][N_nodes_added] = 1;
                adjacency[N_nodes_added][j] = 1;
                degree[j] +=1;
                degree[N_nodes_added] +=1;
                total_sum_of_degrees +=2;
                
                N_nodes_added++;
                if (N_nodes_added > N-1) break;
                }

        
        
        }

}


void calculate_degree_distribution(int opt)
{
int i,j;
FILE *f;

degree = (int *)malloc(N * sizeof(int));
for(i=0;i<N;i++)
    {
    degree[i] = 0;
    for(j=0;j<N;j++)
        if (i!=j)
            degree[i] += adjacency[i][j];
    }

if(opt == 1)
    f = fopen("degree_erdos.txt","wt");
else
    f = fopen("degree_preference.txt","wt");
for(i=0;i<N;i++)
    fprintf(f,"%d\n",degree[i]);
    
fclose(f);
}

void write_graph_to_file(int opt){
    
    FILE *f;
    if(opt == 1)
        f = fopen("graph_erdos.txt","w");
    else
        f = fopen("graph_preference.txt","w");
    for(int i=0;i<N;++i) {
        fprintf(f,"%d\n",i);
    }
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(adjacency[i][j]) {
                fprintf(f,"%d %d\n",i,j);
            }
        }
    }
    fclose(f);
}


int main(int argc, const char * argv[])
{

initialize_adj(10);
create_scale_free_links(20);
calculate_degree_distribution(2);
write_graph_to_file(2);
initialize_adj(10);
create_random_links(20);
calculate_degree_distribution(1);
write_graph_to_file(1);

return 0;
}
