public class Limousine extends Auto {
    private int length;

    public Limousine(int maxSpeed, int weight, int horsepower, String model, int yearOfManufacture, String countryOfManufacture, int price, int length) {
        super(maxSpeed, weight, horsepower, model, yearOfManufacture, countryOfManufacture, price);
        this.length = length;
    }

    public String getDetailedInfo() {
        return this.getBasicInfo() + "Length: " + length + "\n";
    }
}
