import java.util.ArrayList;
import java.util.Locale;
import java.util.Scanner;
import java.util.stream.Collectors;

public class LibraryAction implements Action {
  public static Scanner input = new Scanner(System.in);
  public static ArrayList<Record> records;
  protected static Record activeItem;

  protected ArrayList<LibraryAction> actions = new ArrayList<>();
  private String key;

  public LibraryAction(String key) {
    this.key = key;
  }

  public String getNextAction() {
    String action = LibraryAction.input.next();
    return action.toLowerCase(Locale.ROOT);
  }

  public void call() {}

  public void addAction(LibraryAction action) {
    actions.add(action);
  }

  public String getKey() {
    return this.key;
  }

  public void evaluateAction(String action) {
    try {
    LibraryAction nextAction = actions.stream().filter(a -> a.getKey().equals(action)).findFirst().orElseThrow(Exception::new);
    nextAction.call();
    } catch(Exception e) {
      System.out.println("\n\nSorry, that command is not supported. Please try again.\n\n");
      call();
    }
  }

  public ArrayList<Record> findRecords(String phrase) {
    return records.stream()
            .filter(record -> record.getTitle().toLowerCase().contains(phrase.toLowerCase()))
            .collect(Collectors.toCollection(ArrayList::new));
  }


  public Record findRecord(Integer ID) {
    return records.stream()
            .filter(record -> record.getID().equals(ID))
            .findFirst()
            .orElse(null);
  }
}
