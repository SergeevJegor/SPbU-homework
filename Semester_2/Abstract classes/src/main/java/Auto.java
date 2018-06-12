public class Auto {
    private int maxSpeed;
    private int weight;
    private int horsepower;
    private String model;
    private int yearOfManufacture;
    private String countryOfManufacture;
    private int price;

    public Auto(int maxSpeed, int weight, int horsepower, String model, int yearOfManufacture, String countryOfManufacture, int price) {
        this.maxSpeed = maxSpeed;
        this.weight = weight;
        this.horsepower = horsepower;
        this.model = model;
        this.price = price;
        this.yearOfManufacture = yearOfManufacture;
        this.countryOfManufacture = countryOfManufacture;
    }

    public String getBasicInfo() {
        return ("Model: " + model + "\n" +
                "Year of manufacture: " + yearOfManufacture + "\n" +
                "Country of manufacture: " + countryOfManufacture + "\n" +
                "Price: " + price + "\n" +
                "Maximum speed: " + maxSpeed + "\n" +
                "Weight: " + weight + "\n" +
                "Horsepower: " + horsepower + "\n");
    }
}
