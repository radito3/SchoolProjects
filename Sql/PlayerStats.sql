DROP DATABASE IF EXISTS PlayerStats;
CREATE DATABASE PlayerStats;
USE PlayerStats;

CREATE TABLE StatTypes(
	StatCode VARCHAR(3) NOT NULL,
	Name VARCHAR(100) NOT NULL,
    
    PRIMARY KEY(StatCode)
);

CREATE TABLE Positions(
	PositionCode VARCHAR(2) NOT NULL,
	Name VARCHAR(100) NOT NULL,
    
    PRIMARY KEY(PositionCode)
);

CREATE TABLE Players(
	Id INTEGER NOT NULL AUTO_INCREMENT,
	Name VARCHAR(100) NOT NULL,
	Num INTEGER NOT NULL,
	PositionCode VARCHAR(2) NOT NULL,
    
    PRIMARY KEY(Id, Name),
	FOREIGN KEY (PositionCode) REFERENCES Positions(PositionCode)
);

CREATE TABLE Tournaments(
	Id INTEGER NOT NULL AUTO_INCREMENT,
	Name VARCHAR(100) NOT NULL,
	
	PRIMARY KEY(Id, Name)
);

CREATE TABLE Matches(
	Id INTEGER NOT NULL AUTO_INCREMENT,
    MatchDate DATE NOT NULL,
    TournamentId INTEGER NOT NULL,
  
	PRIMARY KEY(Id, MatchDate),
    FOREIGN KEY (TournamentId) REFERENCES Tournaments(Id)
);

CREATE TABLE MatchStats(
	Id INTEGER NOT NULL AUTO_INCREMENT,
    MatchId INTEGER NOT NULL,
    PlayerId INTEGER NOT NULL,
    EventMinute INTEGER NOT NULL,
    StatCode VARCHAR(3) NOT NULL,
    
    PRIMARY KEY(Id, EventMinute, StatCode),
	FOREIGN KEY (MatchId) REFERENCES Matches(Id),
    FOREIGN KEY (PlayerId) REFERENCES Players(Id),
    FOREIGN KEY (StatCode) REFERENCES StatTypes(StatCode)
);

INSERT INTO
	StatTypes(StatCode, Name)
VALUES 
	('G', 'Гол'),
	('A', 'Асистенция'),
	('R', 'Червен картон'),
	('Y', 'Жълт картон'),
	('OG', 'Автогол'),
	('IN', 'Смяна влиза'),
	('OUT', 'Смяна излиза');

INSERT INTO
	Positions(PositionCode, Name)
VALUES
	('GK', 'Вратар'),
	('RB', 'Десен защитник'),
	('LB', 'Ляв защитник'),
	('CB', 'Централен защитник'),
	('RM', 'Десен полузащитник'),
	('LM', 'Ляв полузащитник'),
	('CM', 'Полузащитник'),
	('CF', 'Централен нападател');

INSERT INTO
	Players(Name, Num, PositionCode)
VALUES
	('Ivaylo Trifonov', 1, 'GK'),
	('Valko Trifonov', 2, 'RB'),
	('Ognyan Yanev', 3, 'CB'),
	('Zahari Dragomirov', 4, 'CB'),
	('Bozhidar Chilikov', 5, 'LB'),
	('Timotei Zahariev', 6, 'CM'),
	('Marin Valentinov', 7, 'CM'),
	('Mitre Cvetkov', 99, 'CF'),
	('Zlatko Genov', 9, 'CF'),
	('Matey Goranov', 10, 'RM'),
	('Sergei Zhivkov', 11, 'LM');

INSERT INTO
	Tournaments(Name)
VALUES
	('Шампионска лига'),
	('Първа лига'),
	('Купа на България'),
	('Суперкупа на България');

INSERT INTO
	Matches(MatchDate, TournamentId)
VALUES
	('2017-04-08', 2),
	('2017-04-13', 2),
	('2017-04-21', 2),
	('2017-04-28', 2),
	('2017-05-06', 2),
	('2017-05-11', 2),
	('2016-09-21', 3),
	('2016-10-26', 3);

INSERT INTO
	MatchStats(MatchId, PlayerId, EventMinute, StatCode) 
VALUES
	(8, 9, 14, 'G'),
	(8, 8, 14, 'A'),
	(8, 3, 43, 'Y'),
	(7, 2, 28, 'Y'),
	(7, 10, 45, 'Y'),
	(7, 10, 65, 'R'),
	(1, 10, 23, 'G'),
	(1, 9, 23, 'A'),
	(1, 9, 43, 'G'),
	(2, 4, 33, 'OG'),
	(2, 9, 68, 'G'),
	(2, 1, 68, 'A'),
	(3, 3, 35, 'G'),
	(3, 4, 35, 'A'),
	(3, 8, 55, 'G'),
	(3, 11, 55, 'A'),
	(4, 3, 9, 'G'),
	(4, 8, 9, 'G'),
	(4, 8, 56, 'OG'),
	(5, 8, 67, 'G');

SELECT Players.Name, Players.Num 
FROM Players
WHERE Players.PositionCode = 'RB' OR Players.PositionCode = 'CB' OR Players.PositionCode = 'LB';

SELECT Matches.MatchDate, Tournaments.Name
FROM Matches
LEFT JOIN Tournaments
ON Matches.TournamentId = Tournaments.Id
WHERE Matches.MatchDate >= '2017-04-01' AND Matches.MatchDate <= '2017-04-31';

SELECT Matches.MatchDate, Players.Name, Players.Num, MatchStats.EventMinute, StatTypes.Name
FROM MatchStats
LEFT JOIN Players
ON Players.Id = MatchStats.PlayerId
LEFT JOIN Matches
ON Matches.Id = MatchStats.MatchId
LEFT JOIN StatTypes
ON StatTypes.StatCode = MatchStats.StatCode
WHERE Players.Num = 99;

SELECT COUNT(MatchStats.StatCode)
FROM MatchStats
WHERE MatchStats.StatCode = 'OG';

SELECT Matches.MatchDate, COUNT(MatchStats.StatCode)
FROM MatchStats
LEFT JOIN Matches
ON Matches.Id = MatchStats.MatchId
WHERE Matches.MatchDate < '2017-05-01' AND MatchStats.StatCode = 'G'
GROUP BY Matches.MatchDate;

SELECT Positions.Name, COUNT(MatchStats.StatCode)
FROM Players
LEFT JOIN Positions
ON Positions.PositionCode = Players.PositionCode
LEFT JOIN MatchStats
ON MatchStats.PlayerId = Players.Id AND MatchStats.StatCode = 'G'
GROUP BY Positions.Name;

SELECT DISTINCT Players.Name, Players.Num, Positions.Name, COUNT(MatchStats.StatCode)
FROM Players
LEFT JOIN Positions
ON Positions.PositionCode = Players.PositionCode
RIGHT JOIN MatchStats
ON Players.Id = MatchStats.PlayerId
WHERE MatchStats.StatCode = 'Y' OR MatchStats.StatCode = 'R'
GROUP BY Players.Name
ORDER BY COUNT(MatchStats.StatCode) DESC;
