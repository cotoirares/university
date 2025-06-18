package com.profile.servlet;

import com.profile.util.DatabaseConfig;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@WebServlet("/checkNewPosts")
public class NotificationServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String currentUser = (String) request.getSession().getAttribute("currentUser");
        if (currentUser == null) {
            response.getWriter().print("ERROR");
            return;
        }

        try (Connection conn = DatabaseConfig.getConnection()) {
            // Get latest post from other users
            String sql = "SELECT p.user, p.text, t.topicname FROM Posts p " +
                    "JOIN Topics t ON p.topicId = t.id " +
                    "WHERE p.user != ? ORDER BY p.date DESC LIMIT 1";

            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, currentUser);
            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                String result = rs.getString("user") + "||" +
                        rs.getString("text") + "||" +
                        rs.getString("topicname");
                response.getWriter().print(result);
            } else {
                response.getWriter().print("NONE");
            }

        } catch (Exception e) {
            response.getWriter().print("ERROR");
        }
    }
}