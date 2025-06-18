package com.profile.servlet;

import com.profile.model.Author;
import com.profile.model.Document;
import com.profile.model.Movie;
import com.profile.util.DatabaseConfig;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.*;
import java.util.*;

public class AuthorOperationsServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        HttpSession session = request.getSession();
        String currentUser = session.getAttribute("currentUser").toString();

        if (currentUser == null) {
            response.sendRedirect("index.jsp");
            return;
        }

        String action = request.getParameter("action");

        try {
            switch (action) {
                case "modifyPost":
                    modifyPost(request, response, currentUser, session);
                    break;

                case "addPostToTopic":
                    addPostToTopic(request, response, currentUser, session);
                    break;

                default:
                    response.sendRedirect("authorProfile.jsp");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            request.setAttribute("error", "Database error: " + e.getMessage());
            request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
        }
    }

    private void modifyPost(HttpServletRequest request, HttpServletResponse response,
                                String currentUser, HttpSession session) throws SQLException, ServletException, IOException {

        String toModifPostIdStr = request.getParameter("toModifPostId");
        String toModifPostContent = request.getParameter("toModifPostContent");

        if (toModifPostIdStr == null || toModifPostContent == null) {
            request.setAttribute("error", "Please fill in all fields!");
            request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
            return;
        }
        int toModifPostId = Integer.parseInt(toModifPostIdStr);

        try (Connection conn = DatabaseConfig.getConnection()) {
            // Insert new document
            String insertSql = "UPDATE Posts SET user = ?, text = ?, date = NOW() WHERE id = ?";
            PreparedStatement pstmt = conn.prepareStatement(insertSql, Statement.RETURN_GENERATED_KEYS);
            pstmt.setString(1, currentUser);
            pstmt.setString(2, toModifPostContent);
            pstmt.setInt(3, toModifPostId);
            try {
                pstmt.executeUpdate();
                session.setAttribute("currentUser", currentUser);
                request.setAttribute("message", "Document added successfully!");
            }
            catch (SQLException e) {
                e.printStackTrace();
                request.setAttribute("error", "Failed to modify post: " + e.getMessage());
            }
        }
        request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
    }

    private void addPostToTopic(HttpServletRequest request, HttpServletResponse response,
                            String currentUser, HttpSession session) throws SQLException, ServletException, IOException {

        String toAddTopic = request.getParameter("toAddTopic");
        String toAddPostContent = request.getParameter("toAddPostContent");

        if (toAddTopic == null || toAddPostContent == null) {
            request.setAttribute("error", "Please fill in all fields!");
            request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
            return;
        }

        try (Connection conn = DatabaseConfig.getConnection()) {
            // Insert new document
            // check if topic exists
            String existingTopicSql = "SELECT id FROM Topics WHERE topicname = ?";
            PreparedStatement existingTopicStmt = conn.prepareStatement(existingTopicSql);
            existingTopicStmt.setString(1, toAddTopic);
            ResultSet existingTopicRs = existingTopicStmt.executeQuery();
            int topicId;
            if (existingTopicRs.next()) {
                topicId = existingTopicRs.getInt("id");
            } else {
                // Insert new topic if it doesn't exist
                String insertTopicSql = "INSERT INTO Topics (topicname) VALUES (?)";
                PreparedStatement insertTopicStmt = conn.prepareStatement(insertTopicSql, Statement.RETURN_GENERATED_KEYS);
                insertTopicStmt.setString(1, toAddTopic);
                insertTopicStmt.executeUpdate();

                ResultSet rs = insertTopicStmt.getGeneratedKeys();
                if (rs.next()) {
                    topicId = rs.getInt(1);
                } else {
                    throw new SQLException("Failed to create new topic.");
                }
            }

            String insertSql = "INSERT INTO Posts (user, topicId, text, date) VALUES (?, ?, ?, NOW())";
            PreparedStatement pstmt = conn.prepareStatement(insertSql, Statement.RETURN_GENERATED_KEYS);
            pstmt.setString(1, currentUser);
            pstmt.setString(2, String.valueOf(topicId));
            pstmt.setString(3, toAddPostContent);
            try {
                pstmt.executeUpdate();
                session.setAttribute("currentUser", currentUser);
                request.setAttribute("message", "Document added successfully!");
            }
            catch (SQLException e) {
                e.printStackTrace();
                request.setAttribute("error", "Failed to modify post: " + e.getMessage());
            }
        request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
    }
}
//    @Override
//    protected void doPost(HttpServletRequest request, HttpServletResponse response)
//            throws ServletException, IOException {
//
//        HttpSession session = request.getSession();
//        Author currentAuthor = (Author) session.getAttribute("author");
//
//        if (currentAuthor == null) {
//            response.sendRedirect("index.jsp");
//            return;
//        }
//
//        String action = request.getParameter("action");
//
//        try {
//            switch (action) {
//                case "addDocument":
//                    addNewDocument(request, response, currentAuthor, session);
//                    break;
//
//                case "deleteMovie":
//                    deleteMovie(request, response, currentAuthor, session);
//                    break;
//
//                default:
//                    response.sendRedirect("authorProfile.jsp");
//            }
//        } catch (SQLException e) {
//            e.printStackTrace();
//            request.setAttribute("error", "Database error: " + e.getMessage());
//            request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
//        }
//    }

