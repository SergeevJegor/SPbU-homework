public class Bus extends Auto {
    private int capacity;

    public Bus(int maxSpeed, int weight, int horsepower, String model, int yearOfManufacture, String countryOfManufacture, int price, int capacity) {
        super(maxSpeed, weight, horsepower, model, yearOfManufacture, countryOfManufacture, price);
        this.capacity = capacity;
    }

    @Override
    public String getDetailedInfo() {
        return ("Capacity: " + capacity + "\n");
    }
}
