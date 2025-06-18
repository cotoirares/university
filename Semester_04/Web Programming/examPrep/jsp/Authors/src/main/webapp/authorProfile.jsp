<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="com.profile.model.Author, com.profile.model.Document, com.profile.model.Movie" %>
<%@ page import="java.util.*" %>

<%
    // Check if user is logged in
//    Author currentAuthor = (Author) session.getAttribute("author");
//    if (currentAuthor == null) {
//        response.sendRedirect("index.jsp");
//        return;
//    }
    String currentUser = session.getAttribute("currentUser").toString();
    // Get data from servlet (if any)
    String message = (String) request.getAttribute("message");
    String error = (String) request.getAttribute("error");
//    List<Object> interleavedWorks = (List<Object>) request.getAttribute("interleavedWorks");
//    Map<String, Object> largestDocument = (Map<String, Object>) request.getAttribute("largestDocument");
//    List<Movie> userMovies = (List<Movie>) request.getAttribute("userMovies");
%>

<!DOCTYPE html>
<html>
<head>
    <title>User Dashboard - <%= currentUser %></title>
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
        <h1>Welcome, <%= currentUser %>!</h1>
        <a href="index.jsp" class="logout">Logout</a>
    </div>

    <div class="nav-buttons">
        <form method="post" action="authorOperations" style="display: inline;">
            <input type="hidden" name="action" value="modifyPost">
            <button type="submit">Modify a Post</button>
        </form>

        <form method="post" action="authorOperations" style="display: inline;">
            <input type="hidden" name="action" value="addPostToTopic">
            <button type="submit" class="view-btn">Add Post to a Topic</button>
        </form>

<%--        <form method="get" action="authorOperations" style="display: inline;">--%>
<%--            <input type="hidden" name="action" value="findLargestDocument">--%>
<%--            <button type="submit" class="view-btn">Document with Most Authors</button>--%>
<%--        </form>--%>

<%--        <form method="get" action="authorOperations" style="display: inline;">--%>
<%--            <input type="hidden" name="action" value="showDeleteMovie">--%>
<%--            <button type="submit" class="delete-btn">Delete My Movie</button>--%>
<%--        </form>--%>
    </div>

    <% if (message != null && !message.isEmpty()) { %>
    <div class="message"><%= message %></div>
    <% } %>

    <% if (error != null && !error.isEmpty()) { %>
    <div class="error"><%= error %></div>
    <% } %>

    <% if ("modifyPost".equals(request.getParameter("action"))) { %>
    <div class="section">
        <h2>Modify a Post</h2>
        <form method="post" action="authorOperations">
            <input type="hidden" name="action" value="modifyPost">
            <div class="form-group">
                <label>Post Id:</label>
                <input type="text" name="toModifPostId" required>
            </div>
            <div class="form-group">
                <label>New post content:</label>
                <textarea name="toModifPostContent" rows="5" required></textarea>
            </div>
            <button type="submit">Modify Post</button>
        </form>
    </div>
    <% } %>

    <% if ("addPostToTopic".equals(request.getParameter("action"))) { %>
    <div class="section">
        <h2>Add a Post to a Topic</h2>
        <form method="post" action="authorOperations">
            <input type="hidden" name="action" value="addPostToTopic">
            <div class="form-group">
                <label>Topic:</label>
                <input type="text" name="toAddTopic" required>
            </div>
            <div class="form-group">
                <label>Post content:</label>
                <textarea name="toAddPostContent" rows="5" required></textarea>
            </div>
            <button type="submit">Add the Post</button>
        </form>
    </div>
    <% } %>

