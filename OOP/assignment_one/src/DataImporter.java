import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.stream.Collectors;

// Given CSV details for Lecturers, Papers, Majors, and Campuses,
// parses the CSVs and populates that information into domain objects
// to be used within the program.
public class DataImporter {
  private String lecturersPathname;
  private String papersPathname;
  private String majorsPathname;
  private String campusesPathname;
  private ArrayList<Campus> campuses;
  private ArrayList<Lecturer> lecturers;
  private ArrayList<Major> majors;
  private ArrayList<Paper> papers;

  public DataImporter(String lecturersPathname, String papersPathname, String majorsPathname, String campusesPathname) {
    this.lecturersPathname = lecturersPathname;
    this.papersPathname = papersPathname;
    this.majorsPathname = majorsPathname;
    this.campusesPathname = campusesPathname;
  }

  public void call() throws FileNotFoundException {
    this.campuses = importCampuses();
    this.lecturers = importLecturers(campuses);
    this.majors = importMajors();
    this.papers = importPapers(majors);
  }

  public ArrayList<Campus> getCampuses() {
    return this.campuses;
  }

  public ArrayList<Lecturer> getLecturers() {
    return this.lecturers;
  }

  public ArrayList<Major> getMajors() {
    return this.majors;
  }

  public ArrayList<Paper> getPapers() {
    return this.papers;
  }

  private ArrayList<Lecturer> importLecturers(ArrayList<Campus> campuses) throws java.io.FileNotFoundException {
    ArrayList<Lecturer> records = new ArrayList<>();
    try (Scanner scanner = new Scanner(new File(lecturersPathname))) {
      while (scanner.hasNextLine()) {
        records.add(createLecturer(scanner.nextLine(), campuses));
      }
    }
    // Adds randomness to Lecturers so that they can be randomly assigned to Papers.
    Collections.shuffle(records);
    return records;
  }

  private ArrayList<Paper> importPapers(ArrayList<Major> majors) {
    ArrayList<Paper> records = new ArrayList<>();
    try (Scanner scanner = new Scanner(new File(papersPathname))) {
      while (scanner.hasNextLine()) {
        records.add(createPaper(scanner.nextLine(), majors));
      }
    } catch(java.io.FileNotFoundException exception) {
      // NOOP for now
    }
    return records;
  }

  private ArrayList<Major> importMajors() {
    ArrayList<Major> records = new ArrayList<>();
    try (Scanner scanner = new Scanner(new File(majorsPathname))) {
      while (scanner.hasNextLine()) {
        records.add(createMajor(scanner.nextLine()));
      }
    } catch(java.io.FileNotFoundException exception) {
      // NOOP for now
    }
    return records;
  }

  private ArrayList<Campus> importCampuses() {
    ArrayList<Campus> records = new ArrayList<>();
    try (Scanner scanner = new Scanner(new File(campusesPathname))) {
      while (scanner.hasNextLine()) {
        records.add(createCampus(scanner.nextLine()));
      }
    } catch(java.io.FileNotFoundException exception) {
      // NOOP for now
    }
    return records;
  }

  private Lecturer createLecturer(String line, ArrayList<Campus> campuses) {
    String[] values = line.split(",");
    ArrayList<Campus> lecturerCampuses = campuses.stream().filter(c -> {
      String name = c.getName();
      return Objects.equals(name, values[3]) || Objects.equals(name, "Distance");
    }).collect(Collectors.toCollection(ArrayList::new));

    return new Lecturer(Integer.parseInt(values[0]), values[1], values[2], lecturerCampuses);
  }

  private Paper createPaper(String line, ArrayList<Major> majors) {
    String[] values = line.split(",");
    Paper paper = new Paper(values[1], Integer.parseInt(values[0]));

    String[] assessmentWeights = Arrays.copyOfRange(values, 3, values.length);
    String[] assessmentTypes = {"Assignments", "Tests", "Exam"};

    for (int index = 0; index < assessmentWeights.length; index++) {
      if (assessmentWeights[index].isEmpty()) { continue; }
      AssessmentType assessmentType = new AssessmentType(assessmentTypes[index], Double.parseDouble(assessmentWeights[index]));
      paper.addAssessment(assessmentType);
    }

    String[] majorNames = values[2].split("\\|");
    for (String name : majorNames) {
      Major major = majors.stream().filter(m -> m.getName().equals(name)).findFirst().get();
      major.addPaper(paper);
      paper.addMajor(major);
    }
    return paper;
  }

  private Major createMajor(String line) {
    String[] values = line.split(",");
    return new Major(values[0]);
  }

  private Campus createCampus(String line) {
    String[] values = line.split(",");
    return new Campus(values[0]);
  }
}
