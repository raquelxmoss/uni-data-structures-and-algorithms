public class SelectItem extends LibraryAction implements Action {
  public SelectItem(String key) {
    super(key);
  }

  public void call() {
    Record selectedItem = LibraryAction.activeItem;

    System.out.println("The selected item is:");
    System.out.println(selectedItem.displayDetails());

    String verb;

    if (selectedItem.isBorrowed()) {
      verb = "return";
    } else {
      verb = "borrow";
    }

    System.out.printf("Enter '%s' to %s the item, 'rate' to rate the item, or 'search' to restart\n", verb, verb);

    evaluateAction(getNextAction());
  }
}