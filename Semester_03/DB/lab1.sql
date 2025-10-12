
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
    MatchDate DATE,
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


