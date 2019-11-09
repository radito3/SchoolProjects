DROP DATABASE IF EXISTS Library;
CREATE DATABASE Library;
USE Library;

CREATE TABLE Authors(
    Id INTEGER AUTO_INCREMENT NOT NULL,
    Name VARCHAR(150) NOT NULL UNIQUE,
  
    PRIMARY KEY(Id)
);

CREATE TABLE Books(
    Id INTEGER AUTO_INCREMENT NOT NULL,
    Name VARCHAR(150) NOT NULL UNIQUE,
    ISBN VARCHAR(17) NOT NULL UNIQUE,
    PublishingDate DATE NOT NULL,
    
    PRIMARY KEY(Id)
);

CREATE TABLE BooksAuthorsRef(
    Id INTEGER AUTO_INCREMENT NOT NULL,
    BookId INTEGER NOT NULL,
    AuthorId INTEGER NOT NULL,
    
    PRIMARY KEY(Id),
    FOREIGN KEY (BookId) REFERENCES Books(Id),
    FOREIGN KEY (AuthorId) REFERENCES Authors(Id),
    CONSTRAINT UnqBookAuthors UNIQUE (BookId, AuthorId)
);
    
INSERT INTO
	Authors(Name)
VALUES
	('Kiril Mitov'),
	('Dimitar Nikolov'),
	('George Lucas'),
	('Stefan Diankov'),
	('Aleksandar Petkov'),
	('Stela Stefanova');

INSERT INTO 
	Books(Name, ISBN, PublishingDate) 
VALUES 
	('LOTR', '978-3-16-148410-0', '2004-04-08'),
	('The Phoenix', '978-3-16-148235-0', '1999-06-20'),
	('Star Wars', '978-3-16-263510-0', '1978-10-05'),
	('Harry Potter', '978-3-16-126710-0', '2004-05-10'),
	('SUBD Basics', '978-3-16-149614-0', '2010-12-18'),
	('Cooking For Dummies', '978-3-16-112340-0', '1989-11-10'),
	('Another One', '978-3-16-163410-0', '2004-07-01'),
	('DJ Khaled', '978-3-16-123450-0', '2004-11-20');

INSERT INTO
	BooksAuthorsRef(BookId, AuthorId)
VALUES 
	(1, 2),
	(1, 3),
	(1, 4),
	(2, 2),
	(2, 5),
	(3, 4),
	(4, 5),
	(5, 1),
	(6, 3),
	(7, 1),
	(8, 1),
	(8, 3);

SELECT Books.Name
FROM Books
WHERE Books.PublishingDate >= '2004-01-01' AND Books.PublishingDate <= '2004-12-31';

SELECT Books.Name, Books.PublishingDate, Books.ISBN
FROM BooksAuthorsRef
INNER JOIN Authors
ON BooksAuthorsRef.AuthorId = Authors.Id
INNER JOIN Books
ON BooksAuthorsRef.BookId = Books.Id
WHERE Authors.Name = 'George Lucas';

SELECT Authors.Name 
FROM BooksAuthorsRef
INNER JOIN Books
ON Books.Id = BooksAuthorsRef.BookId
INNER JOIN Authors
ON BooksAuthorsRef.AuthorId = Authors.Id
WHERE Books.ISBN = '978-3-16-148410-0';

SELECT COUNT(BooksAuthorsRef.BookId), Authors.Name
FROM BooksAuthorsRef
LEFT JOIN Books
ON Books.Id = BooksAuthorsRef.BookId
RIGHT JOIN Authors
ON BooksAuthorsRef.AuthorId = Authors.Id
GROUP BY Authors.Name
ORDER BY COUNT(BooksAuthorsRef.BookId) DESC;

SELECT Books.Name, COUNT(BooksAuthorsRef.AuthorId)
FROM BooksAuthorsRef
LEFT JOIN Books
ON Books.Id = BooksAuthorsRef.BookId
INNER JOIN Authors
ON BooksAuthorsRef.AuthorId = Authors.Id
WHERE Books.PublishingDate >= '2004-01-01' AND Books.PublishingDate <= '2004-12-31'
GROUP BY Books.Name
HAVING COUNT(BooksAuthorsRef.AuthorId) >= 2
ORDER BY Books.Name;
