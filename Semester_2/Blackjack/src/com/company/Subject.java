package com.company;

public interface Subject {

    void addObserver(Observer observer);

    void doNotify(GameEvent event);

}
