import java.util.ArrayList;
import java.util.Comparator;
import java.util.stream.Collectors;

public class Sort extends LibraryAction implements Action {
  public Sort(String key) {
    super(key);
  }

  public void call() {
    sort();
    super.evaluateAction("search");
  }

  private void sort() {
    ArrayList<Record> sortedRecords = records.stream()
            .sorted(Comparator.comparing(Record::getAverageRating)
            .reversed()
            .thenComparing(Record::getID))
            .collect(Collectors.toCollection(ArrayList::new));

    sortedRecords.forEach(record -> System.out.println(record.displayWithRating()));
  }
}