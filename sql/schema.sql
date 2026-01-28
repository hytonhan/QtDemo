CREATE TABLE IF NOT EXISTS school (
   id INTEGER PRIMARY KEY AUTOINCREMENT,
   name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS program (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    school_id INTEGER NOT NULL,
    name TEXT NOT NULL,
    FOREIGN KEY (school_id) REFERENCES school(id)
);

CREATE TABLE IF NOT EXISTS teacher (
    id INTEGER PRIMARY KEY,
    firstName TEXT NOT NULL,
    lastName TEXT NOT NULL,
    address TEXT,
    phoneNumber TEXT,
    field TEXT NOT NULL,
    salary REAL NOT NULL
);

CREATE TABLE IF NOT EXISTS student (
    id INTEGER PRIMARY KEY,
    firstName TEXT NOT NULL,
    lastName TEXT NOT NULL,
    address TEXT,
    phoneNumber TEXT
);

CREATE TABLE IF NOT EXISTS program_teacher (
    program_id INTEGER NOT NULL,
    teacher_id INTEGER NOT NULL,
    PRIMARY KEY (program_id, teacher_id),
    FOREIGN KEY (program_id) REFERENCES program(id) ON DELETE CASCADE,
    FOREIGN KEY (teacher_id) REFERENCES teacher(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS program_student (
    program_id INTEGER NOT NULL,
    student_id INTEGER NOT NULL,
    PRIMARY KEY (program_id, student_id),
    FOREIGN KEY (program_id) REFERENCES program(id) ON DELETE CASCADE,
    FOREIGN KEY (student_id) REFERENCES student(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS schema_version (
    version INTEGER NOT NULL
);
