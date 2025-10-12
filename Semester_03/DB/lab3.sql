-- lab 3
-- modify ranking for players in smallint
-- name convention: sp_<action>_<table>_<column>_<newtype>

CREATE PROCEDURE sp_ModifyColumnType_Players_Ranking_ToSmallInt
AS
BEGIN
    ALTER TABLE Players ALTER COLUMN Ranking SMALLINT;
END;

-- revert
CREATE PROCEDURE sp_Revert_ModifyColumnType_Players_Ranking_ToInt
AS
BEGIN
    ALTER TABLE Players ALTER COLUMN Ranking INT;
END;

-- add email to players
CREATE PROCEDURE sp_AddColumn_Players_Email
AS
BEGIN
    ALTER TABLE Players ADD Email NVARCHAR(100);
END;

-- revert
CREATE PROCEDURE sp_RemoveColumn_Players_Email
AS
BEGIN
    ALTER TABLE Players DROP COLUMN Email;
END;

-- add default to players nationality
CREATE PROCEDURE sp_AddDefaultConstraint_Players_Nationality
AS
BEGIN
    ALTER TABLE Players ADD CONSTRAINT DF_Players_Nationality DEFAULT ('Unknown') FOR Nationality;
END;

-- revert
CREATE PROCEDURE sp_RemoveDefaultConstraint_Players_Nationality
AS
BEGIN
    ALTER TABLE Players DROP CONSTRAINT DF_Players_Nationality;
END;

-- remove primary key from groups
CREATE PROCEDURE sp_RemovePrimaryKey_Groups
AS
BEGIN
    ALTER TABLE Groups DROP CONSTRAINT Groups.PK__Groups__149AF30A7B34C2BA;
END;

-- revert
CREATE PROCEDURE sp_AddPrimaryKey_Groups
AS
BEGIN
    ALTER TABLE Groups ADD CONSTRAINT PK_Groups_GroupID PRIMARY KEY (GroupID);
END;

-- add unique constraint to players on name
CREATE PROCEDURE sp_AddUniqueConstraint_Players_FirstName_LastName
AS
BEGIN
    ALTER TABLE Players ADD CONSTRAINT UQ_Players_FirstName_LastName UNIQUE (FirstName, LastName);
END;

-- revert
CREATE PROCEDURE sp_RemoveUniqueConstraint_Players_FirstName_LastName
AS
BEGIN
    ALTER TABLE Players DROP CONSTRAINT UQ_Players_FirstName_LastName;
END;

-- add foreign key to Sets (winnerID)
CREATE PROCEDURE sp_AddColumn_Sets_WinnerID
AS
BEGIN
    ALTER TABLE Sets ADD WinnerID INT;
END;

CREATE PROCEDURE sp_AddForeignKey_Sets_WinnerID_Players
AS
BEGIN
    ALTER TABLE Sets
        ADD CONSTRAINT FK_Sets_WinnerID_Players_PlayerID FOREIGN KEY (WinnerID) REFERENCES Players(PlayerID);
END;

-- revert foreign key
CREATE PROCEDURE sp_RemoveForeignKey_Sets_WinnerID_Players
AS
BEGIN
    ALTER TABLE Sets DROP CONSTRAINT FK_Sets_WinnerID_Players_PlayerID;
END;

-- revert column
CREATE PROCEDURE sp_RemoveColumn_Sets_WinnerID
AS
BEGIN
    ALTER TABLE Sets DROP COLUMN WinnerID;
END;

-- create Countries table for players
CREATE PROCEDURE sp_CreateTable_Countries
AS
BEGIN
    CREATE TABLE Countries (
                               CountryCode CHAR(2) PRIMARY KEY,
                               CountryName NVARCHAR(100) NOT NULL
    );
END;

-- revert
CREATE PROCEDURE sp_DropTable_Countries
AS
BEGIN
    DROP TABLE Countries;
END;

-- versioning
CREATE TABLE SchemaVersion (
                               VersionNumber INT PRIMARY KEY
);

INSERT INTO SchemaVersion (VersionNumber) VALUES (1);

