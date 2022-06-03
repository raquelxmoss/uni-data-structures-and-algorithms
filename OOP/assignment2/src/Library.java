import java.util.ArrayList;

// Hello! Thanks for marking my assignment.
// I have a couple of important notes:

// I've been a professional software developer for the last 8 years,
// working mostly with Ruby (Rails) and JavaScript (React/Angular/Ember).
// As such, I use conventions and patterns that might not map well to Java
// but which I'm used to from my work. You might see those here.

// If you're interested, I was a self-taught developer, and I'm doing my GradDipInfSc
// because I mostly work with employers in the US, and having a relevant university
// qualification helps me in the job market.

public class Library {
  private LibraryAction startingNode;

  public Library() {
    displayInfo();

    DataImporter dataImporter = new DataImporter("library.txt");
    ArrayList<Record> records = dataImporter.call();

    LibraryFlowCreator directedGraphCreator = new LibraryFlowCreator();
    LibraryAction.records = records;
    this.startingNode = directedGraphCreator.call();
  }

  public static void main(String[] args) {
    Library program = new Library();
    program.run();
  }

  private void run() {
    startingNode.call();
  }

  private static void displayInfo() {
    System.out.println("**************************************");
    System.out.println("Assignment 2, 159.234 Semester 1 2022");
    System.out.println("Submitted by: Moss, Raquel, 22001105");
    System.out.println("My Major at Massey: Information Sciences");
    System.out.println("**************************************");
    System.out.println("\n");
  }
}