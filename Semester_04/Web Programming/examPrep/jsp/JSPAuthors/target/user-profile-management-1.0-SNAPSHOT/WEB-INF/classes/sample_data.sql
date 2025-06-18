USE user_profiles_db;

-- Insert sample users
INSERT INTO users (username, password, name, email, age, home_town) VALUES
('john_doe', 'password123', 'John Doe', 'john.doe@email.com', 28, 'New York'),
('jane_smith', 'password456', 'Jane Smith', 'jane.smith@email.com', 32, 'Los Angeles'),
('bob_wilson', 'password789', 'Bob Wilson', 'bob.wilson@email.com', 45, 'Chicago'),
('alice_brown', 'passwordabc', 'Alice Brown', 'alice.brown@email.com', 25, 'Boston'),
('mike_johnson', 'passworddef', 'Mike Johnson', 'mike.johnson@email.com', 35, 'Seattle');

-- Note: In a real application, passwords should be hashed, not stored in plain text 