<%--    <% if (interleavedWorks != null) { %>--%>
<%--    <div class="section">--%>
<%--        <h2>My Works </h2>--%>
<%--        <%--%>
<%--            for (Object work : interleavedWorks) {--%>
<%--                if (work instanceof Document) {--%>
<%--                    Document doc = (Document) work;--%>
<%--        %>--%>
<%--        <div class="work-item">--%>
<%--            <div class="work-type">DOCUMENT</div>--%>
<%--            <strong>ID:</strong> <%= doc.getId() %><br>--%>
<%--            <strong>Name:</strong> <%= doc.getName() %><br>--%>
<%--            <strong>Contents:</strong> <%= doc.getContents() %>--%>
<%--        </div>--%>
<%--        <%--%>
<%--        } else if (work instanceof Movie) {--%>
<%--            Movie movie = (Movie) work;--%>
<%--        %>--%>
<%--        <div class="work-item">--%>
<%--            <div class="work-type">MOVIE</div>--%>
<%--            <strong>ID:</strong> <%= movie.getId() %><br>--%>
<%--            <strong>Title:</strong> <%= movie.getTitle() %><br>--%>
<%--            <strong>Duration:</strong> <%= movie.getDuration() %> minutes--%>
<%--        </div>--%>
<%--        <%--%>
<%--                }--%>
<%--            }--%>

<%--            if (interleavedWorks.isEmpty()) {--%>
<%--        %>--%>
<%--        <p>You haven't authored any documents or movies yet.</p>--%>
<%--        <%--%>
<%--            }--%>
<%--        %>--%>
<%--    </div>--%>
<%--    <% } %>--%>

<%--    <% if (largestDocument != null) { %>--%>
<%--    <div class="section">--%>
<%--        <h2>Document with Most Authors</h2>--%>
<%--        <div class="work-item">--%>
<%--            <strong>Document ID:</strong> <%= largestDocument.get("id") %><br>--%>
<%--            <strong>Name:</strong> <%= largestDocument.get("name") %><br>--%>
<%--            <strong>Contents:</strong> <%= largestDocument.get("contents") %><br>--%>
<%--            <strong>Number of Authors:</strong> <%= largestDocument.get("authorCount") %>--%>
<%--        </div>--%>
<%--    </div>--%>
<%--    <% } %>--%>

<%--    <% if (userMovies != null) { %>--%>
<%--    <div class="section">--%>
<%--        <h2>Delete My Movies</h2>--%>
<%--        <%--%>
<%--            if (userMovies.isEmpty()) {--%>
<%--        %>--%>
<%--        <p>You don't have any movies to delete.</p>--%>
<%--        <%--%>
<%--        } else {--%>
<%--            for (Movie movie : userMovies) {--%>
<%--        %>--%>
<%--        <div class="work-item">--%>
<%--            <strong>ID:</strong> <%= movie.getId() %><br>--%>
<%--            <strong>Title:</strong> <%= movie.getTitle() %><br>--%>
<%--            <strong>Duration:</strong> <%= movie.getDuration() %> minutes<br>--%>
<%--            <form method="post" action="authorOperations" style="margin-top: 10px;">--%>
<%--                <input type="hidden" name="action" value="deleteMovie">--%>
<%--                <input type="hidden" name="movieId" value="<%= movie.getId() %>">--%>
<%--                <button type="submit" class="delete-btn" onclick="return confirm('Are you sure you want to delete this movie?')">Delete Movie</button>--%>
<%--            </form>--%>
<%--        </div>--%>
<%--        <%--%>
<%--                }--%>
<%--            }--%>
<%--        %>--%>
<%--    </div>--%>
<%--    <% } %>--%>
</div>
<script>
    let lastPost = '';

    // Check for new posts every 5 seconds
    setInterval(function() {
        fetch('checkNewPosts')
            .then(response => response.text())
            .then(data => {
                if (data !== 'ERROR' && data !== 'NONE' && data !== lastPost) {
                    let parts = data.split('||');
                    let user = parts[0];
                    let text = parts[1];
                    let topic = parts[2];

                    // Show simple alert
                    alert('New post by ' + user + ' in topic "' + topic + '":\n' + text);

                    lastPost = data;
                }
            })
            .catch(error => console.log('Error:', error));
    }, 5000);
</script>

</body>
</html>