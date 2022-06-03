import org.junit.*;

import java.util.ArrayList;

import static org.junit.Assert.assertEquals;

public class PhraseSearchTest {
  @Before
  public void setUp() {
    DataImporter dataImporter = new DataImporter("library.txt");
    LibraryAction.records = dataImporter.call();
  }

  @After
  public void tearDown() {
    LibraryAction.records = null;
  }

  @Test
  public void findsRecordByTitle() {
    LibraryAction phraseSearch = new PhraseSearch("title");
    ArrayList<Record> result = phraseSearch.findRecords("Martian");
    assertEquals(result.stream().findFirst().get().getTitle(), "Martian Hairdresser");
  }

  // Any case is accepted and produces the expected result
  @Test
  public void ignoresCase() {
    LibraryAction phraseSearch = new PhraseSearch("title");
    ArrayList<Record> sentenceCase = phraseSearch.findRecords("Martian");
    ArrayList<Record> allCaps = phraseSearch.findRecords("MARTIAN");
    ArrayList<Record> lowerCase = phraseSearch.findRecords("martian");

    assertEquals(sentenceCase.stream().findFirst().get().getTitle(), "Martian Hairdresser");
    assertEquals(allCaps.stream().findFirst().get().getTitle(), "Martian Hairdresser");
    assertEquals(lowerCase.stream().findFirst().get().getTitle(), "Martian Hairdresser");
  }

  // when multiple records match the given phrase, all matching
  // records should be returned
  @Test
  public void multipleRecordsWithSameTitlePhrase() {
    LibraryAction phraseSearch = new PhraseSearch("title");
    ArrayList<Record> result = phraseSearch.findRecords("Lord");
    assertEquals(result.size(), 2);
  }

  // In the case of no results, an empty array is returned.
  @Test
  public void noResultsEmptyArrayList() {
    LibraryAction phraseSearch = new PhraseSearch("title");
    ArrayList<Record> result = phraseSearch.findRecords("Nonsense");
    assertEquals(result.size(), 0);
  }
}