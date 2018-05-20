package com.company;

public class Dealer extends Player {

    public Dealer() {
        super(Integer.MAX_VALUE);
    }

    public void Play() {

        if (this.getScore() < 16) {
            doNotify(new GameEvent(this, EventType.HIT));
        } else {
            doNotify(new GameEvent(this, EventType.DEALER_FINISH));
        }
    }

    public void MakeBet() {
        this.currentBet = 0;
    }

}
