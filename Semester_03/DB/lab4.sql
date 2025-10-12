-- lab 4: testing

-- tables to test: coaches (single-column pk, no fk); players (single-column pk, one fk), player_coach(multi-column pk, two fks)
-- views for the test: v_playersBasic (select), v_PlayersCoaches (join), v_GroupPlayerCounts(select with group by containing join)

-- tables for the tests
-- Tables that hold data about tests, tables, views, and runs

CREATE TABLE Tests (
    TestID INT IDENTITY PRIMARY KEY,
    TestName NVARCHAR(100) NOT NULL
);

CREATE TABLE TablesForTesting (
    TableID INT IDENTITY PRIMARY KEY,
    TableName NVARCHAR(100) NOT NULL
);

CREATE TABLE TestTables (
    TestID INT NOT NULL,
    TableID INT NOT NULL,
    Position INT NOT NULL,
    NoOfRows INT NOT NULL, -- how many rows to insert
    PRIMARY KEY (TestID, TableID),
    FOREIGN KEY (TestID) REFERENCES Tests(TestID),
    FOREIGN KEY (TableID) REFERENCES TablesForTesting(TableID)
);

CREATE TABLE ViewsForTesting (
    ViewID INT IDENTITY PRIMARY KEY,
    ViewName NVARCHAR(100) NOT NULL
);

CREATE TABLE TestViews (
    TestID INT NOT NULL,
    ViewID INT NOT NULL,
    PRIMARY KEY (TestID, ViewID),
    FOREIGN KEY (TestID) REFERENCES Tests(TestID),
    FOREIGN KEY (ViewID) REFERENCES ViewsForTesting(ViewID)
);

CREATE TABLE TestRuns (
    TestRunID INT IDENTITY PRIMARY KEY,
    TestID INT NOT NULL,
    RunDate DATETIME NOT NULL,
    FOREIGN KEY (TestID) REFERENCES Tests(TestID)
);

CREATE TABLE TestRunTables (
    TestRunID INT NOT NULL,
    TableID INT NOT NULL,
    InsertTimeMs INT NOT NULL,
    PRIMARY KEY (TestRunID, TableID),
    FOREIGN KEY (TestRunID) REFERENCES TestRuns(TestRunID),
    FOREIGN KEY (TableID) REFERENCES TablesForTesting(TableID)
);

CREATE TABLE TestRunViews (
    TestRunID INT NOT NULL,
    ViewID INT NOT NULL,
    SelectTimeMs INT NOT NULL,
    PRIMARY KEY (TestRunID, ViewID),
    FOREIGN KEY (TestRunID) REFERENCES TestRuns(TestRunID),
    FOREIGN KEY (ViewID) REFERENCES ViewsForTesting(ViewID)
);

-- views for the tests
CREATE VIEW v_PlayersBasic AS
SELECT PlayerID, FirstName, LastName, Nationality, Ranking
FROM Players;

CREATE VIEW v_PlayersCoaches AS
SELECT P.PlayerID, P.FirstName AS PlayerFirstName, P.LastName AS PlayerLastName,
       C.CoachID, C.FirstName AS CoachFirstName, C.LastName AS CoachLastName
FROM Players P
         INNER JOIN Player_Coach PC ON P.PlayerID = PC.PlayerID
         INNER JOIN Coaches C ON PC.CoachID = C.CoachID;

CREATE VIEW v_GroupPlayerCounts AS
SELECT G.GroupName, COUNT(P.PlayerID) AS NumPlayers
FROM Groups G
         LEFT JOIN Players P ON G.GroupID = P.GroupID
GROUP BY G.GroupName;

-- insert a test
DECLARE @TestID INT = (SELECT TOP 1 TestID FROM Tests WHERE TestName = 'Performance Test 1');
DELETE FROM TestTables WHERE TestID = @TestID;


-- insert tables into TablesForTesting
INSERT INTO TablesForTesting (TableName) VALUES ('Coaches');       -- ID 1
INSERT INTO TablesForTesting (TableName) VALUES ('Players');       -- ID 2
INSERT INTO TablesForTesting (TableName) VALUES ('Player_Coach');  -- ID 3

-- insert views into ViewsForTesting
INSERT INTO ViewsForTesting (ViewName) VALUES ('v_PlayersBasic');        -- ID 1
INSERT INTO ViewsForTesting (ViewName) VALUES ('v_PlayersCoaches');      -- ID 2
INSERT INTO ViewsForTesting (ViewName) VALUES ('v_GroupPlayerCounts');   -- ID 3

