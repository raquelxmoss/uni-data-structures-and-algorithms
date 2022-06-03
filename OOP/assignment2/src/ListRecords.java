public class ListRecords extends LibraryAction {
  public ListRecords(String key) {
    super(key);
  }

  public void call() {
    records.forEach(System.out::println);
    super.evaluateAction("search");
  }
}