public class Book extends Record {
  private String author;
  private Integer numberOfPages;

  public Book(Integer ID, String title, Integer year, String author, Integer numberOfPages, Integer maxBorrowingPeriod) {
    super(ID, title, year, maxBorrowingPeriod);
    this.author = author;
    this.numberOfPages = numberOfPages;
  }

  public String displayDetails() {
    return super.displayDetails() + String.format("Author: %s\nNumber of pages: %s\nMax number of days for borrowing: %s\n",
            this.getAuthor(),
            this.getNumberOfPages(),
            this.getMaxBorrowingPeriod());
  }

  private Integer getNumberOfPages() {
    return this.numberOfPages;
  }

  private String getAuthor() {
    return this.author;
  }
}