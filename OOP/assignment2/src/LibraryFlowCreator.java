public class LibraryFlowCreator {
  private LibraryAction startingNode;

  public LibraryFlowCreator() {
    LibraryAction list = new ListRecords("list");
    LibraryAction sort = new Sort("sort");
    LibraryAction search = new Search("search");
    LibraryAction idSearch = new IDSearch("id");
    LibraryAction phraseSearch = new PhraseSearch("title");
    LibraryAction selectItem = new SelectItem("select");
    LibraryAction returnItem = new ReturnItem("return");
    LibraryAction rateItem = new RateItem("rate");
    LibraryAction borrowItem = new BorrowItem("borrow");
    LibraryAction quit = new Quit("quit");

    // list
    list.addAction(search);

    // sort
    sort.addAction(search);

    // search
    search.addAction(idSearch);
    search.addAction(phraseSearch);
    search.addAction(quit);
    search.addAction(sort);

    // id_search
    idSearch.addAction(selectItem);
    idSearch.addAction(idSearch);
    idSearch.addAction(search);

    // phrase_search
    phraseSearch.addAction(selectItem);
    phraseSearch.addAction(phraseSearch);
    phraseSearch.addAction(search);

    // select_item
    selectItem.addAction(borrowItem);
    selectItem.addAction(returnItem);
    selectItem.addAction(rateItem);
    selectItem.addAction(search);

    // return
    returnItem.addAction(selectItem);
    returnItem.addAction(search);

    // borrow
    borrowItem.addAction(selectItem);
    borrowItem.addAction(search);

    // rate
    rateItem.addAction(selectItem);
    rateItem.addAction(search);

    this.startingNode = list;
  }

  public LibraryAction call() {
    return startingNode;
  }
}
