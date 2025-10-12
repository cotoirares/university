CREATE TABLE Groups (
    GroupID INT PRIMARY KEY,
    GroupName NVARCHAR(50) NOT NULL
);

CREATE TABLE Players (
    PlayerID INT PRIMARY KEY,
    FirstName NVARCHAR(50) NOT NULL,
    LastName NVARCHAR(50) NOT NULL,
    DateOfBirth DATE,
    Nationality NVARCHAR(50),
    Ranking INT,
    GroupID INT,
    FOREIGN KEY (GroupID) REFERENCES Groups(GroupID)
);

CREATE TABLE Coaches (
    CoachID INT PRIMARY KEY,
    FirstName NVARCHAR(50) NOT NULL,
    LastName NVARCHAR(50) NOT NULL,
    Nationality NVARCHAR(50)
);

CREATE TABLE Player_Coach (
    PlayerID INT NOT NULL,
    CoachID INT NOT NULL,
    StartDate DATE,
    EndDate DATE,
    PRIMARY KEY (PlayerID, CoachID),
    FOREIGN KEY (PlayerID) REFERENCES Players(PlayerID),
    FOREIGN KEY (CoachID) REFERENCES Coaches(CoachID)
);

CREATE TABLE Sponsors (
    SponsorID INT PRIMARY KEY,
    SponsorName NVARCHAR(100) NOT NULL,
    Industry NVARCHAR(100)
);

CREATE TABLE Player_Sponsors (
    PlayerID INT NOT NULL,
    SponsorID INT NOT NULL,
    StartDate DATE,
    EndDate DATE,
    PRIMARY KEY (PlayerID, SponsorID),
    FOREIGN KEY (PlayerID) REFERENCES Players(PlayerID),
    FOREIGN KEY (SponsorID) REFERENCES Sponsors(SponsorID)
);

CREATE TABLE Officials (
    OfficialID INT PRIMARY KEY,
    FirstName NVARCHAR(50) NOT NULL,
    LastName NVARCHAR(50) NOT NULL,
    Nationality NVARCHAR(50),
    Role NVARCHAR(50)
);

CREATE TABLE Rounds (
    RoundID INT PRIMARY KEY,
    RoundName NVARCHAR(50) NOT NULL
);

CREATE TABLE Matches (
    MatchID INT PRIMARY KEY,
    MatchDate DATE NOT NULL,
    Player1ID INT NOT NULL,
    Player2ID INT NOT NULL,
    Score NVARCHAR(50),
    RoundID INT NOT NULL,
    ChairUmpireID INT,
    FOREIGN KEY (Player1ID) REFERENCES Players(PlayerID),
    FOREIGN KEY (Player2ID) REFERENCES Players(PlayerID),
    FOREIGN KEY (RoundID) REFERENCES Rounds(RoundID),
    FOREIGN KEY (ChairUmpireID) REFERENCES Officials(OfficialID)
);

CREATE TABLE Sets (
    SetID INT PRIMARY KEY,
    MatchID INT NOT NULL,
    SetNumber INT NOT NULL,
    Player1GamesWon INT NOT NULL,
    Player2GamesWon INT NOT NULL,
    FOREIGN KEY (MatchID) REFERENCES Matches(MatchID)
);

-- insert into groups
INSERT INTO Groups (GroupID, GroupName) VALUES (1, 'Red Group');
INSERT INTO Groups (GroupID, GroupName) VALUES (2, 'White Group');

-- insert into players
INSERT INTO Players (PlayerID, FirstName, LastName, DateOfBirth, Nationality, Ranking, GroupID)
VALUES (1, 'Iga', 'Swiatek', '2001-05-31', 'Poland', 1, 1);

INSERT INTO Players (PlayerID, FirstName, LastName, DateOfBirth, Nationality, Ranking, GroupID)
VALUES (2, 'Aryna', 'Sabalenka', '1998-05-05', 'Belarus', 2, 1);

INSERT INTO Players (PlayerID, FirstName, LastName, DateOfBirth, Nationality, Ranking, GroupID)
VALUES (3, 'Elena', 'Rybakina', '1999-06-17', 'Kazakhstan', 3, 2);

INSERT INTO Players (PlayerID, FirstName, LastName, DateOfBirth, Nationality, Ranking, GroupID)
VALUES (4, 'Jessica', 'Pegula', '1994-02-24', 'USA', 4, 2);


