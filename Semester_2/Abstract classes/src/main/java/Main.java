public class Main {
    public static void main(String[] Args) {
        Limousine CadillacXTS = new Limousine(137, 5700, 350, "Cadillac XTS", 2012, "Japan", 587600, 5);
        SportCar HennesseyVenom = new SportCar(427, 1244, 1451, "Hennesey Venom GT", 2010, "USA", 1200000, 2.7);
        Bus Mercedes = new Bus(140, 9600, 422, "Mercedes-Benz Tourismo", 1995, "Germany", 156000, 52);

        System.out.println(CadillacXTS.getDetailedInfo());
        System.out.println(HennesseyVenom.getDetailedInfo());
        System.out.println(Mercedes.getDetailedInfo());
    }
}
