import java.util.ArrayList;
import java.util.stream.Collectors;

public class PhraseSearch extends LibraryAction implements Action {
  public PhraseSearch(String key) {
    super(key);
  }

  public void call() {
    System.out.println("Enter a phrase, or enter 'search' to go back");
    evaluateAction(getNextAction());
  }

  public void evaluateAction(String action) {
    if (action.equals("search")) {
      super.evaluateAction(action);
      return;
    }

    ArrayList<Record> records = findRecords(action);
    printResults(records);

    if (records.size() == 0) {
      System.out.println("No results found");
      this.call();
      return;
    }

    System.out.println("Enter the item number to select the item. Otherwise, type any phrase to search again");
    String nextAction = getNextAction();

    try {
      int index = Integer.parseInt(nextAction);
      if (index < 1 || index > records.size()) { throw new ArrayIndexOutOfBoundsException("Index selection out of bounds"); }

      LibraryAction.activeItem = records.get(index - 1);
      super.evaluateAction("select");
    } catch(NumberFormatException error) {
      this.evaluateAction(nextAction);
    } catch(ArrayIndexOutOfBoundsException error) {
      System.out.println("Your selection was invalid, please try again");
      this.call();
    }
  }

  private void printResults(ArrayList<Record> records) {
    int i = 0;
    for (Record record : records) {
      System.out.printf("%s) %s\n", i + 1, record);
      i++;
    }
  }

}
