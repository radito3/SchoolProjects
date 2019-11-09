DROP DATABASE IF EXISTS school;
CREATE DATABASE school DEFAULT CHARACTER SET utf8 DEFAULT COLLATE utf8_general_ci;
USE school;

SET SQL_SAFE_UPDATES = 0;

CREATE TABLE Students(
	Id INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
	Name VARCHAR(150) NOT NULL,
	Num INTEGER NOT NULL,
	ClassNum INTEGER NOT NULL,
	ClassLetter CHAR(1) NOT NULL,
	Birthday DATE,
	EGN CHAR(10)
);

CREATE TABLE Subjects(
	Id INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
	Name VARCHAR(100) NOT NULL
);

CREATE TABLE StudentMarks(
	StudentId INTEGER NOT NULL,
	SubjectId INTEGER NOT NULL,
	ExamDate DATETIME NOT NULL,
	Mark NUMERIC(3,2) NOT NULL,
	
	PRIMARY KEY (StudentId, SubjectId, ExamDate),
	FOREIGN KEY (StudentId) REFERENCES Students(Id) ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY (SubjectId) REFERENCES Subjects(Id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE MarkWords(
	RangeStart NUMERIC(3,2) NOT NULL,
	RangeEnd NUMERIC(3,2) NOT NULL,
	MarkAsWord VARCHAR(15),
	
	PRIMARY KEY(RangeStart, RangeEnd)
);

INSERT INTO Students(Id, Name, Num, ClassNum, ClassLetter, Birthday, EGN) VALUES( 101, 'Зюмбюл Петров', 10, 11, 'а', '1999-02-28', NULL );
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN) VALUES( 'Исидор Иванов', 15, 10, 'б', '2000-02-29', '0042294120' );
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN) VALUES( 'Панчо Лалов', 20, 10, 'б', '2000-05-01', NULL );
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN) VALUES( 'Петраки Ганьов', 20, 10, 'а', '1999-12-25', '9912256301' );
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN) VALUES( 'Александър Момчев', 1, 8, 'а', '2002-06-11', NULL );

INSERT INTO Subjects(Id, Name) VALUES( 11, 'Английски език' );
INSERT INTO Subjects(Name) VALUES( 'Литература' );
INSERT INTO Subjects(Name) VALUES( 'Математика' );
INSERT INTO Subjects(Name) VALUES( 'СУБД' );

INSERT INTO StudentMarks VALUES( 101, 11, '2017-03-03', 6 );
INSERT INTO StudentMarks VALUES( 101, 11, '2017-03-31', 5.50 );
INSERT INTO StudentMarks VALUES( 102, 11, '2017-04-28', 5 );
INSERT INTO StudentMarks VALUES( 103, 12, '2017-04-28', 4 );
INSERT INTO StudentMarks VALUES( 104, 13, '2017-03-03', 5 );
INSERT INTO StudentMarks VALUES( 104, 13, '2017-04-07', 6 );
INSERT INTO StudentMarks VALUES( 104, 11, '2017-04-07', 4.50 );

INSERT INTO MarkWords VALUES( 2, 2.50, 'Слаб' );
INSERT INTO MarkWords VALUES( 2.50, 3.50, 'Среден' );
INSERT INTO MarkWords VALUES( 3.50, 4.50, 'Добър' );
INSERT INTO MarkWords VALUES( 4.50, 5.50, 'Мн. добър' );
INSERT INTO MarkWords VALUES( 5.50, 6, 'Отличен' );



DROP TABLE IF EXISTS H_Students;
CREATE TABLE H_Students (
	UID INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
    BeginDate DATETIME,
    EndDate DATETIME,
    
    Id INTEGER,
	Name VARCHAR(150),
	Num INTEGER,
	ClassNum INTEGER,
	ClassLetter CHAR(1),
	Birthday DATE,
	EGN CHAR(10)
);

DROP TABLE IF EXISTS H_Subjects;
CREATE TABLE H_Subjects(
	UID INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
    BeginDate DATETIME,
    EndDate DATETIME,
    
    Id INTEGER,
	Name VARCHAR(100)
);

DROP TABLE IF EXISTS H_StudentMarks;
CREATE TABLE H_StudentMarks(
	UID INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
    BeginDate DATETIME,
    EndDate DATETIME,
    
    StudentId INTEGER,
	SubjectId INTEGER,
	ExamDate DATETIME,
	Mark NUMERIC(3,2)
);

