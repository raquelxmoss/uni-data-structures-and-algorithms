import java.text.SimpleDateFormat;

public class BorrowItem extends LibraryAction implements Action {
  public BorrowItem(String key) {
    super(key);
  }

  public void call() {
    Record selectedItem = LibraryAction.activeItem;
    try {
      selectedItem.borrowItem();
    } catch (Exception e) {
      System.out.println(e.getMessage());
      evaluateAction("select");
      return;
    }

    SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy");
    String date = formatter.format(selectedItem.getDueDate());
    System.out.printf("The new due date is: %s\n", date);

    evaluateAction("select");
  }
}
