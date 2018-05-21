package com.company;

import org.picocontainer.MutablePicoContainer;

import java.io.BufferedReader;
import java.io.FileReader;
import java.lang.reflect.Constructor;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class PlayerProvider {

    private MutablePicoContainer pico;
    private Map<String, Class<?>> playersNames;

    public PlayerProvider(MutablePicoContainer inputPicoContainer) throws Exception {
        this.pico = inputPicoContainer;
        this.playersNames = new HashMap<>();
        mapClassesToNames();
    }

    public void registerPlayer(String name, Class<?> playerClass) {
        //pico.addComponent(Player.class, playerClass, new ComponentParameter(name));
        playersNames.put(name, playerClass);
    }

    public void mapClassesToNames() throws Exception {
        // Registering built-in bots:
        registerPlayer("Random bot", RandomBot.class);

        // Registering plugin bots:
        BufferedReader bufferedReader = new BufferedReader( new FileReader("/home/jegor/Projects/Java/Blackjack_1/src/plugins/pluginsConfig"));
        String line;

        while ((line = bufferedReader.readLine()) != null) {
            URL[] classLoaderUrls = new URL[]{(new URL("file:///home/jegor/Projects/Java/Blackjack_UPD/src/plugins/" + line + ".class"))};
            URLClassLoader urlClassLoader = new URLClassLoader(classLoaderUrls);
            Class<?> botClass = urlClassLoader.loadClass("plugins." + line);
            registerPlayer(line, botClass);
        }
    }

    public ArrayList<Player> getPlayers() throws Exception {
        ArrayList<Player> playersInstances = new ArrayList<>();

        for (Map.Entry<String, Class<?> > entry : this.playersNames.entrySet()) {
            Constructor<?> constructor = entry.getValue().getDeclaredConstructor(String.class, Integer.class);
            Player player = (Player) constructor.newInstance(entry.getKey(), 1000);
            playersInstances.add(player);
        }

        return playersInstances;
    }
}