-- insert into coaches
INSERT INTO Coaches (CoachID, FirstName, LastName, Nationality)
VALUES (1, 'Piotr', 'Sierzputowski', 'Poland');

INSERT INTO Coaches (CoachID, FirstName, LastName, Nationality)
VALUES (2, 'Dmitry', 'Tursunov', 'Russia');


-- insert into player_coach
INSERT INTO Player_Coach (PlayerID, CoachID, StartDate, EndDate)
VALUES (1, 1, '2016-01-01', NULL);

INSERT INTO Player_Coach (PlayerID, CoachID, StartDate, EndDate)
VALUES (2, 2, '2018-01-01', NULL);

-- violating referential integrity
-- INSERT INTO Players (PlayerID, FirstName, LastName, DateOfBirth, Nationality, Ranking, GroupID)
-- VALUES (5, 'Simona', 'Halep', '1991-09-27', 'Romania', 5, 99);

-- update for players
UPDATE Players
SET Ranking = Ranking + 1
WHERE Nationality = 'Poland';

-- update for coach
UPDATE Coaches
SET Nationality = 'Poland'
WHERE CoachID = 2;

-- update for players
UPDATE Players
SET GroupID = 2
WHERE PlayerID = 1;

-- delete from player_sponsor
DELETE FROM Player_Sponsors
WHERE EndDate IS NULL AND PlayerID IN (SELECT PlayerID FROM Players WHERE Ranking > 3);

-- delete from matches
DELETE FROM Matches
WHERE MatchDate BETWEEN '2021-01-01' AND '2021-12-31' AND Score IS NOT NULL;

--- union 1
SELECT FirstName FROM Players
UNION
SELECT FirstName FROM Coaches;

-- union all and or
SELECT Nationality FROM Players WHERE Nationality = 'Poland' OR Nationality = 'Belarus'
UNION ALL
SELECT Nationality FROM Coaches WHERE Nationality = 'Poland' OR Nationality = 'Belarus';

-- intersect
SELECT Nationality FROM Players
INTERSECT
SELECT Nationality FROM Coaches;

-- intersect in
SELECT * FROM Coaches
WHERE Nationality IN (SELECT Nationality FROM Players);

-- differenec: except
SELECT Nationality FROM Players
EXCEPT
SELECT Nationality FROM Coaches;

-- difference: not in
SELECT * FROM Players
WHERE Nationality NOT IN (SELECT Nationality FROM Coaches);

-- inner join: players and their coaches with player age
SELECT P.FirstName AS PlayerFirstName, P.LastName AS PlayerLastName,
       C.FirstName AS CoachFirstName, C.LastName AS CoachLastName,
       DATEDIFF(year, P.DateOfBirth, GETDATE()) AS PlayerAge
FROM Players P
         INNER JOIN Player_Coach PC ON P.PlayerID = PC.PlayerID
         INNER JOIN Coaches C ON PC.CoachID = C.CoachID;

 -- left join: players and their sponsors
SELECT P.FirstName AS PlayerFirstName, P.LastName AS PlayerLastName,
       S.SponsorName
FROM Players P
         LEFT JOIN Player_Sponsors PS ON P.PlayerID = PS.PlayerID
         LEFT JOIN Sponsors S ON PS.SponsorID = S.SponsorID;

-- right join: matches and chair umpires
SELECT M.MatchID, M.MatchDate,
       O.FirstName AS UmpireFirstName, O.LastName AS UmpireLastName
FROM Matches M
         RIGHT JOIN Officials O ON M.ChairUmpireID = O.OfficialID;

-- full join: coaches who trained players sponsored by nike
SELECT DISTINCT C.FirstName, C.LastName
FROM Coaches C
         FULL OUTER JOIN Player_Coach PC ON C.CoachID = PC.CoachID
         FULL OUTER JOIN Player_Sponsors PS ON PC.PlayerID = PS.PlayerID
         FULL OUTER JOIN Sponsors S ON PS.SponsorID = S.SponsorID
WHERE S.SponsorName = 'Nike';

-- in: players coached by polish coaches
SELECT FirstName, LastName
FROM Players
WHERE PlayerID IN (
    SELECT PlayerID
    FROM Player_Coach
    WHERE CoachID IN (
        SELECT CoachID
        FROM Coaches
        WHERE Nationality = 'Poland'
    )
);

