package com.company;

public class GameEvent {

    private Player eventSource;
    private EventType eventType;

    public GameEvent(Player eventSource, EventType eventType) {
        this.eventSource = eventSource;
        this.eventType = eventType;
    }

    public Player getEventSource() {
        return eventSource;
    }

    public EventType getType() {
        return eventType;
    }

}
