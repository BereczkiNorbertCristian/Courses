import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * created by bnorbert on 18,10,2017
 * bnorbertcristian@gmail.com
 */
public class Product {

    private final int price;
    private String productName;
    private int amount;
    private Lock productLock;

    public Product(final int price, int amount, String productName) {
        this.price = price;
        this.amount = amount;
        this.productName = productName;
        productLock = new ReentrantLock();
    }

    public Lock getProductLock() {
        return productLock;
    }

    public void setProductLock(Lock productLock) {
        this.productLock = productLock;
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
