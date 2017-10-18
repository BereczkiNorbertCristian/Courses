/**
 * created by bnorbert on 18,10,2017
 * bnorbertcristian@gmail.com
 */
public class Bill {

    private int productIdx;
    private int amount;
    private int sum;

    public Bill() {
    }

    public int getProductIdx() {
        return productIdx;
    }

    public void setProductIdx(int productIdx) {
        this.productIdx = productIdx;
    }

    public int getSum() {
        return sum;
    }

    public void setSum(int sum) {
        this.sum = sum;
    }

    public int getAmount() {
        return amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    public Bill withProductIdx(int productIdx) {
        this.productIdx = productIdx;
        return this;
    }

    public Bill withSum(int sum) {
        this.sum = sum;
        return this;
    }

    public Bill withAmount(int amount) {
        this.amount = amount;
        return this;
    }

    @Override
    public String toString() {
        return "Bill{" +
                "productIdx=" + productIdx +
                ", amount=" + amount +
                ", sum=" + sum +
                '}';
    }
}
