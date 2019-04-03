//AIM:Differentiate between link state routing and distance vector routing.

/****************************************************

	Author: RAJAT AGRAWAL

/***************************************************
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define mx 10
#define inf 999
string s2="";
struct node{
	int dis[20];	// to store the distance form a source to destination
	int prev[20];	// to store the next hop to reach  the destination
	int parent[20];
}arr[20];
//structure to store the details of each edge in the network
struct edge{
	int src,dest,w;
};
//initialization of data structures
void initialize(int adj[][mx],int v){
    int i,j;
    for(i=0;i<v;i++)
        for(j=0;j<v;j++){
            adj[i][j]=inf;
        }
}
void createadj(int adj[][mx],int u,int v,int cost,int type){
 if(type==1)
 	adj[u][v]=cost;
 else
 	adj[u][v]=adj[v][u]=cost;	
 }
void Initialize(int dis[],int prev[],int visited[],int ver){
	int v;
	for(v=0;v<ver;v++){
		dis[v]=inf;
		prev[v]=-1;
		visited[v]=0;
	}
}	
//print shortest path for lsrp
void printpathsssp(int prev[],int vt){
	if(prev[vt]==-1)
		return;
		printpathsssp(prev,prev[vt]);
		printf("->%2d",vt+1);
}
void printsssp(int dist[],int ver,int prev[],int src){
	int s=src,i;
	cout<<"\t\tPath: [u]->[v]  Min-Cost  Shortest Path\n";
	cout<<"\t\t      --------  --------  -------------\n";
	for(i=0;i<ver;i++){
		if(i==s)
			continue;
		printf("\t\t      [%d]->[%d]  %4d       %2d",src+1,i+1,dist[i],src+1);
		printpathsssp(prev,i);
		cout<<endl;
	}
	cout<<endl;
}
//dijkstra algorithm to find shortest path from a  source router to every other router in the network 
 void dijkstra_sssp(int adj[][mx],int ver,int src,int dis[],int prev[],int visited[]){
	int u,v,c,i,alt,min;
	Initialize(dis,prev,visited,ver);
	dis[src]=0;
	for(c=0;c<ver-1;c++){
		min=inf;
		for(i=0;i<ver;i++){
			if(visited[i]==0 && dis[i]<=min){
				min=dis[i];
				u=i;
			}	
		}
		visited[u]=1;
		for(v=0;v<ver;v++){
			if(adj[u][v]>0 && dis[u]!=inf){
				alt=dis[u]+adj[u][v];
				if(alt<dis[v]){
					dis[v]=alt;
					prev[v]=u;
				}
			}
		}
		cout<<"\t\tITERATION [ "<<c+1<<" ]..."<<endl;
		sleep(2);	
	printf("  ");	
	for(i=0;i<12*ver;i++)
 		printf("-");
	 printf("\n");
	printf("\t\t ");
	for(i=0;i<ver;i++)
		 printf("%4d | ",i+1);
	printf("\n");
	printf("  ");	 
	for(i=0;i<12*ver;i++)
 		printf("-");	 	 	
	printf("\n    COST        |");
	for(i=0;i<ver;i++)
		printf("%4d | ",dis[i]);
	printf("\n");
	printf("  ");	
	for(i=0;i<12*ver;i++)
 		printf("-");
	 printf("\n");
	
	}
	 printsssp(dis,ver,prev,src);
	
}	
//print path for dvrp
void printPath(int prev[], int v)
{
    if (v < 0)
        return;

    printPath(prev, prev[v]);
    cout << v+1 << " ";
}
//bellen ford algo to calculate shortest path for dvrp
void bellmen_ford(int adj[][mx],int ver,int c,vector<edge>&vll){
	//initialize all values
	string str[ver];
	int i,j,p,u,v,w;
	int temp[20];
	for(i=0;i<ver;i++){
		for(j=0;j<ver;j++){
			arr[i].parent[j]=-1;
		}	
	}
	for(i=0;i<ver;i++){
		for(int x=0;x<ver;x++){
			temp[x]=999;
		}
		temp[i]=0;
		p=ver;
		while (--p){
		    for (j = 0; j < c; j++) 
		    {
		        // edge from u to v having weight w        
		        u = vll[j].src, v = vll[j].dest;
		        w = vll[j].w;
		        
		        // if the distance to the destination v can be 
		        // shortened by taking the edge u-> v
		        if (temp[u] != 999 && temp[u] + w < temp[v])
		        {
		            // update distance to the new lower value
		            temp[v] = temp[u] + w;
		            
		            // set v's parent as u
		            arr[i].parent[v] = u;
		        }
		    }
    	}
			
	}
	
	for (i = 0; i < ver; i++) {
        for (j = 0; j < ver; j++) {
            arr[i].dis[j] =adj[i][j];
            arr[i].prev[j] = j;
        }
    }
    //calculate the minimum cost
    int flag;
    do {
        flag = 0;
        for (i = 0; i < ver; i++) {
            for (j = 0; j < ver; j++) {
                for (int k = 0; k < ver; k++) {
                    if ((arr[i].dis[j]) > adj[i][k]+arr[k].dis[j]) {
                        arr[i].dis[j] = arr[i].dis[k]+arr[k].dis[j];
                        arr[i].prev[j] = k;
                        flag++;
                    }
                
                    
                }
            }
            
        }
        
    } while (flag!=0);
    //print routing table information for each router
    for (i = 0; i < ver; i++) {
        cout << "Router info for router: " << i + 1 << endl;
        cout << "Dest\tNext Hop\tDist\tShortest path" << endl;
        cout<<"-------------------------------------------------"<<endl;
        for (int j = 0; j < ver; j++){
            	printf("%d\t%d\t\t%d\t", j+1,arr[i].prev[j]+1, arr[i].dis[j]);
            	cout<<"[ ";
            	printPath(arr[i].parent,j);
            	cout<<"]"<<endl;
           }
    }
    
}			
int main(){
	srand(time(NULL));
	int adj[mx][mx],dis[mx],prev[mx],visited[mx],x;
    int src,i,j,choice,ver=0,u,v,cost=0;
    int type;
    int count=0;
    edge e[50]; //array of links
    vector<edge>vll;//vector to store the links in the network topology
    do{	
    	cout<<"\nDISTANCE VECTOR ROUTING VS LINK STATE ROUTING";
    	cout<<"\n0.Exit";
    	cout<<"\n1.CREATE A NETWORK TOPOLOGY";
		cout<<"\n2.IMPLEMENT LSRP";
		cout<<"\n3.IMPLEMENT DVRP";    	
    	cout<<"\nEnter your choice:";
    	cin>>choice;
    	switch(choice){
    		case 0:
				printf("\nyou have opted to exit...\n");
				exit(0);
			case 1:
					printf("\nEnter type of network:[0: UNDIRECTED] := ");
				scanf("%d",&type);
				if(type!=0)
					type=1;
				do{
					 printf("\nEnter no of nodes/routers:(<=%d)",mx);
					 scanf("%d",&ver);
				  }while(ver>mx || ver<1);
				printf("\nEnter links as(u,v) & -1 to terminate:");
			  printf("\n\t\t 'u'    |      'v'     |   REMARK\n");
			  printf("\t   --------------------------------------------");
			  printf("\n");
				initialize(adj,ver);
 				  do{
				  	  printf("\t\t  ");
					  scanf("%d%d",&u,&v);
						if(u==v)
							cost=0;
						else		
					  		cost=(rand()%20)+1;
					  if(u==-1 || v==-1 )
						  break;
						else if(adj[u][v]<inf && u<ver && v<ver)
							  printf("\t\t\t\t\t   LINK EXISTS\n");
					  else if((u<ver && v<ver) && (u>-1 || v>-1)){
					  		if((u==v && cost>0)||(u!=v && cost==0))
					  			printf("\t\t\t\t\t   INVALID COST\n");
					  		else{	
						  	createadj(adj,u,v,cost,type);
						  	e[count].src=u;
						  	e[count].dest=v;
						  	e[count].w=cost;
						  	vll.push_back(e[count]);
						  	++count;
						  	printf("\t\t\t\t\t   LINK TAKEN\n");
						  	}
					  }		
						else
						  printf("\t\t\t\t\t   INVALID LINK\n");
					 }while(u<mx && v<mx);
					 printf("\nLINK MATRIX :\n");
					 printf("\n u|v |");
					 for(i=0;i<ver;i++)
						 printf("    %d",i);
						 printf("\n");
						 for(i=0;i<7*ver;i++)
					 			printf("-");
					 	printf("\n");		
				  for(i=0;i<ver;i++){
				  	printf("  %d  | ",i);
					 for(j=0;j<ver;j++){
						adj[i][i]=0;
						  printf("%4d ",adj[i][j]);
					}	  
				  printf("\n");
				  }
				  break;
			case 2:
				  do{
					printf("\nEnter node/router id to print routing table for:[1-%d]",ver);
					scanf("%d",&src);
					}while(src>ver);
					cout<<"\nLSRP ALGORITHM\n";
					cout<<"Routing table information for router: "<<src<<endl;
					dijkstra_sssp(adj,ver,src-1,dis,prev,visited);		
					break;	
			case 3:
					int v;
					cout<<"\nDVRP ALGORITHM"<<endl;
					bellmen_ford(adj,ver,count,vll);		
					break;		
    	}
    }while(choice>0);
    
	return 0;
}
//END
