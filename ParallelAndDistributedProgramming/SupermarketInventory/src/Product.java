/**
 * created by bnorbert on 18,10,2017
 * bnorbertcristian@gmail.com
 */
public class Product {

    private final int price;
    private String productName;
    private int amount;

    public Product(final int price,int amount,String productName){
        this.price = price;
        this.amount = amount;
        this.productName = productName;
    }

    public String getProductName() {
        return productName;
    }

    public void setProductName(String productName) {
        this.productName = productName;
    }

    public int getPrice() {
        return price;
    }

    public int getAmount() {
        return amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    @Override
    public String toString() {
        return "Product{" +
                "price=" + price +
                ", productName='" + productName + '\'' +
                ", amount=" + amount +
                '}';
    }
}
