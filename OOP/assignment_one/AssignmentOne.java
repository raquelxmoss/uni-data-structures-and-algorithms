package com.assignment_one;

public class AssignmentOne {
  private static String schoolName = "School of Mathematical and Computational Sciences";
  private static School school;

  public static void main(String[] args) {
    // todo does this go in constructor
    school = new School(schoolName);
    displayInfo();
    taskOne();
    taskTwo();
    taskThree();
    taskFour();
    taskFive();
    taskSix();
    taskSeven();
    taskEight();
  }

  private static void displayInfo() {
    System.out.println("**************************************");
    System.out.println("Assignment 1, 159.234 Semester 1 2022");
    System.out.println("Submitted by: Mouse, Mickey 12345678");
    System.out.println("My Major at Massey: Computer Science");
    System.out.println("**************************************");
    System.out.println();
  }

  private static void taskOne() {
    System.out.println("---------------- Task 1 ----------------");
    System.out.println(school.getName());
    System.out.println();
  }

  private static void taskTwo() {
    System.out.println("---------------- Task 2 ----------------");
    System.out.println();
  }

  private static void taskThree() {
    System.out.println("---------------- Task 3 ----------------");
    System.out.println();
  }

  private static void taskFour() {
    System.out.println("---------------- Task 4 ----------------");
    System.out.println();
  }

  private static void taskFive() {
    System.out.println("---------------- Task 5 ----------------");
    System.out.println();
  }

  private static void taskSix() {
    System.out.println("---------------- Task 6 ----------------");
    System.out.println();
  }

  private static void taskSeven() {
    System.out.println("---------------- Task 7 ----------------");
    System.out.println();
  }

  private static void taskEight() {
    System.out.println("---------------- Task 8 ----------------");
    System.out.println();
  }
}