-- in: matches where both players are from countries with players ranked in the top 3
SELECT *
FROM Matches
WHERE Player1ID IN (
    SELECT PlayerID
    FROM Players
    WHERE Nationality IN (
        SELECT Nationality
        FROM Players
        WHERE Ranking <= 3
    )
) AND Player2ID IN (
    SELECT PlayerID
    FROM Players
    WHERE Nationality IN (
        SELECT Nationality
        FROM Players
        WHERE Ranking <= 3
    )
);

-- exists: coaches who have coached polish players
SELECT FirstName, LastName
FROM Coaches C
WHERE EXISTS (
    SELECT *
    FROM Player_Coach PC
             JOIN Players P ON PC.PlayerID = P.PlayerID
    WHERE PC.CoachID = C.CoachID AND P.Nationality = 'Poland'
);

-- exists: matches umpired by greek umpire
SELECT *
FROM Matches M
WHERE EXISTS (
    SELECT *
    FROM Officials O
    WHERE O.OfficialID = M.ChairUmpireID AND O.Nationality = 'Greece'
);

-- from: average ranking per nationality for players ranked in the top 10
SELECT P.Nationality, AVG(P.Ranking) AS AvgRanking
FROM (SELECT * FROM Players WHERE Ranking <= 10) P
GROUP BY P.Nationality;

-- from: total number of sponsors/industry
SELECT S.Industry, COUNT(*) AS NumSponsors
FROM (SELECT * FROM Sponsors WHERE SponsorID > 0) S
GROUP BY S.Industry;

-- group by: number of players/group
SELECT G.GroupName, COUNT(P.PlayerID) AS NumPlayers
FROM Groups G
         LEFT JOIN Players P ON G.GroupID = P.GroupID
GROUP BY G.GroupName;

-- group by: coaches who coached more than 1 player
SELECT C.FirstName, C.LastName, COUNT(PC.PlayerID) AS NumPlayersCoached
FROM Coaches C
         JOIN Player_Coach PC ON C.CoachID = PC.CoachID
GROUP BY C.FirstName, C.LastName
HAVING COUNT(PC.PlayerID) > 1;

-- group by: nationalities with avg player ranking > overall avg ranking
SELECT P.Nationality, AVG(P.Ranking) AS AvgRanking
FROM Players P
GROUP BY P.Nationality
HAVING AVG(P.Ranking) < (SELECT AVG(Ranking) FROM Players);

-- group by: sponsors that sponsor >= 2 players
SELECT S.SponsorName, COUNT(PS.PlayerID) AS NumPlayersSponsored
FROM Sponsors S
         JOIN Player_Sponsors PS ON S.SponsorID = PS.SponsorID
GROUP BY S.SponsorName
HAVING COUNT(PS.PlayerID) >= ALL (
    SELECT COUNT(PlayerID)
    FROM Player_Sponsors
    GROUP BY SponsorID
);

-- any: players who are older than any usa player
SELECT FirstName, LastName, DateOfBirth
FROM Players
WHERE DateOfBirth < ANY (SELECT DateOfBirth FROM Players WHERE Nationality = 'USA');

-- rewrite with aggregation
SELECT FirstName, LastName, DateOfBirth
FROM Players
WHERE DateOfBirth < (SELECT MAX(DateOfBirth) FROM Players WHERE Nationality = 'USA');

-- any: players whose ranking matches any player from belarus
SELECT FirstName, LastName, Ranking
FROM Players
WHERE Ranking = ANY (SELECT Ranking FROM Players WHERE Nationality = 'Belarus');

-- rewrite with in
SELECT FirstName, LastName, Ranking
FROM Players
WHERE Ranking IN (SELECT Ranking FROM Players WHERE Nationality = 'Belarus');

-- all: coaches with different nationality than any other players
SELECT FirstName, LastName, Nationality
FROM Coaches
WHERE Nationality <> ALL (SELECT Nationality FROM Players);

-- rewrite with not in
SELECT FirstName, LastName, Nationality
FROM Coaches
WHERE Nationality NOT IN (SELECT Nationality FROM Players);

-- all: players ranked better that any german player
SELECT FirstName, LastName, Ranking
FROM Players
WHERE Ranking < ALL (SELECT Ranking FROM Players WHERE Nationality = 'Germany');

-- rewrite with aggregation
SELECT FirstName, LastName, Ranking
FROM Players
WHERE Ranking < (SELECT MIN(Ranking) FROM Players WHERE Nationality = 'Germany');
