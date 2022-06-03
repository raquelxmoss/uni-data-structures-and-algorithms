public class Movie extends Record {
  private String director;

  public Movie(Integer ID, String title, Integer year, String director, Integer maxBorrowingPeriod) {
    super(ID, title, year, maxBorrowingPeriod);
    setDirector(director);
  }

  private void setDirector(String director) {
    this.director = director;
  }

  public String getDirector() {
    return this.director;
  }

  public String displayDetails() {
    return super.displayDetails() + String.format("Director: %s\nMax number of days for borrowing: %s\n",
            this.getDirector(),
            this.getMaxBorrowingPeriod());
  }
}
