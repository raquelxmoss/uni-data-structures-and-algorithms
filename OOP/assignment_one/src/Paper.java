import java.util.ArrayList;
import java.util.stream.Collectors;

// Stores information about a Paper that is offered at the school.
public class Paper {
  private String name;
  private int number;
  private ArrayList<AssessmentType> assessments = new ArrayList<>();
  private ArrayList<CourseDelivery> courseDeliveries = new ArrayList<>();
  private ArrayList<Major> majors = new ArrayList<>();

  public Paper(String name, int number) {
    setName(name);
    setNumber(number);
  }

  private void setName(String name) { this.name = name; }

  private void setNumber(int number) { this.number = number; }

  @Override
  public String toString() {
    return String.format("%-8s %-10s", number, name);
  }

  // Prints the Paper's details, including the Majors it belongs to.
  public String fullDetails() { return this.toString() + ' ' + this.getMajors(); }

  public int getNumber() {
    return this.number;
  }

  public ArrayList<Major> getMajors() { return this.majors; }

  public void addMajor(Major major) { this.majors.add(major); }

  public void addAssessment(AssessmentType assessment) {
    this.assessments.add(assessment);
  }

  public ArrayList<AssessmentType> getAssessments() {
    return this.assessments;
  }

  // Find the Paper's assessments by assessment name.
  public ArrayList<AssessmentType> getAssessments(String name) {
    return getAssessments()
            .stream()
            .filter(assessmentType -> assessmentType.getName().equals(name))
            .collect(Collectors.toCollection(ArrayList::new));
  }

  // Find the Paper's assessments by assessment name and weight.
  public ArrayList<AssessmentType> getAssessments(String name, double weight) {
    return getAssessments(name)
            .stream()
            .filter(assessmentType -> assessmentType.getWeight() > weight)
            .collect(Collectors.toCollection(ArrayList::new));
  }

  // Checks whether the paper has an assessment of the given name
  public boolean hasAssessment(String name) {
    return !getAssessments(name).isEmpty();
  }

  // Checks whether the paper has an assessment of the given name and weight
  public boolean hasAssessment(String name, double weight) {
    return !getAssessments(name, weight).isEmpty();
  }

  public void addCourseDelivery(CourseDelivery courseDelivery) {
    this.courseDeliveries.add(courseDelivery);
  }

  public ArrayList<CourseDelivery> getCourseDeliveries() { return this.courseDeliveries; }
}

