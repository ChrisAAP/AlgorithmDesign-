#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h> 
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void exportGDF(PNGraph Graph);
void exportGraphSON(PNGraph Graph);
void exportGraphML(PNGraph Graph);
void exportGEXF(PNGraph Graph);

int main() {
    typedef TPt<TNGraph> PNGraph;
    PNGraph G = TNGraph::New();
    for(int i = 0; i <= 10878; i++)
    {
        G->AddNode(i);
    }
    ifstream archivo_entrada;
    char linea[128];
    archivo_entrada.open("p2p-Gnutella04.txt");
    if(archivo_entrada.fail())
    {
        cout<<"Error al abrir el archivo \n";
        return 0;
    }
    for(int i = 0; i < 4; i++)
        archivo_entrada.getline(linea,sizeof(linea));
    string origen, destino;
    int org, dest;
    while(!archivo_entrada.eof())
    {
        archivo_entrada.getline(linea,sizeof(linea));
        string str(linea);
        istringstream iss(str);
        if(iss)
        {
            iss >> origen;
            iss >> destino;
            dest = stoi(destino);
            org = stoi(origen);
            
            G->AddEdge(org,dest);
        }
    }
    archivo_entrada.close();
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    exportGDF(G);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
    cout << "Time GDF: " << time_span.count()  << "seconds" << endl;
    t1 = high_resolution_clock::now();
    exportGEXF(G);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double> >(t2 - t1);
    cout << "Time GEXF: " << time_span.count()  << "seconds" << endl;
    t1 = high_resolution_clock::now();
    exportGraphML(G);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double> >(t2 - t1);
    cout << "Time GraphML: " << time_span.count()  << "seconds" << endl;
    t1 = high_resolution_clock::now();
    exportGraphSON(G);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double> >(t2 - t1);
    cout << "Time GraphSON: " << time_span.count()  << "seconds" << endl;
    return 0;
}
void exportGDF(PNGraph Graph)
{
    ofstream s_Out;
    s_Out.open("grafoGnutella.gdf");
    
    if (s_Out.is_open())
    {
        s_Out << "nodedef>name\n";
        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++)
            s_Out << NI.GetId() << ",\n";
        s_Out << "edgedef>node1,node2\n";
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++)
            s_Out << EI.GetSrcNId() << "," << EI.GetDstNId() << "\n";
        s_Out.close();
    }
}
void exportGraphSON(PNGraph Graph)
{
    ofstream s_Out;
    s_Out.open("grafoGnutella.json");
    if (s_Out.is_open())
    {
        s_Out << "{ \"graph\": {\n";
        s_Out << "\"nodes\": [\n";
        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++)
        {
            s_Out << "{\n \"_id\": \"" << NI.GetId() << "\" }";
            if (NI == Graph->EndNI())
                s_Out << " ],\n";
            else
                s_Out << ",\n";
        }
        s_Out << "\"edges\": [\n";
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++)
        {
            s_Out << "{ \"source\": \"" << EI.GetSrcNId() << "\", \"target\": \"" << EI.GetDstNId() << "\" }";
            
            if (EI == Graph->EndEI())
                s_Out << " ]\n";
            else
                s_Out << ",\n";
        }
        s_Out << "} }";
    }
}
void exportGraphML(PNGraph Graph){
    ofstream s_Out;
    s_Out.open("grafoGnutella.graphml");
    if (s_Out.is_open())
    {
        s_Out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        s_Out << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
        s_Out << "<graph id=\"G\" edgedefault=\"directed\">\n";
        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++)
            s_Out << "<node id=\"n" << NI.GetId() << "\"/>\n";
        int i = 0;
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++,i++)
            s_Out << "<edge id=\"e" << i << "\" source=\"n" << EI.GetSrcNId() << "\" target=\"n" << EI.GetDstNId() << "\" />\n";
        s_Out << "</graph>\n";
        s_Out << "</graphml>\n";
        s_Out.close();
    }
}
void exportGEXF(PNGraph Graph){
    ofstream s_Out;
    s_Out.open("grafoGnutella.gexf");
    if (s_Out.is_open())
    {
        s_Out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        s_Out << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
        s_Out << "<graph mode=\"static\" defaultedgetype=\"directed\">\n";
        s_Out << "<nodes>\n";
        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++)
            s_Out << "<node id=\"" << NI.GetId() << "\" />\n";
        s_Out << "</nodes>\n";
        s_Out << "<edges>\n";
        int i = 0;
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++,i++)
            s_Out << "<edge id=\"" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\" />\n";
        s_Out << "</edges>\n";
        s_Out << "</graph>\n";
        s_Out << "</gexf>\n";
        s_Out.close();
    }
}