package com.company;

import org.picocontainer.DefaultPicoContainer;
import org.picocontainer.MutablePicoContainer;

import java.lang.reflect.Constructor;
import java.net.URL;
import java.net.URLClassLoader;

public class Main {
    public static void main(String[] args) throws Exception {

        URL[] classLoaderUrls = new URL[]{new URL("file:///home/jegor/Projects/Java/Blackjack_UPD/src/plugins/NormalBot.jar")};
        URLClassLoader urlClassLoader = new URLClassLoader(classLoaderUrls);
        Class<?> normalBotClass = urlClassLoader.loadClass("plugins.NormalBot");

        MutablePicoContainer pico = new DefaultPicoContainer();

        pico.addComponent(Dealer.class);
        pico.addComponent(Deck.class);
        //pico.addComponent(Player.class);
        pico.addComponent(Blackjack.class);

        Blackjack blackjack = pico.getComponent(Blackjack.class);

        Constructor<?> constructor = normalBotClass.getDeclaredConstructor(Integer.class);
        pico.
        Player normalBot = (Player) constructor.newInstance(1000);

        //NormalBot normalBot = new NormalBot(1000, blackjack);
        RandomBot randomBot = new RandomBot(1000);

        blackjack.addPlayer(normalBot);
        blackjack.addPlayer(randomBot);

        for (int i = 0; i < 40; i++) {
            blackjack.NewRound();
        }

        System.out.println(normalBot.getStatistic("Normal bot"));
        System.out.println(randomBot.getStatistic("Random bot"));
    }
}
