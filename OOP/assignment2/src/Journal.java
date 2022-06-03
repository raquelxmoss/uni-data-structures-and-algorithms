public class Journal extends Record {
  private Integer volume;
  private Integer number;

  public Journal(Integer ID, String title, Integer year, Integer volume, Integer number, Integer maxBorrowingPeriod) {
    super(ID, title, year, maxBorrowingPeriod);
    setVolume(volume);
    setNumber(number);
  }

  public String displayDetails() {
    return super.displayDetails() + String.format("Volume: %s\nNumber: %s\nMax number of days for borrowing: %s\n",
            this.getVolume(),
            this.getNumber(),
            this.getMaxBorrowingPeriod());
  }

  private Integer getVolume() {
    return this.volume;
  }

  private void setVolume(Integer volume) {
    this.volume = volume;
  }

  private Integer getNumber() {
    return this.number;
  }

  private void setNumber(Integer number) {
    this.number = number;
  }
}