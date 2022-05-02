// Holds information about a physical or virtual campus
public class Campus {
  private String name;

  public Campus (String name) {
    setName(name);
  }

  public String getName() {
    return this.name;
  }

  @Override
  public String toString() {
    return getName();
  }

  private void setName(String name) { this.name = name; }
}
