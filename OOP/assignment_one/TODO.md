# TODO
- [ ] Read in CSVs to populate models
- [ ] Create all the models
- [ ] Print out required printouts
- [ ] Document with jdoc
- [ ] Create UML

## Models

### School
- Name
- Nickname
- has_many: Majors

The School of Mathematical and Computational Sciences (SMCS)

### Campus
- Name [Auckland, Palmerston North, Distance]

### Major
- Name
- Nickname
- has_many: Papers
- offered_at: all campuses

Computer Science (CS)
Information Technology (IT)
Information Systems (IS)
Software Engineering (SE)
and Data Science (DS)

### Paper
- Name
- Number
- has_many: Major
- assessment types: [Test, Assignment, Exam]

### Assessment
- Name [test, assignment, exam]
- Weighting

### Lecturer
- first name
- last name
- ID number

- has_many papers
- campuses: [one of AK/PN, distance]
- min/max papers: 0-4

TODO: figure out paper<->campuses<->lecturer relationships

Draw a class diagram, using UML to show your program design. You need to identify necessary classes, their attributes, and their methods – and then represent classes and their methods with possible associations in your class diagram (you can refer to the class diagram from Lecture 10 of Week 4 for expected details and components).

monkey-patch toString on objects to present in the way required by the task
use javadoc (like yard) to doc things

Task 1: Full name of school
Task 2: All papers’ details (including paper number, name, and majors it belongs to) Task 3: All papers belong to your real major at Massey (such as ‘CS’)
Task 4: All papers that have an exam
Task 5: All papers whose assignments weigh more than 50% in total
Task 6: All paper offerings including paper number, offering mode, and lecturer Task 7: The paper offerings that you teach
Task 8: The lecturer’s name of Auckland offering 159234
