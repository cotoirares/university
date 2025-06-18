package com.profile.servlet;

import com.profile.model.Author;
import com.profile.util.DatabaseConfig;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        //String documentOrMovie = request.getParameter("documentOrMovie");

        HttpSession session = request.getSession();
        session.setAttribute("currentUser", username);
        response.sendRedirect("authorProfile.jsp");

//        try (Connection conn = DatabaseConfig.getConnection()) {
//            String sql = "SELECT * FROM Authors WHERE name = ?";
//            PreparedStatement pstmt = conn.prepareStatement(sql);
//            pstmt.setString(1, username);
//
//            ResultSet rs = pstmt.executeQuery();
//            if (rs.next()) {
//                Author author = new Author();
//                author.setId(rs.getInt("id"));
//                author.setName(rs.getString("name"));
//                author.setDocumentList(rs.getString("documentList"));
//                author.setMovieList(rs.getString("movieList"));
//
//                String[] documentList = author.getDocumentList().split(",");
//                boolean isValid = false;
//                for (String docId : documentList) {
//                    // get the document name based on the ID
//                    docId = docId.trim(); // Trim whitespace
//                    String sqlDoc = "SELECT name FROM Documents WHERE id = ?";
//                    PreparedStatement pstmtDoc = conn.prepareStatement(sqlDoc);
//                    pstmtDoc.setString(1, docId);
//                    ResultSet rsDoc = pstmtDoc.executeQuery();
//                    if (rsDoc.next()) {
//                        String docName = rsDoc.getString("name");
//                        if (docName.trim().equals(documentOrMovie)) {
//                            isValid = true;
//                            break;
//                        }
//                    }
//                    rsDoc.close();
//                    pstmtDoc.close();
//                }
//                if (!isValid) {
//                    String[] movieList = author.getMovieList().split(",");
//                    for (String movieId : movieList) {
//                        // get the document name based on the ID
//                        movieId = movieId.trim(); // Trim whitespace
//                        String sqlDoc = "SELECT title FROM Movies WHERE id = ?";
//                        PreparedStatement pstmtDoc = conn.prepareStatement(sqlDoc);
//                        pstmtDoc.setString(1, movieId);
//                        ResultSet rsDoc = pstmtDoc.executeQuery();
//                        if (rsDoc.next()) {
//                            String movieTitle = rsDoc.getString("title");
//                            if (movieTitle.trim().equals(documentOrMovie)) {
//                                isValid = true;
//                                break;
//                            }
//                        }
//                        rsDoc.close();
//                        pstmtDoc.close();
//                    }
//                }
//                if (isValid) {
//                    HttpSession session = request.getSession();
//                    session.setAttribute("author", author);
//                    response.sendRedirect("authorProfile.jsp");
//                } else {
//                    request.setAttribute("error", "Invalid document or movie selection for the author");
//                    request.getRequestDispatcher("index.jsp").forward(request, response);
//                }
//            } else {
//                request.setAttribute("error", "Invalid username or document/movie selection");
//                request.getRequestDispatcher("index.jsp").forward(request, response);
//            }
//        } catch (SQLException e) {
//            e.printStackTrace();
//            request.setAttribute("error", "Database error occurred");
//            request.getRequestDispatcher("index.jsp").forward(request, response);
//        }
    }
} 