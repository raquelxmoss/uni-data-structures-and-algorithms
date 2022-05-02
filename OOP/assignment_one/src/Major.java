import java.util.ArrayList;

// Stores information about a Major offered at the School.
public class Major {
  private String name;
  private ArrayList<Paper> papers = new ArrayList<>();

  public Major(String name) {
    setName(name);
  }

  @Override
  public String toString() {
    return getName();
  }

  public String getName() {
    return this.name;
  }

  private void setName(String name) { this.name = name; }

  public ArrayList<Paper> getPapers() {
    return this.papers;
  }

  public void addPaper(Paper paper) {
    this.papers.add(paper);
  }
}