//    private void addNewDocument(HttpServletRequest request, HttpServletResponse response,
//                                Author currentAuthor, HttpSession session) throws SQLException, ServletException, IOException {
//
//        String docName = request.getParameter("docName");
//        String docContents = request.getParameter("docContents");
//
//        if (docName == null || docContents == null || docName.trim().isEmpty()) {
//            request.setAttribute("error", "Please fill in all fields!");
//            request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
//            return;
//        }
//
//        try (Connection conn = DatabaseConfig.getConnection()) {
//            // Insert new document
//            String insertSql = "INSERT INTO documents (name, contents) VALUES (?, ?)";
//            PreparedStatement pstmt = conn.prepareStatement(insertSql, Statement.RETURN_GENERATED_KEYS);
//            pstmt.setString(1, docName);
//            pstmt.setString(2, docContents);
//            pstmt.executeUpdate();
//
//            // Get the new document ID
//            ResultSet rs = pstmt.getGeneratedKeys();
//            if (rs.next()) {
//                int newDocId = rs.getInt(1);
//
//                // Update author's documentList
//                String currentDocList = currentAuthor.getDocumentList();
//                String newDocList = (currentDocList == null || currentDocList.isEmpty()) ?
//                        String.valueOf(newDocId) :
//                        currentDocList + "," + newDocId;
//
//                String updateSql = "UPDATE authors SET documentList = ? WHERE id = ?";
//                PreparedStatement updateStmt = conn.prepareStatement(updateSql);
//                updateStmt.setString(1, newDocList);
//                updateStmt.setInt(2, currentAuthor.getId());
//                updateStmt.executeUpdate();
//
//                // Update session
//                currentAuthor.setDocumentList(newDocList);
//                session.setAttribute("author", currentAuthor);
//
//                request.setAttribute("message", "Document added successfully!");
//            }
//        }
//
//        request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
//    }
//
//    private void listMyWorksInterleaved(HttpServletRequest request, HttpServletResponse response,
//                                        Author currentAuthor) throws SQLException, ServletException, IOException {
//
//        List<Object> interleavedWorks = new ArrayList<>();
//
//        try (Connection conn = DatabaseConfig.getConnection()) {
//            // Get author's documents
//            List<Document> myDocuments = new ArrayList<>();
//            if (currentAuthor.getDocumentList() != null && !currentAuthor.getDocumentList().isEmpty()) {
//                String[] docIds = currentAuthor.getDocumentList().split(",");
//                for (String docId : docIds) {
//                    String sql = "SELECT * FROM documents WHERE id = ?";
//                    PreparedStatement pstmt = conn.prepareStatement(sql);
//                    pstmt.setInt(1, Integer.parseInt(docId.trim()));
//                    ResultSet rs = pstmt.executeQuery();
//                    if (rs.next()) {
//                        Document doc = new Document();
//                        doc.setId(rs.getInt("id"));
//                        doc.setName(rs.getString("name"));
//                        doc.setContents(rs.getString("contents"));
//                        myDocuments.add(doc);
//                    }
//                }
//            }
//
//            // Get author's movies
//            List<Movie> myMovies = new ArrayList<>();
//            if (currentAuthor.getMovieList() != null && !currentAuthor.getMovieList().isEmpty()) {
//                String[] movieIds = currentAuthor.getMovieList().split(",");
//                for (String movieId : movieIds) {
//                    String sql = "SELECT * FROM movies WHERE id = ?";
//                    PreparedStatement pstmt = conn.prepareStatement(sql);
//                    pstmt.setInt(1, Integer.parseInt(movieId.trim()));
//                    ResultSet rs = pstmt.executeQuery();
//                    if (rs.next()) {
//                        Movie movie = new Movie();
//                        movie.setId(rs.getInt("id"));
//                        movie.setTitle(rs.getString("title"));
//                        movie.setDuration(rs.getInt("duration"));
//                        myMovies.add(movie);
//                    }
//                }
//            }
//
//            // Create interleaved list: document, movie, document, movie...
//            int docIndex = 0, movieIndex = 0;
//            boolean addDocument = true;
//
//            while (docIndex < myDocuments.size() || movieIndex < myMovies.size()) {
//                if (addDocument && docIndex < myDocuments.size()) {
//                    interleavedWorks.add(myDocuments.get(docIndex++));
//                } else if (!addDocument && movieIndex < myMovies.size()) {
//                    interleavedWorks.add(myMovies.get(movieIndex++));
//                } else if (docIndex < myDocuments.size()) {
//                    interleavedWorks.add(myDocuments.get(docIndex++));
//                } else if (movieIndex < myMovies.size()) {
//                    interleavedWorks.add(myMovies.get(movieIndex++));
//                }
//                addDocument = !addDocument;
//            }
//        }
//
//        request.setAttribute("interleavedWorks", interleavedWorks);
//        request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
//    }
//
//    private void findDocumentWithMostAuthors(HttpServletRequest request, HttpServletResponse response)
//            throws SQLException, ServletException, IOException {
//
//        try (Connection conn = DatabaseConfig.getConnection()) {
//            // Get all authors and their document lists
//            String sql = "SELECT name, documentList FROM authors WHERE documentList IS NOT NULL AND documentList != ''";
//            PreparedStatement pstmt = conn.prepareStatement(sql);
//            ResultSet rs = pstmt.executeQuery();
//
//            Map<Integer, Integer> documentAuthorCount = new HashMap<>();
//
//            while (rs.next()) {
//                String docList = rs.getString("documentList");
//                if (docList != null && !docList.isEmpty()) {
//                    String[] docIds = docList.split(",");
//                    for (String docId : docIds) {
//                        int id = Integer.parseInt(docId.trim());
//                        documentAuthorCount.put(id, documentAuthorCount.getOrDefault(id, 0) + 1);
//                    }
//                }
//            }
//
//            // Find document with maximum authors
//            int maxAuthors = 0;
//            int mostAuthoredDocId = -1;
//            for (Map.Entry<Integer, Integer> entry : documentAuthorCount.entrySet()) {
//                if (entry.getValue() > maxAuthors) {
//                    maxAuthors = entry.getValue();
//                    mostAuthoredDocId = entry.getKey();
//                }
//            }
//
//            if (mostAuthoredDocId != -1) {
//                // Get document details
//                String docSql = "SELECT * FROM documents WHERE id = ?";
//                PreparedStatement docStmt = conn.prepareStatement(docSql);
//                docStmt.setInt(1, mostAuthoredDocId);
//                ResultSet docRs = docStmt.executeQuery();
//
//                if (docRs.next()) {
//                    Map<String, Object> largestDocument = new HashMap<>();
//                    largestDocument.put("id", docRs.getInt("id"));
//                    largestDocument.put("name", docRs.getString("name"));
//                    largestDocument.put("contents", docRs.getString("contents"));
//                    largestDocument.put("authorCount", maxAuthors);
//
//                    request.setAttribute("largestDocument", largestDocument);
//                }
//            } else {
//                request.setAttribute("error", "No documents found in the system.");
//            }
//        }
//
//        request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
//    }
//
//    private void showUserMovies(HttpServletRequest request, HttpServletResponse response,
//                                Author currentAuthor) throws SQLException, ServletException, IOException {
//
//        List<Movie> userMovies = new ArrayList<>();
//
//        if (currentAuthor.getMovieList() != null && !currentAuthor.getMovieList().isEmpty()) {
//            try (Connection conn = DatabaseConfig.getConnection()) {
//                String[] movieIds = currentAuthor.getMovieList().split(",");
//                for (String movieId : movieIds) {
//                    String sql = "SELECT * FROM movies WHERE id = ?";
//                    PreparedStatement pstmt = conn.prepareStatement(sql);
//                    pstmt.setInt(1, Integer.parseInt(movieId.trim()));
//                    ResultSet rs = pstmt.executeQuery();
//                    if (rs.next()) {
//                        Movie movie = new Movie();
//                        movie.setId(rs.getInt("id"));
//                        movie.setTitle(rs.getString("title"));
//                        movie.setDuration(rs.getInt("duration"));
//                        userMovies.add(movie);
//                    }
//                }
//            }
//        }
//
//        request.setAttribute("userMovies", userMovies);
//        request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
//    }
//
//    private void deleteMovie(HttpServletRequest request, HttpServletResponse response,
//                             Author currentAuthor, HttpSession session) throws SQLException, ServletException, IOException {
//
//        String movieIdToDelete = request.getParameter("movieId");
//
//        if (movieIdToDelete == null || movieIdToDelete.trim().isEmpty()) {
//            request.setAttribute("error", "Invalid movie ID!");
//            request.getRequestDispatcher("authorProfile.jsp").forward(request, response);
//            return;
//        }
//
//        try (Connection conn = DatabaseConfig.getConnection()) {
//            // Remove movie from database
//            String deleteSql = "DELETE FROM movies WHERE id = ?";
//            PreparedStatement pstmt = conn.prepareStatement(deleteSql);
//            pstmt.setInt(1, Integer.parseInt(movieIdToDelete));
//            int deleted = pstmt.executeUpdate();
//
//            if (deleted > 0) {
//                // Update author's movieList
//                String currentMovieList = currentAuthor.getMovieList();
//                if (currentMovieList != null && !currentMovieList.isEmpty()) {
//                    String[] movieIds = currentMovieList.split(",");
//                    StringBuilder newMovieList = new StringBuilder();
//
//                    for (String movieId : movieIds) {
//                        if (!movieId.trim().equals(movieIdToDelete)) {
//                            if (newMovieList.length() > 0) newMovieList.append(",");
//                            newMovieList.append(movieId.trim());
//                        }
//                    }
//
//                    String updateSql = "UPDATE authors SET movieList = ? WHERE id = ?";
//                    PreparedStatement updateStmt = conn.prepareStatement(updateSql);
//                    updateStmt.setString(1, newMovieList.toString());
//                    updateStmt.setInt(2, currentAuthor.getId());
//                    updateStmt.executeUpdate();
//
//                    // Update session
//                    currentAuthor.setMovieList(newMovieList.toString());
//                    session.setAttribute("author", currentAuthor);
//                }
//
//                request.setAttribute("message", "Movie deleted successfully!");
//            } else {
//                request.setAttribute("error", "Movie not found or could not be deleted!");
//            }
//        }
//
//        // Show movies list again after deletion
//        showUserMovies(request, response, currentAuthor);
//    }
}