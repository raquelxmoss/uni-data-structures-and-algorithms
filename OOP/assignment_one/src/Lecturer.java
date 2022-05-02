import java.util.ArrayList;

// Holds information about a Lecturer, including their name, id,
// Campuses, and CourseDeliveries.
public class Lecturer {
  private int id;
  private String firstName;
  private String lastName;
  private ArrayList<Campus> campuses = new ArrayList<>();
  private ArrayList<CourseDelivery> courseDeliveries = new ArrayList<>();

  public Lecturer(int id, String firstName, String lastName, ArrayList<Campus> campuses) {
    setID(id);
    setFirstName(firstName);
    setLastName(lastName);
    setCampuses(campuses);
  }

  // Check whether the Lecturer belongs to the given Campus
  public boolean belongsToCampus(Campus campus) {
    return getCampuses().contains(campus);
  }

  public void addCourseDelivery (CourseDelivery courseDelivery) {
    getCourseDeliveries().add(courseDelivery);
  }

  public ArrayList<CourseDelivery> getCourseDeliveries() {
    return this.courseDeliveries;
  }

  public int getID() {
    return this.id;
  }

  public String getName() { return String.format("%s %s", this.firstName, this.lastName); }

  @Override
  public String toString() {
    return String.format("%s %s", this.firstName, this.lastName);
  }

  private ArrayList<Campus> getCampuses() { return this.campuses; }

  private void setID(int id) { this.id = id; }

  private void setFirstName(String name) { this.firstName = name; }

  private void setLastName(String name) { this.lastName = name; }

  private void setCampuses(ArrayList<Campus> campuses) { this.campuses = campuses; }
}
