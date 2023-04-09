package heap;

import java.util.ArrayList;
import java.beans.Transient;
import java.util.Comparator;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import org.junit.Test;
import org.junit.Before;

/**
* test suite for the MinHeap library
* @author: Orru, Perotta , Marino
*/

public class HeapPriorityQueueTest {

  private static HeapPriorityQueue<Integer> heap;

  /* viene eseguito ogni volta che viene eseguita la classe */
  @Before
  public void createMinHeap(){
    heap = new HeapPriorityQueue<Integer>(10);
  }

  @Test
  public void TestIsEmpty_zeroEl(){
    assertTrue(heap.isEmpty());
  }

  @Test
  public void TestIsEmpty_oneEl(){
    heap.insert(10,23);
    assertFalse(heap.isEmpty());
  }

  @Test
  public void testSize_zeroEl() throws Exception{
    assertEquals(0, heap.size());
  }

  @Test
  public void testSize_oneEl() throws Exception{
    heap.insert(10,23);
    assertEquals(1, heap.size());
  }

  @Test
  public void testSize_threeEl() throws Exception{
    heap.insert(10,23);
    heap.insert(6,3);
    heap.insert(1,1);
    assertEquals(3, heap.size());
  }

  @Test
  public void testSize_sevenEl() throws Exception{
    heap.insert(10,23);
    heap.insert(6,3);
    heap.insert(1,1);
    heap.insert(120,5);
    heap.insert(14,6);
    heap.insert(65,20);
    heap.insert(3,10);
    assertEquals(7, heap.size());
  }

  @Test
  public void testParent_threeEl() throws Exception{
    heap.insert(10,23);
    heap.insert(6,3);
    heap.insert(1,1);
    assertEquals(new Integer(1), heap.parent_value(2));
  }


  @Test
  public void test_parentAllEl()throws Exception{
    heap.insert(10,23);
    heap.insert(6,3);
    heap.insert(1,1);
    heap.insert(120,5);
    heap.insert(14,6);
    heap.insert(65,20);
    heap.insert(3,10);
    assertEquals(new Integer(120) , heap.parent_value(3));
  }

  @Test
  public void test_leftSonAllEl()throws Exception{
    heap.insert(10,23);
    heap.insert(6,3);
    heap.insert(1,1);
    heap.insert(120,5);
    heap.insert(14,6);
    heap.insert(65,20);
    heap.insert(3,10);
    assertEquals(new Integer(65) , heap.left_child_value(2));
  }

  @Test
  public void test_rightSonAllEl()throws Exception{
    heap.insert(10,23);
    heap.insert(6,3);
    heap.insert(1,1);
    heap.insert(120,5);
    heap.insert(14,6);
    heap.insert(65,20);
    heap.insert(3,10);
    assertEquals(new Integer(6) , heap.right_child_value(0));
  }


  @Test
  public void testExtractFirst() {
    heap.insert(10, 10);
    heap.insert(7, 3);
    heap.insert(3, 30);
    heap.insert(1, 1);
    heap.insert(12, 12);
    assertEquals(new Integer(1), heap.extractfirst());
    assertEquals(new Integer(7), heap.extractfirst());
    assertEquals(new Integer(10), heap.extractfirst());
    assertEquals(new Integer(12), heap.extractfirst());
    assertFalse(heap.isEmpty());
    assertEquals(new Integer(3), heap.extractfirst());
    assertTrue(heap.isEmpty());
  }

  @Test
	public void testRemove(){
		heap.insert(10, 10);
		heap.insert(7, 3);
		heap.insert(3, 30);
		heap.insert(1, 1);
		heap.insert(12, 12);
		heap.insert(8,11);
		assertEquals(new Integer(1), heap.getFirst());
		heap.remove(1);
		assertEquals(new Integer(7),heap.getFirst());
	}

    @Test
	public void testDecreasePriority(){
    heap.insert(10, 10);
		heap.insert(7, 3);
		heap.insert(3, 30);
		heap.insert(12, 12);
		heap.decreasePriority(10,1);
		assertEquals(new Integer(10),heap.extractfirst());
		heap.decreasePriority(3, 2);
		assertEquals(new Integer(3),heap.extractfirst());

	}
}