-- define the test tables: order them so we delete in coaches -> players -> player_Coach
-- position defines delete order. For insertion we will do reverse.

-- Player_Coach at position 1 (delete first)
INSERT INTO TestTables (TestID, TableID, Position, NoOfRows)
VALUES (@TestID, 3, 1, 30);  -- Player_Coach

-- Players at position 2 (delete second)
INSERT INTO TestTables (TestID, TableID, Position, NoOfRows)
VALUES (@TestID, 2, 2, 20);  -- Players

-- Coaches at position 3 (delete last)
INSERT INTO TestTables (TestID, TableID, Position, NoOfRows)
VALUES (@TestID, 1, 3, 10);  -- Coaches

-- define the test views
INSERT INTO TestViews (TestID, ViewID) VALUES (@TestID, 1);
INSERT INTO TestViews (TestID, ViewID) VALUES (@TestID, 2);
INSERT INTO TestViews (TestID, ViewID) VALUES (@TestID, 3);

-- stored procedures for the tests
CREATE OR ALTER PROCEDURE sp_RunTest
@TestID INT
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @RunDate DATETIME = GETDATE();
    DECLARE @TestRunID INT;

    -- insert a new test run
    INSERT INTO TestRuns (TestID, RunDate) VALUES (@TestID, @RunDate);
    SET @TestRunID = SCOPE_IDENTITY();

    -- delete data from the test’s tables in the specified order
    -- gather table info ordered by Position
    ;WITH OrderedTables AS (
        SELECT TT.TableID, TFT.TableName, TT.Position, TT.NoOfRows
        FROM TestTables TT
                 JOIN TablesForTesting TFT ON TT.TableID = TFT.TableID
        WHERE TT.TestID = @TestID)
     SELECT * INTO #TableOrder FROM OrderedTables;

    DECLARE @TableName SYSNAME;
    DECLARE @NoOfRows INT;
    DECLARE @SQL NVARCHAR(MAX);
    DECLARE @Position INT;

    DECLARE TableCursor CURSOR LOCAL FAST_FORWARD FOR
        SELECT TableName
        FROM #TableOrder
        ORDER BY Position;  -- deletion order

    OPEN TableCursor;
    FETCH NEXT FROM TableCursor INTO @TableName;

    WHILE @@FETCH_STATUS = 0
        BEGIN
            SET @SQL = N'TRUNCATE TABLE ' + QUOTENAME(@TableName) + ';';
            BEGIN TRY
                EXEC sys.sp_executesql @SQL;
            END TRY
            BEGIN CATCH
                -- If TRUNCATE not possible (FK constraints), use DELETE
                SET @SQL = N'DELETE FROM ' + QUOTENAME(@TableName) + ';';
                EXEC sys.sp_executesql @SQL;
            END CATCH

            FETCH NEXT FROM TableCursor INTO @TableName;
        END
    CLOSE TableCursor;
    DEALLOCATE TableCursor;

    -- Step 2: Insert data into the test’s tables in reverse order of deletion
    -- We will insert dummy data. We also measure insertion time.

    DECLARE ReverseCursor CURSOR LOCAL FAST_FORWARD FOR
        SELECT TableID, TableName, NoOfRows
        FROM #TableOrder
        ORDER BY Position DESC; -- reverse order

    OPEN ReverseCursor;
    DECLARE @StartTime DATETIME2, @EndTime DATETIME2;
    DECLARE @InsertTimeMs INT;
    DECLARE @i INT, @TableID INT;

    FETCH NEXT FROM ReverseCursor INTO @TableID, @TableName, @NoOfRows;
    WHILE @@FETCH_STATUS = 0
        BEGIN
            SET @StartTime = SYSDATETIME();

            -- Insert dummy rows. We'll do a simple pattern depending on the table.
            IF @TableName = 'Coaches'
                BEGIN
                    -- Insert NoOfRows coaches
                    SET @i = 1;
                    WHILE @i <= @NoOfRows
                        BEGIN
                            SET @SQL = N'INSERT INTO Coaches (CoachID, FirstName, LastName, Nationality)
                             VALUES (' + CAST((1000+@i) AS NVARCHAR(10)) +
                                       N', ''TestCoachF''+CAST(' + CAST(@i AS NVARCHAR(10)) + ' AS NVARCHAR(10)), ''TestCoachL''+CAST(' + CAST(@i AS NVARCHAR(10)) + ' AS NVARCHAR(10)), ''TestCountry'')';
                            EXEC sys.sp_executesql @SQL;
                            SET @i += 1;
                        END
                END
            ELSE IF @TableName = 'Players'
                BEGIN
                    -- Insert NoOfRows players referencing GroupID = 1 (assume it exists)
                    SET @i = 1;
                    WHILE @i <= @NoOfRows
                        BEGIN
                            SET @SQL = N'INSERT INTO Players (PlayerID, FirstName, LastName, DateOfBirth, Nationality, Ranking, GroupID)
                             VALUES (' + CAST((2000+@i) AS NVARCHAR(10)) +
                                       N', ''TestPlayerF''+CAST(' + CAST(@i AS NVARCHAR(10)) + ' AS NVARCHAR(10)), ''TestPlayerL''+CAST(' + CAST(@i AS NVARCHAR(10)) + ' AS NVARCHAR(10)), ''1990-01-01'', ''TestCountry'', '
                                + CAST(@i AS NVARCHAR(10)) + ', 1)';
                            EXEC sys.sp_executesql @SQL;
                            SET @i += 1;
                        END
                END
            ELSE IF @TableName = 'Player_Coach'
                BEGIN
                    SET @i = 1;
                    WHILE @i <= @NoOfRows
                        BEGIN
                            -- PlayerID cycles through 2001 to 2020 repeatedly every 20 inserts
                            -- CoachID increments every 20 rows
                            SET @SQL = N'INSERT INTO Player_Coach (PlayerID, CoachID, StartDate, EndDate)
                     VALUES ('
                                + CAST((2000 + ((@i - 1) % 20) + 1) AS NVARCHAR(10)) + ','
                                + CAST((1000 + ((@i - 1) / 20) + 1) AS NVARCHAR(10))
                                + ',''2020-01-01'', NULL)';

                            EXEC sys.sp_executesql @SQL;
                            SET @i += 1;
                        END
                END
            SET @EndTime = SYSDATETIME();
            SET @InsertTimeMs = DATEDIFF(MILLISECOND, @StartTime, @EndTime);

            INSERT INTO TestRunTables (TestRunID, TableID, InsertTimeMs)
            VALUES (@TestRunID, @TableID, @InsertTimeMs);

            FETCH NEXT FROM ReverseCursor INTO @TableID, @TableName, @NoOfRows;
        END

    CLOSE ReverseCursor;
    DEALLOCATE ReverseCursor;

    -- evaluate test views and record their performance

    DECLARE ViewCursor CURSOR LOCAL FAST_FORWARD FOR
        SELECT TV.ViewID, VFT.ViewName
        FROM TestViews TV
                 JOIN ViewsForTesting VFT ON TV.ViewID = VFT.ViewID
        WHERE TV.TestID = @TestID;

    OPEN ViewCursor;
    DECLARE @ViewID INT;
    DECLARE @ViewName SYSNAME;
    DECLARE @SelectTimeMs INT;

    FETCH NEXT FROM ViewCursor INTO @ViewID, @ViewName;
    WHILE @@FETCH_STATUS = 0
        BEGIN
            SET @StartTime = SYSDATETIME();

            SET @SQL = N'SELECT * FROM ' + QUOTENAME(@ViewName) + ';';
            EXEC sys.sp_executesql @SQL;

            SET @EndTime = SYSDATETIME();
            SET @SelectTimeMs = DATEDIFF(MILLISECOND, @StartTime, @EndTime);

            INSERT INTO TestRunViews (TestRunID, ViewID, SelectTimeMs)
            VALUES (@TestRunID, @ViewID, @SelectTimeMs);

            FETCH NEXT FROM ViewCursor INTO @ViewID, @ViewName;
        END

    CLOSE ViewCursor;
    DEALLOCATE ViewCursor;

    DROP TABLE #TableOrder;

    PRINT 'Test run completed successfully. Run ID = ' + CAST(@TestRunID AS NVARCHAR(10));
END;

-- run the test
DECLARE @TestID INT = (SELECT TOP 1 TestID FROM Tests WHERE TestName = 'Performance Test 1');
    EXEC sp_RunTest @TestID;

-- inspect
SELECT * FROM TestRuns;
SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;

