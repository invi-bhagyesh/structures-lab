-- 1. Find the number of students in each course.
SELECT course_id, COUNT(*) as num_students
FROM takes 
GROUP BY course_id;

-- 2. Find those departments where the average number of students are greater than 10.
SELECT dept_name 
FROM student
GROUP BY dept_name 
HAVING COUNT(*) > 10;

-- 3. Find the total number of courses in each department.
SELECT dept_name, COUNT(*) as num_courses
FROM course 
GROUP BY dept_name;

-- 4. Find the names and average salaries of all departments whose average salary is greater than 42000.
SELECT dept_name, AVG(salary) as avg_salary
FROM instructor 
GROUP BY dept_name 
HAVING AVG(salary) > 42000;

-- 5. Find the enrolment of each section that was offered in Spring 2009.
SELECT s.course_id, s.sec_id, s.semester, s.year, COUNT(*) as enrollment
FROM section s JOIN takes t ON (s.course_id, s.sec_id, s.semester, s.year) = (t.course_id, t.sec_id, t.semester, t.year)
WHERE s.semester = 'Spring' AND s.year = 2009
GROUP BY s.course_id, s.sec_id, s.semester, s.year;

-- 6. List all the courses with prerequisite courses, then display course id in increasing order.
SELECT c1.course_id, c1.title, c2.course_id as prereq_id
FROM course c1 JOIN prereq ON c1.course_id = prereq.course_id
JOIN course c2 ON prereq.prereq_id = c2.course_id
ORDER BY c1.course_id ASC;

-- 7. Display the details of instructors sorting the salary in decreasing order.
SELECT *
FROM instructor
ORDER BY salary DESC;

-- 8. Find the maximum total salary across the departments.
SELECT MAX(dept_total) as max_dept_salary
FROM (SELECT dept_name, SUM(salary) as dept_total 
      FROM instructor 
      GROUP BY dept_name) dept_salaries;

-- 9. Find the average instructors' salaries of those departments where the average salary is greater than 42000.
SELECT AVG(avg_salary) as overall_avg_salary
FROM (SELECT dept_name, AVG(salary) as avg_salary
      FROM instructor 
      GROUP BY dept_name 
      HAVING AVG(salary) > 42000) high_salary_depts;

-- 10. Find the sections that had the maximum enrolment in Spring 2010
WITH max_enroll AS (
    SELECT MAX(enrollment) as max_count
    FROM (SELECT COUNT(*) as enrollment
          FROM section s JOIN takes t ON (s.course_id, s.sec_id, s.semester, s.year) = (t.course_id, t.sec_id, t.semester, t.year)
          WHERE s.semester = 'Spring' AND s.year = 2010
          GROUP BY s.course_id, s.sec_id, s.semester, s.year) enroll_counts
)
SELECT s.course_id, s.sec_id, s.semester, s.year, COUNT(*) as enrollment
FROM section s JOIN takes t ON (s.course_id, s.sec_id, s.semester, s.year) = (t.course_id, t.sec_id, t.semester, t.year)
WHERE s.semester = 'Spring' AND s.year = 2010
GROUP BY s.course_id, s.sec_id, s.semester, s.year
HAVING COUNT(*) = (SELECT max_count FROM max_enroll);

-- 11. Find the names of all instructors who teach all students that belong to 'CSE' department.
-- (Division query - instructors who teach every CSE student)
SELECT i.name
FROM instructor i
WHERE NOT EXISTS (
    SELECT s.ID
    FROM student s
    WHERE s.dept_name = 'CSE'
    AND NOT EXISTS (
        SELECT t.ID
        FROM teaches t JOIN section sec ON (t.course_id, t.sec_id, t.semester, t.year) = (sec.course_id, sec.sec_id, sec.semester, sec.year)
        WHERE t.ID = i.ID AND t.course_id = sec.course_id AND sec.course_id IN (
            SELECT r.course_id
            FROM student s2 JOIN takes r ON s2.ID = r.ID
            WHERE s2.ID = s.ID
        )
    )
);

-- 12. Find the average salary of those department where the average salary is greater than 50000 and total number of instructors in the department are more than 5.
SELECT AVG(avg_salary) as overall_avg
FROM (SELECT dept_name, AVG(salary) as avg_salary, COUNT(*) as instructor_count
      FROM instructor 
      GROUP BY dept_name 
      HAVING AVG(salary) > 50000 AND COUNT(*) > 5) qualified_depts;

-- 13. Find all departments with the maximum budget. (WITH clause)
WITH dept_budget AS (
    SELECT dept_name, budget,
           MAX(budget) OVER () as max_budget
    FROM department
)
SELECT dept_name, budget
FROM dept_budget
WHERE budget = max_budget;

-- 14. Find all departments where the total salary is greater than the average of the total salary at all departments. (WITH clause)
WITH dept_totals AS (
    SELECT dept_name, SUM(salary) as total_salary
    FROM instructor
    GROUP BY dept_name
),
avg_total_salary AS (
    SELECT AVG(total_salary) as avg_dept_total
    FROM dept_totals
)
SELECT dt.dept_name, dt.total_salary
FROM dept_totals dt, avg_total_salary avg
WHERE dt.total_salary > avg.avg_dept_total;

SAVEPOINT before_transfers;

-- 15. Transfer all the students from CSE department to IT department.
UPDATE student 
SET dept_name = 'IT' 
WHERE dept_name = 'CSE';

-- 16. Increase salaries of instructors whose salary is over $100,000 by 3%, and all others receive a 5% raise
UPDATE instructor 
SET salary = CASE 
    WHEN salary > 100000 THEN salary * 1.03
    ELSE salary * 1.05
END;

-- Undo modifications
ROLLBACK TO SAVEPOINT before_transfers;
