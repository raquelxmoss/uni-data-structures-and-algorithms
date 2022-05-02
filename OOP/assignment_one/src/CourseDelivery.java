// Holds information about a course delivery -- a combination of a
// Paper offered at a Campus by a Lecturer.
public class CourseDelivery {
  private Campus campus;
  private Paper paper;
  private Lecturer lecturer;

  public CourseDelivery(Campus campus, Paper paper, Lecturer lecturer) {
    setCampus(campus);
    setPaper(paper);
    setLecturer(lecturer);
  }

  @Override
  public String toString() {
    return String.format("%-8s  %-10s  %-10s", getPaper().getNumber(), getCampus(), getLecturer());
  }

  public Lecturer getLecturer() {
    return this.lecturer;
  }

  public Paper getPaper() {
    return this.paper;
  }

  public Campus getCampus() {
    return this.campus;
  }

  private void setCampus(Campus campus) {
    this.campus = campus;
  }

  private void setLecturer(Lecturer lecturer) {
    this.lecturer = lecturer;
  }

  private void setPaper(Paper paper) {
    this.paper = paper;
  }
}
