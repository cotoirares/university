package com.profile.model;

public class Topics {
    private int id;
    private String topicName;

    public Topics() {}

    public Topics(int id, String topicName) {
        this.id = id;
        this.topicName = topicName;
    }

    // Getters and Setters
    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public String getTopicName() { return getTopicName(); }
    public void setTopicName(String topicName) { this.topicName = topicName; }
}
