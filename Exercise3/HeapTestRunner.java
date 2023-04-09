package heap;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class HeapTestRunner {

  public static void main(String [] args){
    Result result = JUnitCore.runClasses(HeapPriorityQueueTest.class);
    for (Failure failure : result.getFailures()){
      System.out.println(failure.toString());
    }
    System.out.println("\n----Risultato del test:---\n\n\t "+result.wasSuccessful());
  }
}
