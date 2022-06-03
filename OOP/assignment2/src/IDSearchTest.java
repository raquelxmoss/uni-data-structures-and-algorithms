import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

public class IDSearchTest {
  @Before
  public void setUp() {
    DataImporter dataImporter = new DataImporter("library.txt");
    LibraryAction.records = dataImporter.call();
  }

  @After
  public void tearDown() {
    LibraryAction.records = null;
  }

  // Find the record with the matching ID
  @Test
  public void findRecordByIDTest() {
    LibraryAction idSearch = new IDSearch("title");
    Record result = idSearch.findRecord(200);
    assertEquals(result.getID(), new Integer(200));
  }

  // Return null if no matching record found
  @Test
  public void noMatchingRecord() {
    LibraryAction idSearch = new IDSearch("title");
    Record result = idSearch.findRecord(999);
    assertNull(result);
  }
}