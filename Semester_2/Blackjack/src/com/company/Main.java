package com.company;

import org.picocontainer.DefaultPicoContainer;
import org.picocontainer.MutablePicoContainer;

public class Main {
    public static void main(String[] args) throws Exception {

        MutablePicoContainer pico = new DefaultPicoContainer();

        pico.addComponent(new PlayerProvider(pico));
        pico.addComponent(Dealer.class);
        pico.addComponent(Deck.class);
        pico.addComponent(Blackjack.class);

        Blackjack blackjack = pico.getComponent(Blackjack.class);
        blackjack.addAllPlayers(pico);

        for (int i = 0; i < 40; i++) {
            blackjack.NewRound();
        }

        blackjack.printStats();
    }
}
