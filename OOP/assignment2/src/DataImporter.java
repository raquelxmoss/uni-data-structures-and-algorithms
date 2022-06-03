import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class DataImporter {
  private ArrayList<Record> records = new ArrayList<>();
  private String pathname;

  public DataImporter(String pathname) {
    this.pathname = pathname;
  }

  public ArrayList<Record> call() {
    try (Scanner scanner = new Scanner(new File(pathname))) {
      while (scanner.hasNextLine()) {
        records.add(createRecord(scanner.nextLine()));
      }
    } catch (FileNotFoundException e) {
      e.printStackTrace();
    }

    return this.records;
  }

  private Record createRecord(String line) {
    String[] values = line.split(",");
    switch (values[0]) {
      case "Movie":
        return new Movie(Integer.parseInt(values[1]),
                values[2],
                Integer.parseInt(values[3]),
                values[4],
                7);
      case "Book":
        return new Book(Integer.parseInt(values[1]),
                values[2],
                Integer.parseInt(values[3]),
                values[4],
                Integer.parseInt(values[5]),
                28);
      case "Journal":
        return new Journal(Integer.parseInt(values[1]),
                values[2],
                Integer.parseInt(values[3]),
                Integer.parseInt(values[4]),
                Integer.parseInt(values[5]),
                14);
      default:
        throw new IllegalStateException("Unexpected value: " + values[0]);
    }
  }
}
