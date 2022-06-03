import java.util.Calendar;
import java.util.Date;

public abstract class Record {
  private Integer ID;
  private String title;
  private Integer year;
  private double averageRating = 0.0;
  private Integer numberOfReviews = 0;
  private Date dueDate;
  private Integer maxBorrowingPeriod;
  private Boolean borrowed = false;

  public Record(Integer ID, String title, Integer year, Integer maxBorrowingPeriod) {
    setID(ID);
    setTitle(title);
    setYear(year);
    setMaxBorrowingPeriod(maxBorrowingPeriod);
  }

  @Override
  public String toString() {
    return String.format("ID: %-4s  Type: %-8s  Title: %s", this.getID(), this.getClass().getName(), this.getTitle());
  }

  public String displayWithRating() {
    return String.format("Average rating: %-8s Number of reviewers: %-8s", this.getAverageRating(), this.getNumberOfReviews()) + this;
  }

  public String displayDetails() {
    return String.format("Type: %s\nTitle: %s\nID: %s\nYear: %s\nAverage Rating: %.2f\nNumber of Reviewers: %s\nStatus: %s\n",
            this.getClass().getName(),
            this.getTitle(),
            this.getID(),
            this.getYear(),
            this.getAverageRating(),
            this.getNumberOfReviews(),
            this.getStatus()
            );
  }

  protected void setID(Integer ID) {
    this.ID = ID;
  }

  public Integer getID() {
    return this.ID;
  }

  protected void setTitle(String title) {
    this.title = title;
  }

  public String getTitle() {
    return this.title;
  }

  protected void setYear(Integer year) {
    this.year = year;
  }

  public Integer getYear() {
    return this.year;
  }

  protected void setAverageRating(double averageRating) {
    this.averageRating = averageRating;
  }

  public double getAverageRating() {
    return this.averageRating;
  }

  protected void incrementNumberOfReviews() {
    this.numberOfReviews++;
  }

  public Integer getNumberOfReviews() {
    return this.numberOfReviews;
  }

  public boolean isBorrowed() { return this.borrowed; }

  private void setBorrowed(Boolean bool) { this.borrowed = bool; }

  private String getStatus() {
    return isBorrowed() ? "On loan" : "Available";
  }

  private void setMaxBorrowingPeriod(Integer period) { this.maxBorrowingPeriod = period; }

  protected Integer getMaxBorrowingPeriod() { return this.maxBorrowingPeriod; }

  private void setDueDate(Date date) { this.dueDate = date; }

  public Date getDueDate() { return this.dueDate; }

  public void borrowItem() throws Exception {
    if (isBorrowed()) {
      throw new Exception("This item has already been borrowed");
    }

    Calendar c = Calendar.getInstance();
    c.setTime(new Date());
    c.add(Calendar.DATE, this.maxBorrowingPeriod);
    setDueDate(c.getTime());

    setBorrowed(true);
  }

  public void returnItem() throws Exception {
    if (!isBorrowed()) {
      throw new Exception("This item has not yet been borrowed");
    }

    setBorrowed(false);
    setDueDate(null);
  }

  public void rateItem(Integer rating) throws Exception {
    if (rating < 0 || rating > 10) { throw new Exception("This rating is out of bounds. Please enter a rating between 0 and 10"); }

    this.incrementNumberOfReviews();
    double newAverageRating = (averageRating + rating) / numberOfReviews;
    this.setAverageRating(newAverageRating);
  }
}
