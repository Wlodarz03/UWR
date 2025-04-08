import structures.OrderedList;

import java.util.Date;

public class Main {
    public static void main(String[] args) {
        OrderedList<Integer> intList = new OrderedList<>();
        intList.insert(5);
        intList.insert(3);
        intList.insert(8);
        intList.insert(5); // duplikat
        System.out.println("IntegerList: " + intList.toString());
        System.out.println("Min: " + intList.min());
        System.out.println("Max: " + intList.max());
        System.out.println("Czy jest 3: " + intList.search(3));
        System.out.println("Liczba elementow: " + intList.size());
        System.out.println("Na indexie 1: " + intList.at(1));
        System.out.println("Index elementu 8: " + intList.index(8));
        intList.remove(3);
        System.out.println("Po usunieciu 3: " + intList.toString());
        System.out.println("Czy jest 3 po usunieciu: " + intList.search(3));
        System.out.println("Liczba elementow po usunieciu: " + intList.size());

        OrderedList<String> stringList = new OrderedList<>();
        stringList.insert("cherry");
        stringList.insert("apple");
        stringList.insert("banana");
        System.out.println("\nStringList: " + stringList);

        OrderedList<Date> dateList = new OrderedList<>();
        dateList.insert(new Date(1000000000)); // 12 Jan
        dateList.insert(new Date(2000000000)); // 24 Jan
        dateList.insert(new Date(500000000)); // 06 Jan
        System.out.println("\nDateList: " + dateList);

        System.out.println("\nIteracja na StringList");
        for (String s : stringList) {
            System.out.print(s + " ");
        }
    }
}
