package graph ;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class Graph_test_run {

  public static void main(String[] args) {
  Result result = JUnitCore.runClasses(Graph_unit_test.class);
    for (Failure failure : result.getFailures()) {
      System.out.println(failure.toString());
    }
    System.out.println("\n----RISULTATO DEL TEST----\n\n\t" + result.wasSuccessful() + "\n");
    }
}
