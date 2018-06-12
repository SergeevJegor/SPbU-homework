package com.company;

import java.util.ArrayList;
import java.util.Random;

public class Deck {

    private final Integer decksNumber = 8;
    private final Integer deckSize = 52;

    private ArrayList<Card> cards;
    private Integer currentSize;

    public Deck() {
        shuffle();
    }

    public void shuffle() {
        cards = new ArrayList<>(decksNumber);
        currentSize = decksNumber * deckSize;

        for (CardSuits suit : CardSuits.values())
            for (CardRanks rank : CardRanks.values()) {
                for (int i = 0; i < decksNumber; i++) cards.add(new Card(suit, rank));
            }
    }

    public Integer getCurrentSize() {
        return currentSize;
    }

    public Integer getDefaultSize() {
        return decksNumber * deckSize;
    }

    public Card Pop() {
        Random rnd = new Random(System.currentTimeMillis());
        Integer temp = rnd.nextInt(currentSize);

        Card result = cards.get(temp);
        cards.remove(temp);

        return result;
    }

}
