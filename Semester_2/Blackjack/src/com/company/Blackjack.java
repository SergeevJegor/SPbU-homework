package com.company;

import org.picocontainer.PicoContainer;
import java.util.ArrayList;

public class Blackjack implements Observer {

    private Deck deck;

    private Dealer dealer;
    private ArrayList<Player> players;

    private ArrayList<Player> playersFinished;
    private ArrayList<Player> playersSurrendered;

    private boolean dealerInPlay;

    public Blackjack(Dealer dealerArg, Deck deckArg) {
        this.dealer = dealerArg;
        this.dealer.setGameTable(this);

        this.players = new ArrayList<>();
        this.playersSurrendered = new ArrayList<>();
        this.playersFinished = new ArrayList<>();

        this.deck = deckArg;
        this.dealerInPlay = false;
    }

    public void addAllPlayers(PicoContainer pico) throws Exception {
        // Adding all players from container to blackjack table:
        for (Player player : pico.getComponent(PlayerProvider.class).getPlayers()) {
            addPlayer(player);
        }
    }

    private void giveStartingHand() {

        for (int i = 0; i < 2; i++) {

            dealer.hand.add(deck.Pop());
            for (Player player : players) {
                player.hand.add(deck.Pop());
            }
        }
    }

    private void giveCard(Player player) {
        player.hand.add(deck.Pop());
    }

    public void addPlayer(Player newPlayer) {
        this.players.add(newPlayer);
        newPlayer.setGameTable(this);
    }

    public void NewRound() {

        if (this.players.isEmpty())
            return;

        playersFinished.clear();
        playersSurrendered.clear();

        if (this.deck.getCurrentSize() < this.deck.getDefaultSize() * 2 / 3)
            deck.shuffle();

        dealerInPlay = true;

        for (Player player : players) {
            player.MakeBet();
        }

        giveStartingHand();

        for (Player player : players) {
            while (!(playersFinished.contains(player) || playersSurrendered.contains(player)))
                player.Play();
        }

        while (dealerInPlay)
            dealer.Play();

        for (Player player : playersFinished)
            playerFinish(player);

        for (Player player : playersSurrendered)
            playerSurrender(player);

        dealer.clearHand();

        for (int i = 0; i < players.size(); i++)
            if (players.get(i).getMoney() <= 0) players.remove(players.get(i));
    }

    private boolean checkIfBlackJack(Player player) {
        if (player.hand.size() == 2 && player.getScore() == 21)
            if (!(dealer.hand.size() == 2 && dealer.getScore() == 21)) {
                player.winMoney((player.getCurrentBet() * 3) / 2);
                player.clearHand();
                return true;
            }

        return false;
    }

    private void playerFinish(Player player) {
        if (checkIfBlackJack(player))
            return;

        Integer playerScore = player.getScore();
        Integer dealerScore = dealer.getScore();

        if (dealerScore > 21) {

            if (playerScore < dealerScore)
                player.winMoney(player.getCurrentBet());
            else
                player.loseMoney(player.getCurrentBet());

        } else if (playerScore <= 21 && playerScore > dealerScore) {
            player.winMoney(player.getCurrentBet());

        } else if (!playerScore.equals(dealerScore)) {
            player.loseMoney(player.getCurrentBet());
        }

        player.clearHand();
    }

    private void playerSurrender(Player player) {
        player.loseMoney(player.getCurrentBet() / 2);
        player.clearHand();
    }

    public void printStats() {
        for (Player player : this.players) {
            System.out.println(player.getStatistic());
        }
    }

    @Override
    public void onNotify(GameEvent event) {
        Player player = event.getEventSource();
        switch (event.getType()) {

            case HIT: {
                giveCard(player);
                break;
            }

            case SURRENDER: {
                playersSurrendered.add(player);
                break;
            }

            case STAND: {
                playersFinished.add(player);
                break;
            }

            case DOUBLE: {
                player.doubleDown();
                giveCard(player);
                playersFinished.add(player);
                break;
            }

            case DEALER_FINISH: {
                dealerInPlay = false;
                break;
            }
        }
    }
}
