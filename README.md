# Distance-vector-routing-vs-link-state-routing
simulation of distance vector and link state routing protocol used in computer network

## Problem Definition :

A program which will differentiate between distance vector routing and link state routing protocol . considering 'n' number of nodes/routers in a network. Making  sure that the number of links are greater than n.Randomly initializing weigths for each link. For any source and destination finding the shortest path chosen by DVR and LSR.

## DESCRIPTION :
  
> simulating the process of generating routing table for each router in the network.
	
> Computing the optimal path with least cost between any two routers.

> To find the shortest path in LSR I used the Dijkstra's algorithm.It finds the shortest path – distance to all the routers,      Based on which we find the routing table and the shortest path to all destination routers.

> To find the shortest path in DVR I used the bellmen ford algorithm.This algorithm helps a router to inform its neighbors of     topology changes periodically.

> Each router maintains a Distance Vector table containing the distance between itself and ALL possible destination nodes.  

> A value of 999 in the input denotes  infinity i.e no direct link between two routers. 

> check the file-name **output.txt** for sample test cases.
