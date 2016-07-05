#include <cstdlib>
#include <string>
#include <algorithm>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/fileformats/GraphIO.h>

using namespace ogdf;

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char * argv[])
{
    if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        printf("Genereate an SVG image from a GML file.\n");
        printf("---------------------------------------\n\n");
        
        printf("gml2svg -f graph.gml -o graph.svg\n");
        printf("gml2svg -t -o graph.svg\n");
        printf("gml2svg -gml\n");
        
        printf("---------------------------------------\n\n");
        
        printf("-h Show This help text.\n");
        
        printf("-f File    The GML file to be parsed.\n");
        printf("-t         An SVG is generated from a test OGDF graph.\n");
        printf("-o File    Optional, defaults to graph.svg\n");
        
        printf("-gml       Generate the test graph test.gml\n");
    }

    if(cmdOptionExists(argv, argv+argc, "-t"))
    {
        Graph G;
        GraphAttributes GA(G, GraphAttributes::nodeGraphics | GraphAttributes::edgeGraphics );

        const int LEN = 11;
        for(int i = 1; i<LEN; ++i) {
            node left = G.newNode();
            GA.x(left) = -5*(i+1);
            GA.y(left) = -20*i;
            GA.width(left) = 10*(i+1);
            GA.height(left) = 15;

            node bottom = G.newNode();
            GA.x(bottom) = 20*(LEN-i);
            GA.y(bottom) = 5*(LEN+1-i);
            GA.width(bottom) = 15;
            GA.height(bottom) = 10*(LEN+1-i);

            edge e = G.newEdge(left,bottom);
            DPolyline &p = GA.bends(e);
            p.pushBack(DPoint(10,-20*i));
            p.pushBack(DPoint(20*(LEN-i),-10));
        }
    
        char * filename_out = getCmdOption(argv, argv + argc, "-o");
    
        if (filename_out)
        {
            GraphIO::drawSVG(GA, filename_out);
        }else{
            GraphIO::drawSVG(GA, "graph.svg");
        }

    }
    
    if(cmdOptionExists(argv, argv+argc, "-gml"))
    {
        Graph G;
        GraphAttributes GA(G, GraphAttributes::nodeGraphics | GraphAttributes::edgeGraphics );

        const int LEN = 11;
        for(int i = 1; i<LEN; ++i) {
            node left = G.newNode();
            GA.x(left) = -5*(i+1);
            GA.y(left) = -20*i;
            GA.width(left) = 10*(i+1);
            GA.height(left) = 15;

            node bottom = G.newNode();
            GA.x(bottom) = 20*(LEN-i);
            GA.y(bottom) = 5*(LEN+1-i);
            GA.width(bottom) = 15;
            GA.height(bottom) = 10*(LEN+1-i);

            edge e = G.newEdge(left,bottom);
            DPolyline &p = GA.bends(e);
            p.pushBack(DPoint(10,-20*i));
            p.pushBack(DPoint(20*(LEN-i),-10));
        }

        GraphIO::writeGML(GA, "test.gml");
    }

    char * filename = getCmdOption(argv, argv + argc, "-f");

    if (filename)
    {
        printf("%s\n", filename);
        Graph G;
        
        GraphAttributes GA(G,
                GraphAttributes::nodeGraphics | 
                GraphAttributes::edgeGraphics |
                GraphAttributes::edgeStyle |
                GraphAttributes::nodeStyle);
        
        bool status = GraphIO::readGML(GA, G, filename);
        
        if (status)
        {
            printf("success reading file\n");
        
            
            char * filename_out = getCmdOption(argv, argv + argc, "-o");
        
            if (filename_out)
            {
                GraphIO::drawSVG(GA, filename_out);
            }else{
                GraphIO::drawSVG(GA, "graph.svg");
            }

        }else {
            printf("error reading file\n");
        }
    }

	return 0;
}
