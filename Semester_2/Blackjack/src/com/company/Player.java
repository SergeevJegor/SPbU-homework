package com.company;

import java.util.ArrayList;

public abstract class Player implements Subject {

    ArrayList<Card> hand;

    protected String playerName;
    protected Integer gamesPlayed;
    protected Integer currentMoney;
    protected Integer currentBet;

    protected Observer gameTable;

    public Player(String playerName, Integer money) {
        this.playerName = playerName;
        this.gamesPlayed = 0;
        this.currentMoney = money;
        this.currentBet = 0;
        this.hand = new ArrayList<>();
    }

    public void setGameTable(Observer gameTable) {
        this.gameTable = gameTable;
    }

    public Integer getCurrentBet() {
        return currentBet;
    }

    public void winMoney(Integer money) {
        this.currentMoney += money;
    }

    public void loseMoney(Integer money) {
        this.currentMoney -= money;
    }

    public Integer getMoney() {
        return this.currentMoney;
    }

    public void clearHand() {
        this.hand.clear();
    }

    public Integer getScore() {
        int result = 0;
        boolean isAce = false;

        for (Card card : hand) {
            result += card.getValue();
            if (card.getRank() == CardRanks.Ace) isAce = true;
        }

        if (isAce && result + 10 <= 21) result += 10;

        return result;
    }

    public void doubleDown() {
        currentBet *= 2;
    }

    public String getStatistic() {
        return (this.playerName + " played " + gamesPlayed + " games and his account is now " + currentMoney);
    }

    @Override
    public void doNotify(GameEvent event) {
        gameTable.onNotify(event);
    }

    @Override
    public void addObserver(Observer observer) {
        gameTable = observer;
    }

    abstract public void MakeBet();

    abstract public void Play();

}
