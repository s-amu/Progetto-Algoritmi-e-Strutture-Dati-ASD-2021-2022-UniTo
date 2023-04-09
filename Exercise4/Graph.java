package graph;
import java.nio.file.Path;
import java.util.*;
import java.util.HashMap;


/**
* It represents a Graph bidirectional
* @author Perrotta, Marino, Orru
* @param <G,T>: generic type of the Grap elements
*/

public class Graph <G>{

  private Map<G , List <Arch<G>>> map = new HashMap <>();
	public static HashMap<String, Double> dist = new HashMap<String,Double>();
  public static Map<String ,String> father = new HashMap<String,String>();


  private boolean direction ;

/**
 * Graph Costructor
 * @param direction
 */
  public Graph(boolean direction){
    this.direction = direction;
  }

/**
 * the new vertex whit an empty adjiacency list will be appended to the HasMap
 * @param new_Vertex
 * @throws GraphException throws an exception if the vertex already exist
 * @complexity O(1)
 */

  public void add_vertex (G new_Vertex) throws GraphException {
  if (new_Vertex == null){
    throw new GraphException("[ERROR IN ADD VERTEX ] : null parameter");
  }
  if (has_already_Vertex(new_Vertex)){
    throw new GraphException("[ERROR IN ADD VERTEX ] : Vertex already exist in the Graph ");
  }
  map.put (new_Vertex , new LinkedList<Arch<G>>());
  }

/**
 * it creates a new arch :
 * it creates a new Arch which whill be appended to the source's adjiacency list.
 * if bidirectional, the arch will be appended to the destination too
 * @param source
 * @param destination
 * @param i
 * @throws GraphException Throws an exception if one of both param is nul
 */

  public void add_arch(G source, G destination, double i) throws GraphException {
    if (source == null || destination == null){
      throw new GraphException("[ERROR ADD ARCH ]: you can't insert arches with null sources/destinations");
    }
    if (!map.containsKey(source)){
      add_vertex(source);
    }
    if (!map.containsKey(destination)){
      add_vertex(destination);
    }
    map.get(source).add(new Arch<G>(source, destination, i));

    if (is_bidirect()) {
      map.get(destination).add(new Arch<G>(destination, source, i));
    }
  }

/**
 * Checks if the graph has been created as bidirectional
 * @return boolean
 * @complexity O(1)
 */

    public boolean is_bidirect() {
        return this.direction;
    }

/**
 * Checks if a vertex already exist
 * @param search
 * @return boolean
 * @throws GraphException It throws an exception if param is null
 * @complexity O(1)
 */
  public boolean has_already_Vertex(G search) throws GraphException {
    if (search == null){
      throw new GraphException("[ERROR] hasVertex(): vertex cannot be NULL");
    }
    return map.containsKey(search);
  }

  /**
 * Checks if an Arch already exist
 * @param source
 * @param destination
 * @return boolean
 * @throws GraphException  It throws an exception if param are null
 */

  public boolean has_already_Arch(G source, G destination) throws GraphException {
    if (source == null || destination == null){
      throw new GraphException("[ERROR] hasArch(): source and destination cannot be NULL");
    }
    if (map.get(source) != null){
      return map.get(source).contains(new Arch<G>(source, destination));
    }
    return false;
  }

/**
 * It removes a vertex from the graph
 * @param val
 * @throws GraphException  Throws an exception if the param is null
 * @complexity O(n)
 */
  public void remove_vertex(G val) throws GraphException {
    if (val == null){
      throw new GraphException("Error: a null vertex cannot be removed");
    }
    if (map.containsKey(val)) {
      for (G k : map.keySet()) {
        if (has_already_Arch(k, val)) {
          remove_arch(k, val);
        }
      }
    map.remove(val);
    } else {
      throw new GraphException("Error: vertex not found. Can't remove this vertex: " + val);
    }
  }

/**
 * Removes an arch from the graph
 * @param src
 * @param dest
 * @throws GraphException It trhows an exception if param are null ,or if the graph does not contain one of the two boundary
 * @complexity O(1)
 */
  public void remove_arch(G src, G dest) throws GraphException {
    if (src == null || dest == null)
      throw new GraphException("Error: a null arch cannot be removed");

    if (!map.containsKey(src) || !map.containsKey(dest))
      throw new GraphException("Error: cannot remove an arch with a null boundary");

    if (has_already_Arch(src, dest)) {
      map.get(src).remove(dest);
    }
    if (is_bidirect()) {
      map.get(dest).remove(src);
    }
  }

/**
 * It gives the number of the vertex contained in the Graph
 * @return int
 * @complexity O(1)
 */
  public int get_number_vertex() {
    return map.keySet().size();
  }

/**
 * It gives the number of the arches contained in the Graph.
 * The half of the value will be returned the graph is
 * bidirectional
 * @return int
 * @complexity O(n)
 */
  public int get_number_arch() {
    int count = 0;
    for (G v : map.keySet()) {
    count += map.get(v).size();
    }
    if (this.direction == true) {
      count = count / 2;
    }
    return count;
  }

/**
 * Extracts a list of vertex contained in the graph
 * @return List<G>
 * @complexity O(n)
 */
  public List<G> get_vertexes() {
    List<G> v_list = new ArrayList<>();

    for (G k : map.keySet())
    v_list.add(k);

    return v_list;
  }


