public class ReturnItem extends LibraryAction implements Action {
  public ReturnItem(String key) {
    super(key);
  }

  public void call() {
    Record selectedItem = LibraryAction.activeItem;
    try {
      selectedItem.returnItem();
    } catch (Exception e) {
      System.out.println(e.getMessage());
      evaluateAction("select");
      return;
    }

    System.out.println("The item has been returned, thank you");

    evaluateAction("select");
  }
}