DROP TRIGGER IF EXISTS H_Student_Insert;
DELIMITER $
CREATE TRIGGER H_Student_Insert AFTER INSERT ON Students FOR EACH ROW
BEGIN 
	INSERT INTO H_Students(Id, Name, Num, ClassNum, ClassLetter, Birthday, EGN, BeginDate)
    VALUES(new.Id, new.Name, new.Num, new.ClassNum, new.ClassLetter, new.Birthday, new.EGN, NOW());
END$
DELIMITER ;

DROP TRIGGER IF EXISTS H_Student_Update;
DELIMITER $
CREATE TRIGGER H_Student_Update	AFTER UPDATE ON Students FOR EACH ROW
BEGIN
	UPDATE H_Students
    SET H_Students.EndDate = NOW()
    WHERE new.Id = H_Students.Id and H_Students.EndDate is NULL;
    
	INSERT INTO H_Students(Id, Name, Num, ClassNum, ClassLetter, Birthday, EGN, BeginDate)
    VALUES(new.Id, new.Name, new.Num, new.ClassNum, new.ClassLetter, new.Birthday, new.EGN, NOW());
END$
DELIMITER ;

DROP TRIGGER IF EXISTS H_Student_Delete;
DELIMITER $
CREATE TRIGGER H_Student_Delete BEFORE DELETE ON Students FOR EACH ROW
BEGIN
	UPDATE H_Students
    SET H_Students.EndDate = NOW()
    WHERE Id = H_Students.Id and H_Students.EndDate is NULL;
END$
DELIMITER ;


DROP TRIGGER IF EXISTS H_Subjects_Insert;
DELIMITER $
CREATE TRIGGER H_Subjects_Insert AFTER INSERT ON Subjects FOR EACH ROW
BEGIN 
	INSERT INTO H_Subjects(Id, Name, BeginDate)
    VALUES(new.Id, new.Name, NOW());
END$
DELIMITER ;

DROP TRIGGER IF EXISTS H_Subjects_Update;
DELIMITER $
CREATE TRIGGER H_Subjects_Update AFTER UPDATE ON Subjects FOR EACH ROW
BEGIN 
	UPDATE H_Subjects
    SET H_Subjects.EndDate = NOW()
    WHERE new.Id = H_Subjects.Id and H_Subjects.EndDate is NULL;
    
    INSERT INTO H_Subjects(Id, Name, BeginDate)
    VALUES(new.Id, new.Name, NOW());
END$
DELIMITER ;

DROP TRIGGER IF EXISTS H_Subjects_Delete;
DELIMITER $
CREATE TRIGGER H_Subjects_Delete BEFORE DELETE ON Subjects FOR EACH ROW
BEGIN
	UPDATE H_Subjects
    SET H_Subjects.EndDate = NOW()
    WHERE Id = H_Subjects.Id and H_Subjects.EndDate is NULL;
END$
DELIMITER ;


DROP TRIGGER IF EXISTS H_StudentMarks_Insert;
DELIMITER $
CREATE TRIGGER H_StudentMarks_Insert AFTER INSERT ON StudentMarks FOR EACH ROW
BEGIN 
	INSERT INTO H_StudentMarks(StudentId, SubjectId, ExamDate, Mark, BeginDate)
    VALUES(new.StudentId, new.SubjectId, new.ExamDate, new.Mark, NOW());
END$
DELIMITER ;

DROP TRIGGER IF EXISTS H_StudentMarks_Update;
DELIMITER $
CREATE TRIGGER H_StudentMarks_Update AFTER UPDATE ON StudentMarks FOR EACH ROW
BEGIN 
	UPDATE H_StudentMarks
    SET H_StudentMarks.EndDate = NOW()
    WHERE new.StudentId = H_StudentMarks.StudentId and H_StudentMarks.EndDate is NULL;
    
    INSERT INTO H_StudentMarks(StudentId, SubjectId, ExamDate, Mark, BeginDate)
    VALUES(new.StudentId, new.SubjectId, new.ExamDate, new.Mark, NOW());
END$
DELIMITER ;

DROP TRIGGER IF EXISTS H_StudentMarks_Delete;
DELIMITER $
CREATE TRIGGER H_StudentMarks_Delete BEFORE DELETE ON StudentMarks FOR EACH ROW
BEGIN
	UPDATE H_StudentMarks
    SET H_StudentMarks.EndDate = NOW()
    WHERE StudentId = H_StudentMarks.StudentId and H_StudentMarks.EndDate is NULL;