  public List<Arch<G>> get_arches() {

    List<Arch<G>> a_list = new ArrayList<>();
    for (G k : map.keySet()){
     for (int i = 0; i < map.get(k).size(); i++){
       a_list.add(map.get(k).get(i));
     }
    }
    return a_list;
  }


/**
 * Extracts a vertex's adjacency list
 * @param vertex
 * @return List<G>
 * @throws GraphException  * It throws an exception if param is null or if it is not contained in the graph
 * @complexity O(1)
 */

  public List<G> adj_list_of(G vertex) throws GraphException {
    if (vertex == null){
    throw new GraphException("Error: vertex null. Adjacent list cannot be printed");
    }
    if (!map.containsKey(vertex)){
      throw new GraphException("Error: vertex does not exist. Adjacent list cannot be printed");
    }
    List<G> adj_list = new ArrayList<>();
    for (int i = 0; i < map.get(vertex).size(); i++)
      adj_list.add(map.get(vertex).get(i).getEnd());
    return adj_list;
  }

  public Map<G, List<Arch<G>>> getMap() {
    return map;
  }


/**
* It gives the weight of a specific arch
* An exception will be throwed if one of the
* two param are null or if the arch does not exist
* @param v1
* @param v2
* @throws GraphException
* @complexity O(1)
*/
  public double get_w_btw(G v1,G v2) throws GraphException {
    if (v1 == null || v2 == null)
      throw new GraphException("Error: get_w_btw: Parameters cannot be null");

    if (has_already_Arch(v1, v2)) {
      for (int i = 0; i < map.get(v1).size(); i++)
        if (map.get(v1).get(i).getEnd() == v2)
          return map.get(v1).get(i).getWeight();
    } else
      throw new GraphException("Error: get_w_btw: arch (" + v1 + ", " + v2 + ") doesn't exist");

      return -1;
  }


/**
 * Algoritmo di Dijkstra che calcola il percorso di peso minimo da un nodo sorgente a tutti gli altri nodi
 * @param graph grafo su cui si vuole eseguire l'algoritmo di dijkstra
 * @param sstart nodo di partenza
 * @return sequenza di nodi che compongono il percorso di peso minimo da d a s
 */
    public Graph<String> minPath(Graph<String> graph, String start){
	HeapPriorityQueue<String> minQueue = new HeapPriorityQueue<String>(g.get_vertexes().size());
	List<Object> path = new ArrayList<Object>();
	Graph<String> minPath = new Graph<String>(false);

	List<String> vertex = graph.get_vertexes();
	try{
	    for(String x:vertex){
	    dist.put(x,Double.POSITIVE_INFINITY);
	    father.put(x,null);
	    }
	    father.put(start, start);
	    dist.put(s, 0.0);
	    for(String x:vertex){
	        minQueue.insert(x, dist.get(x));
	    }

	    while(!minQueue.isEmpty()){
	        String u = minQueue.extractfirst();
		for(String v: graph.adj_list_of(u)){
		    double weight = graph.get_w_btw(u, v);
		    double distanceThrought = dist.get(u)+weight;//distanza del padre + la sua distanza
		        if(distanceThrought<dist.get(v)){//se il costo è inferiore al nodo attuale
			    dist.put(v, distanceThrought);
			    if(!(minPath.has_already_Vertex(v))) minPath.add_vertex(v);
			    if(!(minPath.has_already_Vertex(u))) minPath.add_vertex(u);
			    minPath.add_arch(v,u,distanceThrought);
			    father.put(v, u);
			    minQueue.decreasePriority(v,dist.get(v));
			}
		}
	    }
	}catch(GraphException exception){
	    System.out.println(exception);
	}
	return minPath;
    }


/**
 * @return String
*/
  public String toString() {
    StringBuilder builder = new StringBuilder();
    for (G v : map.keySet()) {
      builder.append("Vertex: " + v + "\n\tAdj_list:");
      for (int i = 0; i < map.get(v).size(); i++) {
        builder.append("\n\t\t\t" + map.get(v).get(i));
      }
      builder.append("\n");
    }
    return (builder.toString());
  }
}