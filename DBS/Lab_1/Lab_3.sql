-- 1. UNION ALL: Courses that ran in Fall 2009 or Spring 2010
SELECT course_id, sec_id, semester, year
FROM section 
WHERE semester = 'Fall' AND year = 2009
UNION ALL
SELECT course_id, sec_id, semester, year
FROM section 
WHERE semester = 'Spring' AND year = 2010;

-- 2. INTERSECT ALL: Courses that ran in Fall 2009 AND Spring 2010
SELECT course_id 
FROM section 
WHERE semester = 'Fall' AND year = 2009
INTERSECT ALL
SELECT course_id 
FROM section 
WHERE semester = 'Spring' AND year = 2010;

-- 3. MINUS: Courses in Fall 2009 but NOT in Spring 2010
SELECT course_id 
FROM section 
WHERE semester = 'Fall' AND year = 2009
MINUS
SELECT course_id 
FROM section 
WHERE semester = 'Spring' AND year = 2010;

-- 4. NULL values: Course with NO student registrations
SELECT c.course_id, c.title
FROM course c
WHERE NOT EXISTS (
    SELECT 1 
    FROM section s 
    JOIN takes t ON s.course_id = t.course_id 
                 AND s.sec_id = t.sec_id 
                 AND s.semester = t.semester 
                 AND s.year = t.year
    WHERE s.course_id = c.course_id
);

-- 5. Set Membership (IN): Courses offered in Fall 2009 AND Spring 2010
SELECT DISTINCT s1.course_id
FROM section s1
WHERE s1.semester = 'Fall' AND s1.year = 2009
AND s1.course_id IN (
    SELECT course_id 
    FROM section 
    WHERE semester = 'Spring' AND year = 2010
);

-- 6. Total students for instructor ID 10101
SELECT COUNT(DISTINCT s_id) AS total_students
FROM takes t
WHERE EXISTS (
    SELECT 1 
    FROM teaches te 
    WHERE te.course_id = t.course_id 
    AND te.ID = '10101'
);

-- 7. Set Membership (NOT IN): Courses Fall 2009 but NOT Spring 2010
SELECT course_id 
FROM section 
WHERE semester = 'Fall' AND year = 2009
AND course_id NOT IN (
    SELECT course_id 
    FROM section 
    WHERE semester = 'Spring' AND year = 2010
);

-- 8. Students with same name as instructors
SELECT DISTINCT s.name
FROM student s
WHERE s.name IN (
    SELECT i.name 
    FROM instructor i
);

-- 9. Salary > SOME Biology instructor
SELECT name 
FROM instructor 
WHERE salary > SOME (
    SELECT salary 
    FROM instructor 
    WHERE dept_name = 'Biology'
);

-- 10. Salary > ALL Biology instructors
SELECT name 
FROM instructor 
WHERE salary > ALL (
    SELECT salary 
    FROM instructor 
    WHERE dept_name = 'Biology'
);

-- 11. Departments with highest average salary
SELECT dept_name 
FROM instructor 
GROUP BY dept_name 
HAVING AVG(salary) >= ALL (
    SELECT AVG(salary) 
    FROM instructor 
    GROUP BY dept_name
);

-- 12. Departments with budget < avg instructor salary
SELECT dept_name 
FROM department 
WHERE budget < (
    SELECT AVG(salary) 
    FROM instructor
);

-- 13. EXISTS: Courses taught in both Fall 2009 and Spring 2010
SELECT DISTINCT s1.course_id
FROM section s1
WHERE s1.semester = 'Fall' AND s1.year = 2009
AND EXISTS (
    SELECT 1 
    FROM section s2 
    WHERE s2.course_id = s1.course_id 
    AND s2.semester = 'Spring' 
    AND s2.year = 2010
);

-- 14. NOT EXISTS: Students who took ALL Biology courses
SELECT s.s_id, s.name
FROM student s
WHERE NOT EXISTS (
    SELECT c.course_id 
    FROM course c
    WHERE c.dept_name = 'Biology'
    AND NOT EXISTS (
        SELECT 1 
        FROM takes t 
        WHERE t.s_id = s.s_id 
        AND t.course_id = c.course_id
    )
);

-- 15. UNIQUE: Courses offered at most once in 2009
SELECT DISTINCT course_id
FROM section 
WHERE year = 2009
GROUP BY course_id
HAVING COUNT(*) <= 1;

-- 16. Students with >=2 CSE courses
SELECT s_id
FROM takes 
WHERE course_id IN (
    SELECT course_id 
    FROM course 
    WHERE dept_name = 'Comp. Sci.'
)
GROUP BY s_id 
HAVING COUNT(DISTINCT course_id) >= 2;

-- 17. Subquery in FROM: Avg salary where dept avg > 42000
SELECT AVG(dept_avg_salary) AS avg_of_high_avgs
FROM (
    SELECT dept_name, AVG(salary) AS dept_avg_salary
    FROM instructor 
    GROUP BY dept_name 
    HAVING AVG(salary) > 42000
) high_salary_depts;

-- 18. CREATE VIEW: all_courses (Physics Fall 2009)
CREATE VIEW all_courses AS
SELECT s.course_id, s.sec_id, s.semester, s.year, 
       s.building, s.room_number
FROM section s
JOIN course c ON s.course_id = c.course_id
WHERE c.dept_name = 'Physics' 
  AND s.semester = 'Fall' 
  AND s.year = 2009;

-- 19. SELECT from all_courses view
SELECT * FROM all_courses;

-- 20. CREATE VIEW: department_total_salary
CREATE VIEW department_total_salary AS
SELECT d.dept_name, COALESCE(SUM(i.salary), 0) AS total_salary
FROM department d
LEFT JOIN instructor i ON d.dept_name = i.dept_name
GROUP BY d.dept_name;
