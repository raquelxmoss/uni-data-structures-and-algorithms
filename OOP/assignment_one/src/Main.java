import java.util.ArrayList;

// Hello! Thanks for marking my assignment.
// I have a couple of important notes:

// I've been a professional software developer for the last 8 years,
// working mostly with Ruby (Rails) and JavaScript (React/Angular/Ember).
// As such, I use conventions and patterns that might not map well to Java
// but which I'm used to from my work. You might see those here.

// For example: Ruby convention is to use short methods and few comments,
// so my commenting might be sparse as compared with what you expect.
// We also make less use of getters and setters, and have different naming
// conventions for them. In this assignment, I've used getters and setters
// internally as suggested in the textbook, but I've only exposed them publicly
// when they are needed as part of a class' public interface.

// For this assessment, it was also a challenge working without a database + ORM,
// which is what I'm used to! :)

// A note on streams usage -- I'm not sure if we were "allowed" to do this, but
// the syntax is familiar to me due to working with RxJS for a few years, so it
// felt comfortable to use.

// As I work full time, I couldn't dedicate as much time to this assignment as I wanted to.
// If I were creating this application for work, I'd add a spec suite, jdoc, and much more
// error handling than is present here.

// If you're interested, I was a self-taught developer, and I'm doing my GradDipInfSc
// because I mostly work with employers in the US, and having a relevant university
// qualification helps me in the job market.

public class Main {
  private School school;

  public static void main(String[] args) throws Exception {
    Main main = new Main();
    displayInfo();
    main.taskOne();
    main.taskTwo();
    main.taskThree();
    main.taskFour();
    main.taskFive();
    main.taskSix();
    main.taskSeven();
    main.taskEight();
  }

  public Main () throws Exception {
    this.school = new School("School of Mathematical and Computational Sciences");
  }

  private static void displayInfo() {
    System.out.println("**************************************");
    System.out.println("Assignment 1, 159.234 Semester 1 2022");
    System.out.println("Submitted by: Moss, Raquel, 22001105");
    System.out.println("My Major at Massey: Information Sciences");
    System.out.println("**************************************");
    System.out.println();
  }

  private void taskOne() {
    System.out.println("---------------- Task 1 ----------------");
    System.out.println("School Full Name: " + this.school.getName());
    System.out.println();
  }

  private void taskTwo() {
    System.out.println("---------------- Task 2 ----------------");
    System.out.println("All papers details:");
    for (Paper paper : school.getPapers()) {
      System.out.println(paper.fullDetails());
    }
    System.out.println();
  }

  private void taskThree() {
    System.out.println("---------------- Task 3 ----------------");
    System.out.println("Papers that belong to Major IS:");
    ArrayList<Paper> isPapers = this.school.getMajor("IS").getPapers();
    for (Paper paper : isPapers) {
      System.out.println(paper);
    }
    System.out.printf("Total matching papers in specified Major - IS: %s\n", isPapers.size());
    System.out.println();
  }

  private void taskFour() {
    System.out.println("---------------- Task 4 ----------------");
    System.out.println("Papers that have an exam:");
    ArrayList<Paper> examPapers = this.school.getPapersByAssessment("Exam");
    for (Paper paper : examPapers) {
       System.out.println(paper);
    }
    System.out.printf("Total number of papers that have an exam: %s\n", examPapers.size());
    System.out.println();
  }

  private void taskFive() {
    System.out.println("---------------- Task 5 ----------------");
    System.out.println("All papers whose assignments weigh more than 50% in total:");
    ArrayList<Paper> papers = this.school.getPapersByAssessment("Assignments", 0.5);
    for (Paper paper : papers) {
       System.out.println(paper);
    }
    System.out.printf("Total number of papers that have assignments weighing more than 50%%: %s\n", papers.size());
    System.out.println();
  }

  private void taskSix() {
    System.out.println("---------------- Task 6 ----------------");
    System.out.println("Paper offering details:");
    ArrayList<CourseDelivery> deliveries = this.school.getCourseDeliveries();
    for (CourseDelivery courseDelivery : deliveries) {
      System.out.println(courseDelivery);
    }
    System.out.println();
  }

  private void taskSeven() {
    System.out.println("---------------- Task 7 ----------------");
    System.out.println("The paper offerings that I teach: ");
    ArrayList<CourseDelivery> deliveries = this.school.getCourseDeliveries("Raquel Moss");
    for (CourseDelivery courseDelivery : deliveries) {
      System.out.println(courseDelivery);
    }
    System.out.println("I am teaching " + deliveries.size() + " paper(s)");
    System.out.println();
  }

  private void taskEight() {
    System.out.println("---------------- Task 8 ----------------");
    System.out.println("The lecturer teaching 159234 at Auckland:");
    CourseDelivery courseDelivery = school.getCourseDelivery("Auckland", 159234);
    System.out.printf("Lecturer's name: %s%n", courseDelivery.getLecturer());
    System.out.printf("This lecturer is teaching %s paper(s)%n", courseDelivery.getLecturer().getCourseDeliveries().size());
    System.out.println();
  }
}
