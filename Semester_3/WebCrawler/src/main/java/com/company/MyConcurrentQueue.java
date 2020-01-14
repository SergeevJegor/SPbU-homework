package com.company;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MyConcurrentQueue<T> {
    private Node<T> head;
    private Node<T> tail;
    private Lock lock = new ReentrantLock();

    public void offer(T value) {
        Node<T> node = new Node<>(value);
        try {
            lock.lock();
            if (head == null) {
                head = node;
                tail = node;
            } else {
                tail.setNext(node);
                tail = node;
            }
        } finally {
            lock.unlock();
        }
    }

    public T poll() {
        try {
            lock.lock();
            if (head != null) {
                Node<T> tmp = head;
                head = head.getNext();
                if (tmp == tail) {
                    tail = null;
                }
                return tmp.getValue();
            } else {
                return null;
            }
        } finally {
            lock.unlock();
        }
    }

    public boolean contains(T obj) {
        Node<T> tmp = head;
        while (tmp != null) {
            if (obj.equals(tmp.getValue())) {
                return true;
            }
            tmp = tmp.getNext();
        }
        return false;
    }

    public boolean isEmpty() {
        return head == null;
    }
}
