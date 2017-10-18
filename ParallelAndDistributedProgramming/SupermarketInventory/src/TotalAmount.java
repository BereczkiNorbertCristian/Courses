import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * created by bnorbert on 18,10,2017
 * bnorbertcristian@gmail.com
 */
public class TotalAmount {

    private Integer total;
    private Lock totalLock;

    public TotalAmount(Integer total) {
        this.total = total;
        this.totalLock = new ReentrantLock();
    }

    public Lock getTotalLock() {
        return totalLock;
    }

    public void setTotalLock(Lock totalLock) {
        this.totalLock = totalLock;
    }

    public void add(Integer gain) {
        total += gain;
    }

    public Integer getTotal() {
        return total;
    }

    public void setTotal(Integer total) {
        this.total = total;
    }

    @Override
    public String toString() {
        return "TotalAmount{" +
                "total=" + total +
                '}';
    }
}
