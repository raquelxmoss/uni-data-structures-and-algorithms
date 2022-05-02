// Holds information about an Assessment -- its type and how much of a student's grade it is worth.
public class AssessmentType {
  private String name;
  private double weight;

  public AssessmentType(String name, double weight) {
    setName(name);
    setWeight(weight);
  }

  public String getName() {
    return this.name;
  }

  private void setName(String name) { this.name = name; }

  public double getWeight() {
    return this.weight;
  }

  private void setWeight(double weight) {
    this.weight = weight;
  }
}