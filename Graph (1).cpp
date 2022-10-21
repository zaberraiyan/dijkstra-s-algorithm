
#include "Graph.hpp"
#include <iostream>
const unsigned long infinity = 4294967295;

Graph:: ~Graph() { //deconstructor 
    for (unsigned int i = 0; i < adjacency_list.size(); i++) { //delete every edge 
        for(auto edge : adjacency_list.at(i).get_edge_list()) {
            delete edge; //delete the edge 
        }
    }
    adjacency_list.clear(); //clear the list 
}

Vertex Graph:: at(std::string label) { //function to get the function 
    for(unsigned int i=0; i<adjacency_list.size(); i++){
        if(*adjacency_list.at(i) == label) { 
            return adjacency_list.at(i); 
        }
    }
    Vertex x; 
    return x; 
}

void createPath( std::vector<std::string> &path, std::map<std::string, std::string> prev, std::string endLabel) { //function to complete the path 
    if(prev[endLabel]!=""){ //if not the empty string 
        createPath(path, prev, prev[endLabel]); //recursively call 
        path.push_back(endLabel);
    }
    else return; //return void otherwise
}

void Graph:: addVertex(std::string label) { //function to remove the vertex 
    Vertex x{label}; //create the vertex 
    adjacency_list.push_back(x); //push back adjecent list 
    }

