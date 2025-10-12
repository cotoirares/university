-- part 1
create table R(
                  FK1 INT NOT NULL,
                  FK2 INT NOT NULL,
                  PRIMARY KEY (FK1, FK2),
                  C1 VARCHAR(100),
                  C2 VARCHAR(100),
                  C3 VARCHAR(100),
                  C4 INT NOT NULL,
                  C5 INT
);

INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (1, 2, 'Caeleb Dressel', 'US', '50m freestyle swim', 50, 1);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (1, 4, 'Fred Ker', 'US', '100m running', 100, 2);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (1, 5, 'Eliud Kipe', 'Kenya', 'Marathon', 300, 3);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (2, 1, 'Florend Manadoua', 'France', '50m freestyle swim', 25, 2);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (2, 2, 'Caeleb Dressel', 'US', '100m freestyle swim', 100, 0);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (2, 3, 'Kyle Chalmers', 'Australia', '100m freestyle swim', 45, 2);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (3, 1, 'Ahmed Hafnoui', 'Netherlands', '400m freestyle swim', 35, 1);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (3, 3, 'Andre', 'Canada', '100m running', 10, 3);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (3, 4, 'Abdi', 'Netherlands', 'Marathon', 250, 3);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (4, 2, 'Marcell', 'Canada', '100m running', 70, 1);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (4, 3, 'Bruno', 'Brazil', '50m freestyle swim', 25, 3);
INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5) VALUES (4, 4, 'Bashir', 'Kenya', 'Marathon', 255, 2);

CREATE OR ALTER TRIGGER TrOnUpdate
    ON R
    FOR UPDATE
    AS
    DECLARE @total INT = 1
    SELECT @total = @total + SUM(i.C5 + d.C5)
    FROM deleted d INNER JOIN inserted i ON d.FK1 = i.FK1 AND d.FK1 = i.FK2
    WHERE d.C5 <= i.C5
    PRINT @total

UPDATE R
SET C5 = 0
WHERE FK1 = FK2

-- part b
create table Accounts(
    AccountID INT PRIMARY KEY IDENTITY (1,1),
    AccEmail VARCHAR(100) UNIQUE ,
    AccJoinDate DATE,
    AccActive BIT
);

create table Actors(
    ActorID INT PRIMARY KEY IDENTITY (1,1),
    ActorName VARCHAR(100),
    ActorNationality VARCHAR(100)
);

create table Movies(
    MovieID INT PRIMARY KEY IDENTITY (1,1),
    MovieTitle VARCHAR(100),
    MovieDuration INT, -- must be positive
    CONSTRAINT MovieDuration CHECK (MovieDuration > 0)
);

create table Actors_Movies(
    ActorID INT REFERENCES Actors(ActorID),
    MovieID INT REFERENCES Movies(MovieID),
    PRIMARY KEY (ActorID, MovieID)
);

create table Reviews(
    ReviewID INT PRIMARY KEY IDENTITY (1,1),
    ReviewDate DATE,
    ReviewRating FLOAT,
    ReviewText VARCHAR(100),
    AccountID INT REFERENCES Accounts(AccountID),
    MovieID INT REFERENCES Movies(MovieID),
    CONSTRAINT ReviewRating CHECK (ReviewRating between 0 AND 10)
);

create table Watchlists(
    WatchID INT PRIMARY KEY IDENTITY (1,1),
    AccountID INT REFERENCES Accounts(AccountID),
    MovieID INT REFERENCES Movies(MovieID),
    WatchDate DATE
);

-- task b
CREATE OR ALTER PROCEDURE sp_AddAccount (@ParamAcc INT, @ParamMovie INT) AS
    BEGIN
        IF NOT EXISTS(SELECT AccountID FROM Accounts WHERE AccountID = @ParamAcc)
        BEGIN
            PRINT 'Account is not valid'
            RETURN
        end
        IF NOT EXISTS(SELECT MovieID FROM Movies WHERE MovieID = @ParamMovie)
            BEGIN
                PRINT 'Movie is not valid'
                RETURN
            end
        -- verificare daca exista in watchlist?
        INSERT INTO Watchlists(AccountID, MovieID, WatchDate) VALUES (@ParamAcc, @ParamMovie, GETDATE())
    end
    GO;

-- task c
CREATE VIEW vw_ShowNames AS
SELECT * FROM Movies AS M
         INNER JOIN
     Reviews AS R ON M.MovieID = R.MovieID
         INNER JOIN
     (SELECT A.AccountID
      FROM Accounts AS A
               INNER JOIN
           Watchlists AS W ON W.AccountID = A.AccountID
      GROUP BY A.AccountID
      HAVING COUNT(A.AccountID) > 3) A
     ON A.AccountID = R.AccountID

-- task d
create function fn_NumberOfMovies(@S INT, @E INT, @R INT)
    RETURNS INT
    AS
    BEGIN
        DECLARE @RESULT INT = 0;
        SELECT @RESULT = COUNT(*) FROM Movies M
        WHERE (SELECT COUNT(*) from Watchlists W
                               WHERE W.MovieID = M.MovieID AND W.WatchDate BETWEEN @S AND @E) >= @R;
        RETURN @RESULT;
    END
    GO
