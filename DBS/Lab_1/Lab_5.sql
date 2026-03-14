-- 1. Retrieve the birth date and address of the employee(s) whose name is ‘John B. Smith’.
SELECT Bdate, Address
FROM EMPLOYEE
WHERE Fname = 'John' AND Minit = 'B' AND Lname = 'Smith';


-- Retrieve the name and address of all employees who work for the ‘Research’ department.
SELECT E.Fname, E.Lname, E.Address
FROM EMPLOYEE E
JOIN DEPARTMENT D
ON E.Dno = D.Dnumber
WHERE D.Dname = 'Research';



-- 2. For every project located in ‘Stanford’, list the project number,
-- the controlling department number, and the department manager’s
-- last name, address, and birth date.
SELECT P.Pnumber, P.Dnum, E.Lname, E.Address, E.Bdate
FROM PROJECT P
JOIN DEPARTMENT D
ON P.Dnum = D.Dnumber
JOIN EMPLOYEE E
ON D.Mgr_ssn = E.Ssn
WHERE P.Plocation = 'Stanford';



-- 3. For each employee, retrieve the employee’s first and last name
-- and the first and last name of his or her immediate supervisor.
SELECT E.Fname AS Employee_FirstName,
       E.Lname AS Employee_LastName,
       S.Fname AS Supervisor_FirstName,
       S.Lname AS Supervisor_LastName
FROM EMPLOYEE E
LEFT JOIN EMPLOYEE S
ON E.Super_ssn = S.Ssn;



-- 4. Make a list of all project numbers for projects that involve an employee
-- whose last name is ‘Smith’, either as a worker or as a manager of the
-- department that controls the project.

-- Case 1: Smith works on the project
SELECT DISTINCT Pno
FROM WORKS_ON W
JOIN EMPLOYEE E
ON W.Essn = E.Ssn
WHERE E.Lname = 'Smith'

UNION

-- Case 2: Smith manages the department controlling the project
SELECT P.Pnumber
FROM PROJECT P
JOIN DEPARTMENT D
ON P.Dnum = D.Dnumber
JOIN EMPLOYEE E
ON D.Mgr_ssn = E.Ssn
WHERE E.Lname = 'Smith';



-- 5. Show the resulting salaries if every employee working on the
-- ‘ProductX’ project is given a 10 percent raise.
SELECT E.Fname, E.Lname, E.Salary * 1.10 AS Increased_Salary
FROM EMPLOYEE E
JOIN WORKS_ON W
ON E.Ssn = W.Essn
JOIN PROJECT P
ON W.Pno = P.Pnumber
WHERE P.Pname = 'ProductX';



-- 6. Retrieve a list of employees and the projects they are working on,
-- ordered by department and, within each department,
-- ordered alphabetically by last name then first name.
SELECT E.Fname, E.Lname, P.Pname, E.Dno
FROM EMPLOYEE E
JOIN WORKS_ON W
ON E.Ssn = W.Essn
JOIN PROJECT P
ON W.Pno = P.Pnumber
ORDER BY E.Dno, E.Lname, E.Fname;



-- 7. Retrieve the name of each employee who has a dependent with the
-- same first name and is the same sex as the employee.
SELECT E.Fname, E.Lname
FROM EMPLOYEE E
JOIN DEPENDENT D
ON E.Ssn = D.Essn
WHERE E.Fname = D.Dependent_name
AND E.Sex = D.Sex;



-- 8. Retrieve the names of employees who have no dependents.
SELECT Fname, Lname
FROM EMPLOYEE
WHERE Ssn NOT IN (
    SELECT Essn FROM DEPENDENT
);



-- 9. List the names of managers who have at least one dependent.
SELECT E.Fname, E.Lname
FROM EMPLOYEE E
JOIN DEPARTMENT D
ON E.Ssn = D.Mgr_ssn
WHERE E.Ssn IN (
    SELECT Essn FROM DEPENDENT
);



-- 10. Find the sum of the salaries of all employees,
-- the maximum salary, the minimum salary, and the average salary.
SELECT SUM(Salary) AS Total_Salary,
       MAX(Salary) AS Maximum_Salary,
       MIN(Salary) AS Minimum_Salary,
       AVG(Salary) AS Average_Salary
FROM EMPLOYEE;



-- 11. For each project, retrieve the project number,
-- the project name, and the number of employees who work on that project.
SELECT P.Pnumber, P.Pname, COUNT(W.Essn) AS Number_of_Employees
FROM PROJECT P
LEFT JOIN WORKS_ON W
ON P.Pnumber = W.Pno
GROUP BY P.Pnumber, P.Pname;



-- 12. For each project on which more than two employees work,
-- retrieve the project number, the project name,
-- and the number of employees who work on the project.
SELECT P.Pnumber, P.Pname, COUNT(W.Essn) AS Number_of_Employees
FROM PROJECT P
JOIN WORKS_ON W
ON P.Pnumber = W.Pno
GROUP BY P.Pnumber, P.Pname
HAVING COUNT(W.Essn) > 2;



-- 13. For each department that has more than five employees,
-- retrieve the department number and the number of its employees
-- who are making more than 40,000.
SELECT Dno, COUNT(*) AS Employees_Above_40000
FROM EMPLOYEE
WHERE Salary > 40000
GROUP BY Dno
HAVING COUNT(*) > 5;
