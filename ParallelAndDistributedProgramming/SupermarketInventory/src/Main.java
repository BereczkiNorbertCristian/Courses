import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {

    private static List<Product> initProducts(){
        return Arrays.asList(
                new Product(3,10,"Soap"),
                new Product(7,20,"Banana"),
                new Product(5,23,"Carrot"),
                new Product(11,30,"Book")
        );
    }

    private static List<Bill> initBills(){
        return Arrays.asList(
                new Bill().withAmount(3).withProductIdx(0),
                new Bill().withAmount(10).withProductIdx(1),
                new Bill().withAmount(4).withProductIdx(0),
                new Bill().withAmount(11).withProductIdx(3)
        );
    }

    public static void main(String[] args) throws InterruptedException {

        List<Product> products = initProducts();
        List<Bill> bills = initBills();

        int billNo = bills.size();
        int queries = 3;

        List<Thread> threads = new ArrayList<>(billNo + queries);
        List<Bill> soldItems = new ArrayList<>(billNo);

        TotalAmount totalGain = new TotalAmount(0);

        for(Bill bill : bills){
            Runnable r = () -> {
                Product productRef = products.get(bill.getProductIdx());
                int gain = productRef.getAmount() * productRef.getPrice();
                soldItems.add(bill.withSum(gain));
                try {
                    Thread.sleep((long)(Math.random() * 1000));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                productRef.setAmount(productRef.getAmount() - bill.getAmount());
                totalGain.add(gain);
            };
            threads.add(new Thread(r));
        }

        for(int i=0;i<queries;++i){
            Runnable r = () -> {

                try {
                    Thread.sleep((long)(Math.random() * 1000));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                int itemsSum = computeCurrentSum(soldItems);
                System.out.println(String.format("%d ? %d ",totalGain.getTotal(),itemsSum));
            };
            threads.add(new Thread(r));
        }

        for(Thread thread : threads){
            thread.start();
        }
        for(Thread thread : threads){
            thread.join();
        }

        System.out.println("Done...");
    }

    static private int computeCurrentSum(List<Bill> soldItems){
        return soldItems.stream().mapToInt(bill -> bill.getSum()).sum();
    }

}
