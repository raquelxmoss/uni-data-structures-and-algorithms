import java.util.ArrayList;
import java.util.Comparator;

// Given information about Papers, Lecturers, and Campuses,
// creates CourseDeliveries so that each Paper is taught at
// each Campus, by a Lecturer. Lecturers are randomly assigned
// to Papers based at their Campuses, with each Lecturer delivering
// at least one course, and no more than four.
public class CourseDeliveryFactory {
  private static int MAX_DELIVERIES_PER_LECTURER = 4;
  private static int MIN_DELIVERIES_PER_LECTURER = 1;

  private ArrayList<Campus> campuses;
  private ArrayList<Lecturer> lecturers;
  private ArrayList<Paper> papers;

  public CourseDeliveryFactory(ArrayList<Campus> campuses, ArrayList<Lecturer> lecturers, ArrayList<Paper> papers) {
    setCampuses(campuses);
    setLecturers(lecturers);
    setPapers(papers);
  }

  private void setCampuses(ArrayList<Campus> campuses) {
    this.campuses = campuses;
  }

  private void setLecturers(ArrayList<Lecturer> lecturers) {
    this.lecturers = lecturers;
  }

  private void setPapers(ArrayList<Paper> papers) {
    this.papers = papers;
  }

  private ArrayList<Campus> getCampuses() {
    return this.campuses;
  }

  private ArrayList<Lecturer> getLecturers() {
    return this.lecturers;
  }

  private ArrayList<Paper> getPapers() {
    return this.papers;
  }

  // Creates CourseDeliveries based on the given information.
  // Throws an error if any Lecturers are idle.
  public void seed() throws Exception {
    createCourseDeliveries();

    boolean idleLecturers = getLecturers()
            .stream()
            .anyMatch(lecturer -> lecturer.getCourseDeliveries().size() < MIN_DELIVERIES_PER_LECTURER);

    if (idleLecturers) {
      throw new Exception("One or more lecturers do not have enough course deliveries");
    }
  }

  // Selects the first available Lecturer for the given campus, choosing the
  // lecturer with the fewest existing CourseDeliveries first, to ensure
  // equitable distribution of CourseDeliveries between lecturers.
  // Throws an error if all Lecturers have reached the maximum number of
  // CourseDeliveries per Lecturer.
  private Lecturer firstAvailableLecturer(Campus campus) throws Exception {
    getLecturers().sort(Comparator.comparingInt(a -> a.getCourseDeliveries().size()));

    boolean allLecturersAtCapacity = getLecturers()
            .stream()
            .allMatch(lecturer -> lecturer.getCourseDeliveries().size() >= MAX_DELIVERIES_PER_LECTURER);

    if (allLecturersAtCapacity) {
      throw new Exception("No available lecturers");
    }

    return getLecturers()
            .stream()
            .filter(l -> l.belongsToCampus(campus))
            .filter(l -> l.getCourseDeliveries().size() < MAX_DELIVERIES_PER_LECTURER)
            .findAny()
            .orElse(null);
  }

  // For each Campus, iterates through each Paper and selects a Lecturer to deliver the
  // course. Creates the CourseDelivery, and stores the CourseDelivery against the
  // Lecturer and Paper.
  // Note: This information could also be stored against the Campus, but since the current
  // system doesn't require querying for that information, I've omitted it, following the
  // YAGNI principle.
  private void createCourseDeliveries() {
    getCampuses().forEach(campus -> getPapers().forEach(paper -> {
      try {
        Lecturer lecturer = firstAvailableLecturer(campus);
        CourseDelivery courseDelivery = new CourseDelivery(campus, paper, lecturer);

        lecturer.addCourseDelivery(courseDelivery);
        paper.addCourseDelivery(courseDelivery);
      } catch (Exception e) {
        // noop for now
      }
    }));
  }
}