void Graph::removeVertex(std::string label) {
    unsigned int i = 0;
    while (i < adjacency_list.size()) {
        if (*adjacency_list.at(i) == label) { // if found the label of the vertex to remove
            auto position = adjacency_list.begin() + i; //get iterator to remove
            adjacency_list.erase(position); //erase the element at the iterator
        }
        else { // the label is not equal to the vertex the loop is at
            auto elist = adjacency_list.at(i).get_edge_list();
            for (auto e = elist.begin(); e != elist.end(); e++) { // for every edge in the vertex
                auto edge = *e;
                if(edge->get_endpoint() == label) { // delete all occurrances of the label of the vertex to remove
                    adjacency_list.at(i).remove_edge(edge);
                }
            }
            i++; //increment i
        }
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) { 
    Edge *vEdge = new Edge(label2, weight); //edge pointer to the vertex edge 
    Edge *endEdge = new Edge(label1,weight); //edge pointer to the endpoint edge 
    for(unsigned int i=0; i<adjacency_list.size(); i++){ //traverse through every vertex in the graph 
        if(*adjacency_list.at(i) ==label1){ //if it is the first label 
            adjacency_list.at(i).push_back_edge(vEdge); //push the edge back 
        }
        else if(*adjacency_list.at(i) == label2) { //if it is the second label 
            adjacency_list.at(i).push_back_edge(endEdge); //push the edge back 
        }
    }
}

void Graph :: removeEdge(std::string label1, std::string label2){
    for(unsigned int i = 0; i<adjacency_list.size(); i++){ //for every vertex
        auto list = adjacency_list.at(i).get_edge_list();//set a variable to the list 
        auto x = list.begin(); //set x to the beginning 
        while(x!=list.end()){ //for every edge in the vertex 
            auto edge = *x;  //set the edge to pointe x 
            if(*adjacency_list.at(i)==label1){ //if the edge is found
                if(edge->get_endpoint() == label2){
                    adjacency_list.at(i).remove_edge(edge); //remove it 
                    break; 
                }
            }
            else if(*adjacency_list.at(i) ==label2) {//if the edge is found 
                if(edge->get_endpoint() == label1) { 
                    adjacency_list.at(i).remove_edge(edge); //remove it
                    break; 
                }
            }
            x++; //increment iterator 
        }
    }
}

unsigned long Graph:: shortestPath(std::string startlabel, std::string endlabel, std::vector<std::string> &path) { //Dijkstra's Algorithm to find the shortest path 
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> point; //structure for priority queue 
    std::map<std::string, int> distStart; //structure for the distance from the start 
    std::map<std::string, std::string> prev; //structure for previous
    
    for(unsigned int i=0; i < adjacency_list.size(); i++){ //for every element in the graph 
        distStart[*adjacency_list.at(i)] = INT_MAX; 
        prev[*adjacency_list.at(i)] = ""; 
    }
    point.push(std::make_pair(0, startlabel)); //push vertex into the point variable 
    distStart[startlabel] = 0; //set distance to 0 
    while(!point.empty()){  //while not empty 
        std::string current = point.top().second; //get the current vertex 
        point.pop(); //pop it 
        std::string neighbor; 

        for(unsigned int i =0; i<adjacency_list.size(); i++) { //for every element in the graph 
            for(auto edge : adjacency_list.at(i).get_edge_list()) { //for every edge 
                if(!(*adjacency_list.at(i) == current)){ //if at the current vertex 
                    if(!(edge->get_endpoint() ==current))
                        continue; //continue 
                    else neighbor = *adjacency_list.at(i);//if endpoint is the current vertex
                }
                else neighbor = edge->get_endpoint(); //if not the current vertex the set to be the neighbor 
                    auto weight = edge->get_weight();
                    unsigned long distNeighbor = distStart[neighbor]; //variable for distance to neighbor 
                    unsigned long distCurrent = distStart[current]; //variable for distance to current vertex 
                    if(!(distNeighbor > distCurrent + weight))  continue; //if not greater than current and the weight, do nothing
                    prev[neighbor] = current; //set prev vertex to current 
                    distStart[neighbor] = distStart[current] + weight; //distance of current 
                    point.push(std::make_pair(distStart[neighbor], neighbor)); //push point into queue 
                
            }
        }
    }
    path.push_back(startlabel); //push start 
    createPath(path,prev,endlabel); //create path 
    return distStart[endlabel]; //return weight of path
} 

void dijkstra::createTable() {
    auto startVertex = not_visisted.at(0); 
    for (unsigned int i = 0; i < not_visisted.size(); i++) { //for every element 
        if (i == 0) { //if found at the beginning 
            row startRow {*not_visisted.at(i), 0, Vertex()}; 
            table.push_back(startRow); //push back the vertex at the beginning 
        }
        else {
            row row {*not_visisted.at(i), infinity, Vertex()};
            table.push_back(row); //push back the element at the index 
        }
    }

    while (!not_visisted.empty()) {
        row* current_vertex = new row;
        current_vertex = &table.at(0);
        //finding the vertex with smallest distance to make the currentVertex
        for (unsigned int i = 0; i < table.size(); i++) { //for loop 
            if(table.at(i).visited != true) { // if it has been visited 
                row* temp = new row; //create a temp variable 
                *temp = table.at(i); //set temp to the table at the index 
                if (current_vertex->visited == true) { //if it has been visited 
                    current_vertex = temp; //set equal 
                }
                else if (temp->start_distance < current_vertex->start_distance) { //else compare which distance is less 
                    current_vertex = temp; //set equal to temp 
                }
                delete temp; //delete the temp variable after use 
            }
        }
        auto current = current_vertex->v; //
        std::list<Edge*> edge_list;
        edge_list = (current.get_edge_list());
        while (!edge_list.empty()) { //while the list is not empty
            for (unsigned int i = 0; i < table.size(); i++) { //for all the elements within the table size 
                if (edge_list.front()->get_endpoint() == *table.at(i).v) { 
                    if (table.at(i).visited == false) { //if the table has not been visited 
                        unsigned long new_distance = current_vertex->start_distance + edge_list.front()->get_weight(); //create a new distance 
                        if (new_distance < table.at(i).start_distance) { //if the distance is less than the start distance 
                            table.at(i).start_distance = new_distance; //the distance is the new distance 
                            table.at(i).prev = current_vertex->v; //set the previous vertex 
                        }
                    }
                }
                edge_list.pop_front();
            }
        }
        //adding the current_vertex to the list of visited verticies
        visit.push_back(current_vertex->v);
        current_vertex->visited = true;
        for (unsigned int i = 0; i < not_visisted.size(); i++) { //for loop 
            if (*not_visisted.at(i) == *(current_vertex->v)) { //check if its the vertex desired 
                auto iterator = not_visisted.begin() + i; //create a variable at the position 
                not_visisted.erase(iterator); //erase the iterator 
                break;
            }
        }
        delete current_vertex; //delete the current vertex 
    }
}
