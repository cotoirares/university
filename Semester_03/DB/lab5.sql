-- lab 5
-- part a)
-- nonclustered index on Ranking
CREATE NONCLUSTERED INDEX IX_Players_Ranking ON Players(Ranking);

-- clustered index scan
SELECT *
FROM Players;

-- clustered index seek
SELECT *
FROM Players
WHERE PlayerID = 1;

-- non-clustered index scan
SELECT Ranking
FROM Players;

-- non-clustered index seek
SELECT PlayerID, FirstName, LastName
FROM Players
WHERE Ranking = 1;

-- key lookup
SELECT Nationality
FROM Players
WHERE Ranking = 1;

-- part b)
CREATE NONCLUSTERED INDEX IX_Coaches_ExperienceLevel ON Coaches(ExperienceLevel);

SET SHOWPLAN_ALL ON;
GO
SELECT *
FROM Coaches
WHERE ExperienceLevel = 5;
GO
SET SHOWPLAN_ALL OFF;
GO

-- part c)

CREATE VIEW v_PlayersAndCoaches AS
SELECT P.PlayerID, P.FirstName, P.LastName, P.Ranking,
       C.CoachID, C.FirstName AS CoachFirstName, C.LastName AS CoachLastName, C.ExperienceLevel
FROM Player_Coach PC
         JOIN Players P ON PC.PlayerID = P.PlayerID
         JOIN Coaches C ON PC.CoachID = C.CoachID;

SELECT *
FROM v_PlayersAndCoaches
WHERE Ranking < 5;
