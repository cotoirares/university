package com.profile.model;

import java.util.Date;

public class Posts {
    private int id;
    private String user;
    private int topicId;
    private String text;
    private Date date;

    public Posts() {}

    public Posts(int id, String user, int topicId, String text, Date date) {
        this.id = id;
        this.user = user;
        this.topicId = topicId;
        this.text = text;
        this.date = date;
    }

    // Getters and Setters
    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public String getUser() { return user; }
    public void setUser(String user) { this.user = user; }

    public int getTopicId() { return topicId; }
    public void setTopicId(int id) { this.topicId = topicId; }

    public String getText() { return text; }
    public void setText(String text) { this.text = text; }

    public Date getDate() { return date; }
    public void setDate(Date date) { this.date = date;}
}
