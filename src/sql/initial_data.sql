INSERT OR IGNORE INTO school (id, name)
VALUES (1, 'TAMK');

INSERT OR IGNORE INTO teacher (id, firstName, lastName, address, phoneNumber, field, salary)
VALUES (1, "DEMO", "TEACHER", "Some address 1", "050 123462", "CS", 4500);

INSERT OR IGNORE INTO student (id, firstName, lastName, address, phoneNumber)
VALUES (1, "EXAMPLE", "STUDENT", "Another address 2", "010 5615135");

INSERT OR IGNORE INTO student (id, firstName, lastName, address, phoneNumber)
VALUES (2, "Some", "Guy", "Another address 3", "040 56456145");

INSERT OR IGNORE INTO program (id, name, school_id)
VALUES (1, "Default program", 1);

INSERT OR IGNORE INTO program_student (program_id, student_id)
VALUES (1, 1);