-- update db to specified version
    CREATE PROCEDURE sp_UpdateSchemaToVersion
        @TargetVersion INT  -- wanted schema version
    AS
    BEGIN
        -- hold the current version
        DECLARE @CurrentVersion INT;

        -- retrieve the current version
        SELECT @CurrentVersion = VersionNumber FROM SchemaVersion;

        -- if no version is set, set it to 1
        IF @CurrentVersion IS NULL
            BEGIN
                SET @CurrentVersion = 1; 
                -- insert the current version 
                INSERT INTO SchemaVersion (VersionNumber) VALUES (@CurrentVersion);
            END

        -- if the database is already at the target version
        IF @CurrentVersion = @TargetVersion
            BEGIN
                PRINT 'Database is already at the wanted version';
                RETURN; 
            END

        -- upgrading the database schema
        WHILE @CurrentVersion < @TargetVersion
            BEGIN
                SET @CurrentVersion = @CurrentVersion + 1;

                -- perform schema changes to reach the target version
                IF @CurrentVersion = 2
                    BEGIN
                        -- v2: modify ranking column to smallint
                        EXEC sp_ModifyColumnType_Players_Ranking_ToSmallInt;
                    END
                ELSE IF @CurrentVersion = 3
                    BEGIN
                        -- v3: add email column to players table
                        EXEC sp_AddColumn_Players_Email;
                    END
                ELSE IF @CurrentVersion = 4
                    BEGIN
                        -- v4: add default constraint to Players
                        EXEC sp_AddDefaultConstraint_Players_Nationality;
                    END
                ELSE IF @CurrentVersion = 5
                    BEGIN
                        -- v5: remove primary key from Groups table
                        EXEC sp_RemovePrimaryKey_Groups;
                    END
                ELSE IF @CurrentVersion = 6
                    BEGIN
                        -- v6: add unique constraint on Players names
                        EXEC sp_AddUniqueConstraint_Players_FirstName_LastName;
                    END
                ELSE IF @CurrentVersion = 7
                    BEGIN
                        -- v7: add foreign key and column to Sets table
                        EXEC sp_AddColumn_Sets_WinnerID;
                        EXEC sp_AddForeignKey_Sets_WinnerID_Players;
                    END
                ELSE IF @CurrentVersion = 8
                    BEGIN
                        -- v8: create Countries table
                        EXEC sp_CreateTable_Countries;
                    END
                -- update
                UPDATE SchemaVersion SET VersionNumber = @CurrentVersion;
            END

        -- downgrading the database schema
        WHILE @CurrentVersion > @TargetVersion
            BEGIN
                IF @CurrentVersion = 8
                    BEGIN
                        -- v8: drop Countries table
                        EXEC sp_DropTable_Countries;
                    END
                ELSE IF @CurrentVersion = 7
                    BEGIN
                        -- v7: remove foreign key and column from Sets table
                        EXEC sp_RemoveForeignKey_Sets_WinnerID_Players;
                        EXEC sp_RemoveColumn_Sets_WinnerID;
                    END
                ELSE IF @CurrentVersion = 6
                    BEGIN
                        -- v6: remove unique constraint from Players
                        EXEC sp_RemoveUniqueConstraint_Players_FirstName_LastName;
                    END
                ELSE IF @CurrentVersion = 5
                    BEGIN
                        -- v5: add primary key back to Groups table
                        EXEC sp_AddPrimaryKey_Groups;
                    END
                ELSE IF @CurrentVersion = 4
                    BEGIN
                        -- v4: remove default constraint from Players
                        EXEC sp_RemoveDefaultConstraint_Players_Nationality;
                    END
                ELSE IF @CurrentVersion = 3
                    BEGIN
                        -- v3: remove email column from Players table
                        EXEC sp_RemoveColumn_Players_Email;
                    END
                ELSE IF @CurrentVersion = 2
                    BEGIN
                        -- v2: modify ranking column back to int
                        EXEC sp_Revert_ModifyColumnType_Players_Ranking_ToInt;
                    END
                SET @CurrentVersion = @CurrentVersion - 1;
                -- update
                UPDATE SchemaVersion SET VersionNumber = @CurrentVersion;
            END
    END;
