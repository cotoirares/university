package com.profile.model;

public class Author {
    private int id;
    private String name;
    private String documentList;
    private String movieList;

    public Author() {}

    public Author(int id, String name, String documentList, String movieList) {
        this.id = id;
        this.name = name;
        this.documentList = documentList;
        this.movieList = movieList;
    }

    // Getters and Setters
    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public String getDocumentList() { return documentList; }
    public void setDocumentList(String documentList) { this.documentList = documentList; }

    public String getMovieList() { return movieList; }
    public void setMovieList(String movieList) { this.movieList = movieList; }
}