# MSMS
(formerly `StudentManagerProgram-SMP--G1`)
> "Manage the database of students!"

---

SHA-1 is used for password hashing/authentication.\
<http://www.zedwood.com/article/cpp-sha1-function>

```
    ============
    SHA-1 in C++
    ============
 
    100% Public Domain.
 
    Original C Code
        -- Steve Reid <steve@edmweb.com>
    Small changes to fit into bglibs
        -- Bruce Guenter <bruce@untroubled.org>
    Translation to simpler C++ Code
        -- Volker Grabsch <vog@notjusthosting.com>
```

---

Code tree:

```
/MSMS/
|
|   main.cpp				main()
|   _FILES_.h				Path to data tree
|
|   Login.cpp				Login facilities
|   Login.h
|   Menu.cpp				Usermenu
|   Menu.h
|
|   Student.cpp				Individual students
|   Student.h
|   Lecturer.cpp			Lecturers
|   Lecturer.h
|   Class.cpp				Classes (list of students)
|   Class.h
|
|   Course.cpp				Courses (list of sessions)
|   Course.h
|   Attendance.cpp			Course attendance lists
|   Attendance.h
|   Score.cpp				Course scoreboards
|   Score.h
|
├───sha1					SHA-1 (used by Login.h)
|       sha1.cpp
|       sha1.h
```

\
Data tree (i.e. where `MSMS` put files in)

```
├───Data
|   ├───Classes
|   |       18CLC1.txt
|   |       18CLC2.txt
|   |
|   ├───Courses
|   |   └───2018
|   |       ├───T1
|   |       └───T2
|   |           └───CTT008
|   |               |   Info.txt
|   |               |
|   |               ├───Tue
|   |               |       Attendance.txt
|   |               |       Score.txt
|   |               |
|   |               └───Wed
|   |                       Attendance.txt
|   |                       Score.txt
|   |
|   ├───Lecturers
|   |       Lecturers.txt
|   |
|   └───Login
|           Admin.txt
|           Lecturer.txt
|           Student.txt
|
└───Import
    ├───Courses
    |       18CLC1 course.csv
    |       18CLC2 course.csv
    |
    ├───Lecturers
    |       Lecturers.csv
    |
    └───Student_Info
            18CLC1.csv
            18CLC2.csv      
```
