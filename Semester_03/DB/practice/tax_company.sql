-- task a
create table TaxCompany(
    CompanyID INT PRIMARY KEY,
    CompanyName VARCHAR(100) NOT NULL,
    NumberOfClients INT,
    NumberOfSRLs INT
);

create table Client(
    ClientID INT PRIMARY KEY,
    ClientIdentification VARCHAR(100) NOT NULL,
    MoneySent INT,
    TaxCompanyID INT NOT NULL,
    FOREIGN KEY (TaxCompanyID) references TaxCompany (CompanyID)
);

create table SRL(
    SRLID INT PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Activity VARCHAR(100) NOT NULL,
    Location varchar(100),
    Client INT NOT NULL,
    FOREIGN KEY (Client) references Client(ClientID)
);

create table Assets(
    AssetID INT PRIMARY KEY,
    Name VARCHAR(100) not null,
    Quantity int not null,
    Location varchar(100),
    SRLID int not null,
    FOREIGN KEY (SRLID) references SRL(SRLID)
);
-- task b
create procedure sp_GetClientCounts @ClientID INT
    AS
    BEGIN
        DECLARE @SRLCount INT;
        SELECT @SRLCount = COUNT(*)
        FROM SRL S
        WHERE S.Client = @ClientID;

        DECLARE @AssetCount INT;
        SELECT @AssetCount = COUNT(*)
        FROM Assets A
        JOIN SRL S ON S.SRLID = A.AssetID
        WHERE S.Client = @ClientID;

        SELECT @SRLCount AS NumberOfSRLs, @AssetCount AS NumberOfAssets;
    end
    GO;

EXEC sp_GetClientCounts 12;
-- task c
create view v_ClientMoneyID AS
    SELECT c.ClientIdentification AS ClientIdentification,
           c.MoneySent AS MoneySent,
           s.Name AS SRLName,
           s.Activity AS SRLActivity
FROM Client c JOIN SRL S on c.ClientID = S.Client

-- task d
CREATE FUNCTION fn_ClientSRLAssetCounts()
    RETURNS TABLE
        AS
        RETURN
        SELECT
            c.ClientIdentification AS ClientIdentification,
            s.Location AS SRLLocation,
            COUNT(a.AssetID) AS NumberOfAssets
        FROM Client c
                 JOIN SRL s ON c.ClientID = s.Client
                 LEFT JOIN Assets a ON s.SRLID = a.SRLID
        GROUP BY c.ClientIdentification, s.Location;
GO


