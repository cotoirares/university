package com.profile.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseConfig {
    private static final String DATABASE = "topicPosts";
    private static final String USER = "root";
    private static final String PASSWORD = "root";  // Empty password for the new MySQL server
    
    // Try multiple connection methods
    private static final String[] URLS = {
        "jdbc:mysql://localhost:8889/" + DATABASE + "?useUnicode=true&characterEncoding=UTF8&allowPublicKeyRetrieval=true&useSSL=false",
        "jdbc:mysql://127.0.0.1:8889/" + DATABASE + "?useUnicode=true&characterEncoding=UTF8&allowPublicKeyRetrieval=true&useSSL=false"
    };

    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection() throws SQLException {
        SQLException lastException = null;
        
        for (String url : URLS) {
            try {
                System.out.println("Trying to connect to: " + url);
                Connection conn = DriverManager.getConnection(url, USER, PASSWORD);
                System.out.println("Successfully connected to: " + url);
                return conn;
            } catch (SQLException e) {
                lastException = e;
                System.out.println("Failed to connect to: " + url + " - " + e.getMessage());
            }
        }
        
        // If all connections failed, throw the last exception
        if (lastException != null) {
            throw lastException;
        }
        
        throw new SQLException("Could not establish database connection with any of the configured URLs");
    }
} 