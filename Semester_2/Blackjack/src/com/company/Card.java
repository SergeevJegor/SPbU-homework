package com.company;

public class Card {

    private CardSuits suit;
    private CardRanks rank;
    private Integer value;

    Card(CardSuits suit, CardRanks rank) {

        this.suit = suit;
        this.rank = rank;

        switch (this.rank) {

            case Two: {
                this.value = 2;
                break;
            }
            case Three: {
                this.value = 3;
                break;
            }
            case Four: {
                this.value = 4;
                break;
            }
            case Five: {
                this.value = 5;
                break;
            }
            case Six: {
                this.value = 6;
                break;
            }
            case Seven: {
                this.value = 7;
                break;
            }
            case Eight: {
                this.value = 8;
                break;
            }
            case Nine: {
                this.value = 9;
                break;
            }
            case Ten: {
                this.value = 10;
                break;
            }
            case Jack: {
                this.value = 10;
                break;
            }
            case Queen: {
                this.value = 10;
                break;
            }
            case King: {
                this.value = 10;
                break;
            }
            case Ace: {
                this.value = 1;
                break;
            }
        }
    }

    public CardRanks getRank() {
        return this.rank;
    }

    public Integer getValue() {
        return this.value;
    }

}
