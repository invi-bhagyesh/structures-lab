-- 1. Create the employee table with emp_no, emp_name, emp_address columns
CREATE TABLE employee (
    emp_no INT PRIMARY KEY,
    emp_name VARCHAR(50),
    emp_address VARCHAR(100)
);

-- 2. Insert five employees information
INSERT INTO employee (emp_no, emp_name, emp_address) VALUES
(1, 'John Doe', 'MANIPAL'),
(2, 'Jane Smith', 'MANGALORE'),
(3, 'Bob Johnson', 'MANIPAL'),
(4, 'Alice Brown', 'MANGALORE'),
(5, 'Charlie Wilson', 'BANGALORE');

-- 3. Display names of all employees
SELECT emp_name FROM employee;

-- 4. Display all employees from 'MANIPAL'
SELECT * FROM employee WHERE emp_address = 'MANIPAL';

-- 5. Add a column named salary to employee table
ALTER TABLE employee ADD COLUMN salary DECIMAL(10,2);

-- 6. Assign salary for all employees
UPDATE employee SET salary = 50000 WHERE emp_no = 1;
UPDATE employee SET salary = 45000 WHERE emp_no = 2;
UPDATE employee SET salary = 55000 WHERE emp_no = 3;
UPDATE employee SET salary = 48000 WHERE emp_no = 4;
UPDATE employee SET salary = 60000 WHERE emp_no = 5;

-- 7. View the structure of the table employee using DESCRIBE
DESCRIBE employee;

-- 8. Delete all employees from 'MANGALORE'
DELETE FROM employee WHERE emp_address = 'MANGALORE';

-- 9. Rename employee table as employee1
RENAME TABLE employee TO employee1;

-- 10. Drop the table employee1
DROP TABLE employee1;
                               
