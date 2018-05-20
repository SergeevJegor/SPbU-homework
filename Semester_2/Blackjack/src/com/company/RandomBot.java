package com.company;

import java.util.Random;

public class RandomBot extends Player {
    public RandomBot(Integer money) {
        super(money);
    }

    public void Play() {
        Random rnd = new Random(System.currentTimeMillis());
        Integer drawCard = rnd.nextInt(1);
        if (drawCard == 1) {
            doNotify(new GameEvent(this, EventType.HIT));
        } else {
            doNotify(new GameEvent(this, EventType.STAND));
        }
    }

    public void MakeBet() {
        if (this.getMoney() > 100) this.currentBet = 100;
        else this.currentBet = this.currentMoney;

        gamesPlayed++;
    }
}
