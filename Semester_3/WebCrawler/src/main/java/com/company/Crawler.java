package com.company;

import org.jsoup.Connection;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.IOException;
import java.util.concurrent.ConcurrentSkipListSet;
import java.util.concurrent.ThreadPoolExecutor;

public class Crawler implements Runnable {
    private String address;
    private int currentDepth;
    private int maxDepth;
    //    private MyThreadPool pool;
//    private MyConcurrentQueue<String> urls;
    private ThreadPoolExecutor pool;
    private ConcurrentSkipListSet<String> urls;

    /*public Crawler(String url,
                   int currentDepth,
                   int maxDepth,
                   MyThreadPool threadPool,
                   MyConcurrentQueue<String> urls) {
        this.address = url;
        this.currentDepth = currentDepth;
        this.maxDepth = maxDepth;
        this.pool = threadPool;
        this.urls = urls;
    }*/
    public Crawler(String url,
                   int currentDepth,
                   int maxDepth,
                   ThreadPoolExecutor threadPool,
                   ConcurrentSkipListSet<String> urls) {
        this.address = url;
        this.currentDepth = currentDepth;
        this.maxDepth = maxDepth;
        this.pool = threadPool;
        this.urls = urls;
    }

    @Override
    public void run() {
        Document document;
        try {
            Connection connection = Jsoup.connect(address);
            document = connection.get();
        } catch (IOException e) {
            return;
        }
        Elements links = document.select("a[href]");
        if (currentDepth < maxDepth) {
            for (Element link : links) {
                String url = link.attr("abs:href");
                if (!urls.contains(url)) {
//                    urls.offer(url);
                    urls.add(url);
                    pool.execute(new Crawler(url, currentDepth + 1, maxDepth, pool, urls));
                } else {
                    System.out.println("Url " + url + " already processed");
                    // Already visited this url
                }
            }
        }
        pool.execute(new Saver(document));
    }
}
