import java.util.ArrayList;
import java.util.stream.Collectors;

public class School {
  private String name;
  private ArrayList<Major> majors;
  private ArrayList<Paper> papers;
  private ArrayList<Campus> campuses;
  private ArrayList<Lecturer> lecturers;

  public School(String name) throws Exception {
    setName(name);

    // Import CSV data, parse into domain objects, and store them.
    // Note, if running within IntelliJ, you might need to prepend
    // /src to the path.
    DataImporter importer = new DataImporter(
            "lecturers.csv",
            "papers.csv",
            "majors.csv",
            "campuses.csv"
    );

    importer.call();

    setLecturers(importer.getLecturers());
    setMajors(importer.getMajors());
    setPapers(importer.getPapers());
    setCampuses(importer.getCampuses());

    createCourseDeliveries();
  }

  public String getName() {
    return name;
  }

  private void setName(String name) { this.name = name; }

  private ArrayList<Lecturer> getLecturers() { return lecturers; }

  private void setLecturers(ArrayList<Lecturer> lecturers) { this.lecturers = lecturers; }

  private ArrayList<Major> getMajors() { return majors; }

  private void setMajors(ArrayList<Major> majors) { this.majors = majors; }

  // Return all Papers offered at the School
  public ArrayList<Paper> getPapers() {
    return papers;
  }

  private void setPapers(ArrayList<Paper> papers) {
    this.papers = papers;
  }

  // Return Papers that have a given assessment, e.g. "Exam".
  public ArrayList<Paper> getPapersByAssessment(String name) {
    return getPapers()
            .stream()
            .filter(p -> p.hasAssessment(name))
            .collect(Collectors.toCollection(ArrayList::new));
  }

  // Return Papers that have a given assessment and weight, e.g. "Exam", 0.5
  public ArrayList<Paper> getPapersByAssessment(String name, double weight) {
    return getPapers()
            .stream()
            .filter(p -> p.hasAssessment(name, weight))
            .collect(Collectors.toCollection(ArrayList::new));
  }

  // Get a Paper by its ID number
  public Paper getPaper(int number) {
    return getPapers()
            .stream()
            .filter(p -> number == p.getNumber())
            .findAny()
            .orElse(null);
  }

  // Get a Lecturer by their ID number
  public Lecturer getLecturer(int number) {
    return getLecturers()
            .stream()
            .filter(l -> number == l.getID())
            .findAny()
            .orElse(null);
  }

  // Get a Lecturer by their name
  public Lecturer getLecturer(String fullName) {
    return getLecturers()
            .stream()
            .filter(l -> l.getName().equals(fullName))
            .findAny()
            .orElse(null);
  }

  // Get a Major by its name
  public Major getMajor(String name) {
    return getMajors()
            .stream()
            .filter(m -> name.equals(m.getName()))
            .findAny()
            .orElse(null);
  }

  private ArrayList<Campus> getCampuses() { return campuses; }

  // Get a Campus by its name
  private Campus getCampus(String name) {
    return getCampuses()
            .stream()
            .filter(c -> name.equals(c.getName()))
            .findAny()
            .orElse(null);
  }

  private void setCampuses(ArrayList<Campus> campuses) {
    this.campuses = campuses;
  }

  // Get the CourseDeliveries for all Papers offered at the School
  public ArrayList<CourseDelivery> getCourseDeliveries() {
    ArrayList<CourseDelivery> deliveries = new ArrayList<>();

    getPapers().forEach(paper -> deliveries.addAll(paper.getCourseDeliveries()));

    return deliveries;
  }

  // Get the CourseDeliveries offered by a Lecturer
  public ArrayList<CourseDelivery> getCourseDeliveries(String lecturerName) {
    return getLecturer(lecturerName).getCourseDeliveries();
  }

  // Get CourseDelivery by its Campus and Paper number
  public CourseDelivery getCourseDelivery(String campusName, int paperNumber) {
    Campus campus = getCampus(campusName);
    Paper paper = getPaper(paperNumber);

    return paper.getCourseDeliveries()
            .stream()
            .filter(cd -> cd.getCampus().equals(campus))
            .findFirst()
            .orElse(null);
  }

  // Create CourseDeliveries for each Campus/Paper/Lecturer combination offered at the School.
  private void createCourseDeliveries() throws Exception {
    CourseDeliveryFactory factory = new CourseDeliveryFactory(campuses, lecturers, papers);
    factory.seed();
  }
}
