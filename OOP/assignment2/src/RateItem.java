public class RateItem extends LibraryAction implements Action {
  public RateItem(String key) {
    super(key);
  }

  public void call() {
    Record selectedItem = LibraryAction.activeItem;

    System.out.println("Please enter your rating (0 - 10)");

    try {
      selectedItem.rateItem(Integer.parseInt(getNextAction()));
      System.out.printf("The item's new average rating is: %.2f\n", selectedItem.getAverageRating());
      evaluateAction("select");
    } catch (Exception error) {
      call();
    }
  }
}
