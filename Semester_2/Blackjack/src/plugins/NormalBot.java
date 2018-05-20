package plugins;

import com.company.EventType;
import com.company.GameEvent;
import com.company.Observer;
import com.company.Player;

public class NormalBot extends Player {

    public NormalBot(Integer money) {
        super(money);
    }

    public void Play() {

        if (this.getScore() < 19) {
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
