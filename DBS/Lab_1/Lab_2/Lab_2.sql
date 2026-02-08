
-- Q1: Create Employee table with required constraints
CREATE TABLE Employee (
    EmpNo NUMBER,
    EmpName VARCHAR2(30) NOT NULL,
    Gender CHAR(1) NOT NULL,
    Salary NUMBER NOT NULL,
    Address VARCHAR2(50) NOT NULL,
    DNo NUMBER,
    CONSTRAINT pk_employee PRIMARY KEY (EmpNo),
    CONSTRAINT chk_gender CHECK (Gender IN ('M','F'))
);
-- Q2: Create Department table with primary key and candidate key
CREATE TABLE Department (
    DeptNo NUMBER,
    DeptName VARCHAR2(30),
    Location VARCHAR2(30),
    CONSTRAINT pk_department PRIMARY KEY (DeptNo),
    CONSTRAINT uq_department UNIQUE (DeptName)
);
-- Q3: Make DNo a foreign key referencing Department
ALTER TABLE Employee
ADD CONSTRAINT fk_emp_dept
FOREIGN KEY (DNo) REFERENCES Department(DeptNo);
-- Q4: Insert valid tuples
INSERT INTO Department VALUES (1, 'CSE', 'Block A');
INSERT INTO Department VALUES (2, 'ECE', 'Block B');

INSERT INTO Employee VALUES (101, 'Alice', 'F', 30000, 'Bangalore', 1);
INSERT INTO Employee VALUES (102, 'Bob', 'M', 35000, 'Chennai', 2);
-- Q5: Insert tuples violating constraints

-- Violates primary key
INSERT INTO Department VALUES (1, 'MECH', 'Block C');

-- Violates check constraint
INSERT INTO Employee VALUES (103, 'Charlie', 'X', 25000, 'Delhi', 1);

-- Violates NOT NULL
INSERT INTO Employee VALUES (104, NULL, 'M', 20000, 'Mumbai', 1);

-- Violates foreign key
INSERT INTO Employee VALUES (105, 'David', 'M', 28000, 'Pune', 10);

-- Q6: Try deleting department with existing employees
DELETE FROM Department WHERE DeptNo = 1;

-- Q7: Modify foreign key with ON DELETE CASCADE
ALTER TABLE Employee DROP CONSTRAINT fk_emp_dept;

ALTER TABLE Employee
ADD CONSTRAINT fk_emp_dept
FOREIGN KEY (DNo) REFERENCES Department(DeptNo)
ON DELETE CASCADE;

-- Q8: Named constraint to set default salary to 10000
ALTER TABLE Employee
MODIFY Salary DEFAULT 10000;

-- Test default constraint
INSERT INTO Employee (EmpNo, EmpName, Gender, Address, DNo)
VALUES (106, 'Eva', 'F', 'Hyderabad', 2);

-- Q9: List all students with names and department names
SELECT name, dept_name
FROM Student;

-- Q10: List all instructors in CSE department
SELECT name
FROM Instructor
WHERE dept_name = 'CSE';

-- Q11: Courses in CSE department with 3 credits
SELECT title
FROM Course
WHERE dept_name = 'CSE'
AND credits = 3;
-- Q12: Courses registered by student with ID 12345
SELECT c.course_id, c.title
FROM Course c, Takes t
WHERE c.course_id = t.course_id
AND t.ID = 12345;


-- Q13: Instructors with salary between 40000 and 90000
SELECT name
FROM Instructor
WHERE salary BETWEEN 40000 AND 90000;

-- Q14: Instructors who have never taught a course
SELECT i.ID
FROM Instructor i
WHERE NOT EXISTS (
    SELECT *
    FROM Teaches t
    WHERE t.ID = i.ID
);

-- Q15: Students who attended classes in room-number 303
SELECT s.name, c.title, sec.year
FROM Student s, Takes t, Course c, Section sec
WHERE s.ID = t.ID
AND t.course_id = sec.course_id
AND c.course_id = sec.course_id
AND sec.room_number = 303;

-- Q16: Students who opted courses in 2015 with alias
SELECT s.name, c.course_id, c.title AS c_name
FROM Student s, Course c, Takes t
WHERE s.ID = t.ID
AND c.course_id = t.course_id
AND t.year = 2015;

-- Q17: Instructors with salary greater than at least one CSE instructor
SELECT name, salary AS inst_salary
FROM Instructor
WHERE salary > ANY (
    SELECT salary
    FROM Instructor
    WHERE dept_name = 'CSE'
);

-- Q18: Instructors whose department name contains 'ch'
SELECT name
FROM Instructor
WHERE dept_name LIKE '%ch%';

-- Q19: Student names and length of names
SELECT name, LENGTH(name)
FROM Student;

-- Q20: Department names and 3 characters from 3rd position
SELECT dept_name, SUBSTR(dept_name, 3, 3)
FROM Department;

-- Q21: Instructor names in upper case
SELECT UPPER(name)
FROM Instructor;

-- Q22: Replace NULL with 0
SELECT NVL(salary, 0)
FROM Instructor;

-- Q23: Salary and salary/3 rounded to nearest hundred
SELECT salary, ROUND(salary/3, -2)
FROM Instructor;

-- Q24: Add DOB column
ALTER TABLE Employee
ADD DOB DATE;

-- Insert DOB values
UPDATE Employee SET DOB = TO_DATE('10-05-2000','DD-MM-YYYY') WHERE EmpNo = 101;
UPDATE Employee SET DOB = TO_DATE('15-08-1999','DD-MM-YYYY') WHERE EmpNo = 102;

-- Q24(a): DD-MON-YYYY
SELECT EmpName, TO_CHAR(DOB, 'DD-MON-YYYY')
FROM Employee;

-- Q24(b): DD-MON-YY
SELECT EmpName, TO_CHAR(DOB, 'DD-MON-YY')
FROM Employee;

-- Q24(c): DD-MM-YY
SELECT EmpName, TO_CHAR(DOB, 'DD-MM-YY')
FROM Employee;

-- Q25(a): YEAR (uppercase)
SELECT EmpName, TO_CHAR(DOB, 'YEAR')
FROM Employee;

-- Q25(b): Year (capitalized)
SELECT EmpName, INITCAP(TO_CHAR(DOB, 'YEAR'))
FROM Employee;

-- Q25(c): year (lowercase)
SELECT EmpName, LOWER(TO_CHAR(DOB, 'YEAR'))
FROM Employee;
