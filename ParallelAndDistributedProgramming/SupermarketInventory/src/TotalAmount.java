/**
 * created by bnorbert on 18,10,2017
 * bnorbertcristian@gmail.com
 */
public class TotalAmount {

    private Integer total;

    public TotalAmount(Integer total){
        this.total = total;
    }

    public void add(Integer gain){
        total+=gain;
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
