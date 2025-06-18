package com.profile.model;

public class Movie {
    private int id;
    private String title;
    private int duration;

    public Movie() {}

    public Movie(int id, String title, int duration) {
        this.id = id;
        this.title = title;
        this.duration = duration;
    }

    // Getters and Setters
    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public String getTitle() { return title; }
    public void setTitle(String name) { this.title = name; }

    public int getDuration() { return duration; }
    public void setDuration(int duration) { this.duration = duration; }
}