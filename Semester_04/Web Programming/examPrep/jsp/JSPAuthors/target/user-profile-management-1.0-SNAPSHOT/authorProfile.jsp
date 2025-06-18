<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="com.profile.model.Author, com.profile.model.Document, com.profile.model.Movie" %>
<%@ page import="java.util.*" %>

<%
    // Check if user is logged in
    Author currentAuthor = (Author) session.getAttribute("author");
    if (currentAuthor == null) {
        response.sendRedirect("index.jsp");
        return;
    }

    // Get data from servlet (if any)
    String message = (String) request.getAttribute("message");
    String error = (String) request.getAttribute("error");
    List<Object> interleavedWorks = (List<Object>) request.getAttribute("interleavedWorks");
    Map<String, Object> largestDocument = (Map<String, Object>) request.getAttribute("largestDocument");
    List<Movie> userMovies = (List<Movie>) request.getAttribute("userMovies");
%>

<!DOCTYPE html>
<html>
<head>
    <title>Author Dashboard - <%= currentAuthor.getName() %></title>
<%--    <style>--%>
<%--        body { font-family: Arial, sans-serif; margin: 20px; background-color: #f5f5f5; }--%>
<%--        .container { max-width: 1200px; margin: 0 auto; }--%>
<%--        .header { background-color: #1877f2; color: white; padding: 20px; border-radius: 8px; margin-bottom: 20px; }--%>
<%--        .section { background-color: white; padding: 20px; margin: 15px 0; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }--%>
<%--        .form-group { margin: 10px 0; }--%>
<%--        label { display: block; margin-bottom: 5px; font-weight: bold; }--%>
<%--        input, textarea { width: 100%; padding: 8px; border: 1px solid #ddd; border-radius: 4px; box-sizing: border-box; }--%>
<%--        button { background-color: #1877f2; color: white; padding: 10px 15px; border: none; border-radius: 4px; cursor: pointer; margin: 5px; }--%>
<%--        button:hover { background-color: #166fe5; }--%>
<%--        .delete-btn { background-color: #dc3545; }--%>
<%--        .delete-btn:hover { background-color: #c82333; }--%>
<%--        .view-btn { background-color: #28a745; }--%>
<%--        .view-btn:hover { background-color: #218838; }--%>
<%--        .message { background-color: #d4edda; color: #155724; padding: 10px; border-radius: 4px; margin: 10px 0; }--%>
<%--        .error { background-color: #f8d7da; color: #721c24; padding: 10px; border-radius: 4px; margin: 10px 0; }--%>
<%--        .work-item { border: 1px solid #ddd; padding: 15px; margin: 10px 0; border-radius: 4px; }--%>
<%--        .work-type { font-weight: bold; color: #1877f2; }--%>
<%--        .logout { float: right; color: white; text-decoration: none; }--%>
<%--        .nav-buttons { margin: 20px 0; text-align: center; }--%>
<%--    </style>--%>
</head>
<body>
<div class="container">
    <div class="header">
        <h1>Welcome, <%= currentAuthor.getName() %>!</h1>
        <a href="index.jsp" class="logout">Logout</a>
    </div>

    <div class="nav-buttons">
        <form method="get" action="authorOperations" style="display: inline;">
            <input type="hidden" name="action" value="showAddDocument">
            <button type="submit">Add Document</button>
        </form>

        <form method="get" action="authorOperations" style="display: inline;">
            <input type="hidden" name="action" value="listMyWorks">
            <button type="submit" class="view-btn">View my Documents / Movies</button>
        </form>

        <form method="get" action="authorOperations" style="display: inline;">
            <input type="hidden" name="action" value="findLargestDocument">
            <button type="submit" class="view-btn">Document with Most Authors</button>
        </form>

        <form method="get" action="authorOperations" style="display: inline;">
            <input type="hidden" name="action" value="showDeleteMovie">
            <button type="submit" class="delete-btn">Delete My Movie</button>
        </form>
    </div>

    <% if (message != null && !message.isEmpty()) { %>
    <div class="message"><%= message %></div>
    <% } %>

    <% if (error != null && !error.isEmpty()) { %>
    <div class="error"><%= error %></div>
    <% } %>

    <% if ("showAddDocument".equals(request.getParameter("action"))) { %>
    <div class="section">
        <h2>Add New Document</h2>
        <form method="post" action="authorOperations">
            <input type="hidden" name="action" value="addDocument">
            <div class="form-group">
                <label>Document Name:</label>
                <input type="text" name="docName" required>
            </div>
            <div class="form-group">
                <label>Document Contents:</label>
                <textarea name="docContents" rows="4" required></textarea>
            </div>
            <button type="submit">Add Document</button>
        </form>
    </div>
    <% } %>

    <% if (interleavedWorks != null) { %>
    <div class="section">
        <h2>My Works </h2>
        <%
            for (Object work : interleavedWorks) {
                if (work instanceof Document) {
                    Document doc = (Document) work;
        %>
        <div class="work-item">
            <div class="work-type">DOCUMENT</div>
            <strong>ID:</strong> <%= doc.getId() %><br>
            <strong>Name:</strong> <%= doc.getName() %><br>
            <strong>Contents:</strong> <%= doc.getContents() %>
        </div>
        <%
        } else if (work instanceof Movie) {
            Movie movie = (Movie) work;
        %>
        <div class="work-item">
            <div class="work-type">MOVIE</div>
            <strong>ID:</strong> <%= movie.getId() %><br>
            <strong>Title:</strong> <%= movie.getTitle() %><br>
            <strong>Duration:</strong> <%= movie.getDuration() %> minutes
        </div>
        <%
                }
            }

            if (interleavedWorks.isEmpty()) {
        %>
        <p>You haven't authored any documents or movies yet.</p>
        <%
            }
        %>
    </div>
    <% } %>

    <% if (largestDocument != null) { %>
    <div class="section">
        <h2>Document with Most Authors</h2>
        <div class="work-item">
            <strong>Document ID:</strong> <%= largestDocument.get("id") %><br>
            <strong>Name:</strong> <%= largestDocument.get("name") %><br>
            <strong>Contents:</strong> <%= largestDocument.get("contents") %><br>
            <strong>Number of Authors:</strong> <%= largestDocument.get("authorCount") %>
        </div>
    </div>
    <% } %>

    <% if (userMovies != null) { %>
    <div class="section">
        <h2>Delete My Movies</h2>
        <%
            if (userMovies.isEmpty()) {
        %>
        <p>You don't have any movies to delete.</p>
        <%
        } else {
            for (Movie movie : userMovies) {
        %>
        <div class="work-item">
            <strong>ID:</strong> <%= movie.getId() %><br>
            <strong>Title:</strong> <%= movie.getTitle() %><br>
            <strong>Duration:</strong> <%= movie.getDuration() %> minutes<br>
            <form method="post" action="authorOperations" style="margin-top: 10px;">
                <input type="hidden" name="action" value="deleteMovie">
                <input type="hidden" name="movieId" value="<%= movie.getId() %>">
                <button type="submit" class="delete-btn" onclick="return confirm('Are you sure you want to delete this movie?')">Delete Movie</button>
            </form>
        </div>
        <%
                }
            }
        %>
    </div>
    <% } %>
</div>
</body>
</html>