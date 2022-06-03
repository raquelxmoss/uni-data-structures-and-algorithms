public interface Action {
  void call();
  void evaluateAction(String action);
  String getNextAction();
}
