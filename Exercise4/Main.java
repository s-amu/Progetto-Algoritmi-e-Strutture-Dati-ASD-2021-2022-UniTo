package graph;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Main{

  public static void main(String[] args) {
    String filepath = "graph/italian_dist_graph.csv";

    System.out.println("Loading data from file...");

    Path inputFilePath = Paths.get(filepath);

    Graph<String> graph = new Graph<String>(false);

    try {
      BufferedReader fileinputrReader = Files.newBufferedReader(inputFilePath, StandardCharsets.UTF_8);
      String line = null;
      while ((line = fileinputrReader.readLine()) != null) {
        String[] lineElements = line.split(",");
        graph.add_arch(lineElements[0], lineElements[1], Float.parseFloat(lineElements[2]));
      }
      //System.out.println(graph);
      System.out.println("\n Calculating Dijkstra..\n\n\n\n");
      Graph <String> minPath = graph.minPath(graph , "torino");
      List<String> vertex = minPath.get_vertexes();
      String pathToTarget = "catania";
      while (pathToTarget != "torino"){
        System.out.println("vertice : [ " + pathToTarget + " ]");
        System.out.println("peso del percorso dell'arco = [" + Graph.dist.get(pathToTarget) + " ]\n");
        pathToTarget=Graph.father.get(pathToTarget);
      }

    }catch (Exception ex){
      System.out.println(ex);
    }
  }
}
