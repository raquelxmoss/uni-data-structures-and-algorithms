public class Search extends LibraryAction {
  public Search(String key) {
    super(key);
  }

  public void call() {
    System.out.println("\n");
    System.out.println("Enter 'quit' to quit");
    System.out.println("Enter 'sort' to sort (first by average rating, then by ID) and display all items");
    System.out.println("Enter 'id' to search by id, or 'title' to search by title");
    evaluateAction(getNextAction());
  }
}
