package com.assignment_one;

public class Lecturer {
  private static String firstName = "";
  private static String lastName = "";
  private static int idNumber = 0;
  private static Campus[] campuses;

  public Lecturer(String firstName, String lastName, int idNumber) {
    firstName = firstName;
    lastName = lastName;
    idNumber = idNumber;
  }

  // getters
  public String getName() {
    // todo look up string concatenation
    return firstName + lastName;
  }
}

