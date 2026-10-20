# DAA Assignment 7: Simple Exam Timetable

If a student takes two courses, those exams cannot share a slot. Model courses
as vertices and shared-student conflicts as edges. Greedy coloring assigns each
course the first slot not already used by a scheduled conflicting course.

## Files
- `ExamScheduler.cpp`: simplified C++ source.
- `input.txt`: sample values.
- `Output.txt`: captured timetable.
- `DAA_Assignment_No_7_Soham_Kulkarni.pdf`: report, without C++ code.

## Compile and Run

```powershell
g++ -std=c++11 ExamScheduler.cpp -o ExamScheduler.exe
.\ExamScheduler.exe
```

## Sample Input

```text
4
DAA DBMS OS CN
4
1 2
1 3
2 3
3 4
```

Four courses have IDs 1=DAA, 2=DBMS, 3=OS, 4=CN. The second 4 is the number
of conflict pairs. Pair `1 2` means DAA and DBMS share a student and need
different slots. Enter every shared-student conflict. Course names are single words.

## Expected Result
| Course | Slot |
| --- | --- |
| DAA | 1 |
| DBMS | 2 |
| OS | 3 |
| CN | 1 |

DAA and CN have no conflict, so they share slot 1. DAA, DBMS and OS all
conflict with one another, requiring three slots in this example. On other
graphs, Greedy may use more slots than necessary; it guarantees validity,
not a general minimum.

## Performance and Scope
Adjacency lists and a fresh used-slot array per course give O(V squared + E)
time and O(V + E) memory. The program accepts up to 5000 courses. Invalid
IDs and self-conflicts are rejected. Repeated pairs are harmless but duplicate
storage. Each course gets an exam slot.

The PDF discusses DSATUR, Welsh-Powell and classroom capacity extensions.
This uploaded simple program focuses on Greedy coloring with manually entered
conflict pairs; it does not infer conflicts from student records or allocate rooms.
