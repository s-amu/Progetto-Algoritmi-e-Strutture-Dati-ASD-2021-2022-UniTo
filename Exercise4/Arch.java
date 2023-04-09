package graph;

import java.util.*;

public class Arch<G>{

  G start;
  G end;
  double weight;

  public Arch(G start, G end, double weight) {
    this.start = start;
    this.end = end;
    this.weight = weight;
  }

  public Arch(G start, G end) {
    this.start = start;
    this.end = end;
    //this.weight = -1;
  }

  public double getWeight() {
    return this.weight;
  }

  public G getStart() {
    return this.start;
  }

  public G getEnd() {
    return this.end;
  }

  @Override
  public String toString() {
    return "start: " + start + "\t end: " + end + "\t weight:" + weight;
  }


  @Override
  public boolean equals(Object o) {
    if (this == o)
      return true;
    if (o == null || getClass() != o.getClass())
      return false;

    Arch<?> arch = (Arch<?>) o;
    return Objects.equals(start, arch.start) && Objects.equals(end, arch.end);
    }
}