END$
DELIMITER ;

	
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN)
VALUES( 'test test', 21, 11, 'b', '1998-12-25', '9812256301' );
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN)
VALUES( 'testing tester', 10, 12, 'v', '1997-12-25', '9712256301' );
INSERT INTO Students(Name, Num, ClassNum, ClassLetter, Birthday, EGN)
VALUES( 'Петраки Ганьов', 20, 10, 'а', '1999-12-25', '9912256301' );


INSERT INTO Subjects(Name) VALUES ('Maths');
INSERT INTO Subjects(Name) VALUES ('Physics');
INSERT INTO Subjects(Name) VALUES ('PE');


INSERT INTO StudentMarks VALUES( 104, 11, '2017-03-03', 5 );
INSERT INTO StudentMarks VALUES( 105, 11, '2017-03-31', 4.50 );
INSERT INTO StudentMarks VALUES( 106, 11, '2017-04-28', 3 );


UPDATE Students 
SET ClassLetter = 'z'
WHERE Name = 'test test';
UPDATE Students 
SET ClassLetter = 'x'
WHERE Name = 'testing tester';
UPDATE Students 
SET ClassLetter = 'y'
WHERE Name = 'Петраки Ганьов';


UPDATE Subjects
SET Name = 'Programming'
WHERE Id = 12;
UPDATE Subjects
SET Name = 'SUBD'
WHERE Id = 13;
UPDATE Subjects
SET Name = 'OOP'
WHERE Id = 14;


UPDATE StudentMarks
SET Mark = 2
WHERE StudentId = 101;
UPDATE StudentMarks
SET Mark = 2
WHERE StudentId = 102;
UPDATE StudentMarks
SET Mark = 2
WHERE StudentId = 103;


DELETE FROM Students
WHERE Id = 101;
DELETE FROM Students
WHERE Id = 102;
DELETE FROM Students
WHERE Id = 103;


DELETE FROM Subjects
Where Id = 11;
DELETE FROM Subjects
Where Id = 12;
DELETE FROM Subjects
Where Id = 13;


DELETE FROM StudentMarks
WHERE StudentId = 101;
DELETE FROM StudentMarks
WHERE StudentId = 102;
DELETE FROM StudentMarks
WHERE StudentId = 104;


INSERT INTO StudentMarks VALUES( 106, 14, '2017-03-03', 5 );  -- t1
SELECT st.Name AS Student_Name, sb.Name AS Subject_Name, hsm.Mark FROM H_StudentMarks AS hsm
INNER JOIN Students AS st ON hsm.StudentId = st.Id
INNER JOIN Subjects AS sb ON hsm.SubjectId = sb.Id
WHERE hsm.StudentId = 106 AND hsm.ExamDate = '2017-03-03';

UPDATE StudentMarks SET Mark = 6 WHERE StudentId = 106;  -- t2
SELECT st.Name AS Student_Name, sb.Name AS Subject_Name, hsm.Mark FROM H_StudentMarks AS hsm
INNER JOIN Students AS st ON hsm.StudentId = st.Id
INNER JOIN Subjects AS sb ON hsm.SubjectId = sb.Id
WHERE hsm.StudentId = 106 AND hsm.ExamDate = '2017-03-03';

UPDATE StudentMarks SET SubjectId = 14 WHERE StudentId = 106;  -- t3
SELECT st.Name AS Student_Name, sb.Name AS Subject_Name, hsm.Mark FROM H_StudentMarks AS hsm
INNER JOIN Students AS st ON hsm.StudentId = st.Id
INNER JOIN Subjects AS sb ON hsm.SubjectId = sb.Id
WHERE hsm.StudentId = 106 AND hsm.ExamDate = '2017-03-03';

UPDATE StudentMarks SET Mark = 3 WHERE StudentId = 106;  -- t4
SELECT st.Name AS Student_Name, sb.Name AS Subject_Name, hsm.Mark FROM H_StudentMarks AS hsm
INNER JOIN Students AS st ON hsm.StudentId = st.Id
INNER JOIN Subjects AS sb ON hsm.SubjectId = sb.Id
WHERE hsm.StudentId = 106 AND hsm.ExamDate = '2017-03-03';

DELETE FROM StudentMarks WHERE StudentId = 106;  -- t5
SELECT st.Name AS Student_Name, sb.Name AS Subject_Name, hsm.Mark FROM H_StudentMarks AS hsm
INNER JOIN Students AS st ON hsm.StudentId = st.Id
INNER JOIN Subjects AS sb ON hsm.SubjectId = sb.Id
WHERE hsm.StudentId = 106 AND hsm.ExamDate = '2017-03-03';
