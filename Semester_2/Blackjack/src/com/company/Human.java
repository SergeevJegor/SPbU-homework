package com.company;

import java.util.Scanner;

public class Human extends Player {

    private Scanner keyboard;

    public Human(String name, Integer money) {
        super(name, money);
        keyboard = new Scanner(System.in);

    }

    public void Play() {
        System.out.println("Your score is " + this.getScore());
        System.out.println("Choose number of action to do:\n" +
                "1. Take a card.\n" +
                "2. Surrender. \n" +
                "3. Double down!\n" +
                "4. Stand.");
        int playerChoice = keyboard.nextInt();
        while (playerChoice <= 0 || playerChoice > 4 || playerChoice == 3) {
            if (playerChoice == 3) {
                if (this.getMoney() - this.getCurrentBet() * 2 < 0)
                    System.out.println("You have not enough money to double. Choose another number of action:");
            } else
                System.out.println("You entered wrong action number, please try again:");
            playerChoice = keyboard.nextInt();
        }

        switch (playerChoice) {
            case 1:
                doNotify(new GameEvent(this, EventType.HIT));
                break;
            case 2:
                doNotify(new GameEvent(this, EventType.SURRENDER));
                break;
            case 3:
                doNotify(new GameEvent(this, EventType.DOUBLE));
                break;
            case 4:
                doNotify(new GameEvent(this, EventType.STAND));
                break;
        }

    }

    public void MakeBet() {
        System.out.println("Your account is " + this.getMoney() + ".");

        System.out.println("Enter amount of money to gamble:");
        int bet = keyboard.nextInt();

        while (bet <= 0 || bet > this.currentMoney) {
            System.out.println("You entered wrong number, please try again:");
            bet = keyboard.nextInt();
        }
        this.currentBet = bet;

        gamesPlayed++;
    }

    @Override
    public void GameOver() {
        System.out.println("You have lost all your money. Bad day.");
    }

    @Override
    public void winMoney(Integer money) {
        this.currentMoney += money;
        System.out.println("You won " + money + "! Your account is now " + this.getMoney() + ".");
    }

    @Override
    public void loseMoney(Integer money) {
        this.currentMoney -= money;
        System.out.println("You lost " + money + ". Your account is now " + this.getMoney() + ".");
    }

    @Override
    public void Draw() {
        System.out.println("Your score equals to dealer's. Returning the bet.");
    }
}
