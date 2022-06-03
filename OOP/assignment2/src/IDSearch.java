public class IDSearch extends LibraryAction implements Action {
  public IDSearch(String key) {
    super(key);
  }

  public void call() {
    System.out.println("Enter an ID, or enter 'search' to go back");
    evaluateAction(getNextAction());
  }

  public void evaluateAction(String action) {
    try {
      Integer recordID = Integer.parseInt(action);
      Record result = performSearch(recordID);

      if (result != null) {
        System.out.println(result);
        System.out.println("Enter 'select' to select this item, or enter 'id' to search for another item.");
      } else {
        System.out.println("No record found. Enter 'id' to search for another item.");
      }

      super.evaluateAction(getNextAction());
    } catch(NumberFormatException error) {
      super.evaluateAction(action);
    }
  }

  private Record performSearch(Integer recordID) {
    Record record = findRecord(recordID);
    activeItem = record;
    return record;
  }
}
