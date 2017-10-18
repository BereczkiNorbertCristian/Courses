import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Main {

    private static List<Product> initProducts() {
        return Arrays.asList(
                new Product(3, 10, "Soap"),
                new Product(7, 20, "Banana"),
                new Product(5, 23, "Carrot"),
                new Product(11, 30, "Book")
        );
    }

    private static List<Bill> initBills() {
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

        Lock soldItemsLock = new ReentrantLock();

        for (Bill bill : bills) {
            Runnable r = () -> {
                try {
                    Thread.sleep((long) (Math.random() * 1000));

                    Product productRef = products.get(bill.getProductIdx());
                    while (true) {
                        boolean productLocked = productRef.getProductLock().tryLock();
                        boolean soldItemsLocked = soldItemsLock.tryLock();
                        boolean totalGainLocked = totalGain.getTotalLock().tryLock();
                        if (productLocked && soldItemsLocked && totalGainLocked) {
                            int gain = productRef.getAmount() * productRef.getPrice();
                            soldItems.add(bill.withSum(gain));

                            productRef.setAmount(productRef.getAmount() - bill.getAmount());
                            totalGain.add(gain);

                            productRef.getProductLock().unlock();
                            soldItemsLock.unlock();
                            totalGain.getTotalLock().unlock();
                            break;
                        }

                        if (productLocked) productRef.getProductLock().unlock();
                        if (soldItemsLocked) soldItemsLock.unlock();
                        if (totalGainLocked) totalGain.getTotalLock().unlock();

                        Thread.sleep(3000);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            };
            threads.add(new Thread(r));
        }

        for (int i = 0; i < queries; ++i) {
            Runnable r = () -> {

                try {
                    Thread.sleep((long) (Math.random() * 1000));

                    while (true) {
                        boolean totalGainLocked = totalGain.getTotalLock().tryLock();
                        boolean soldItemsLocked = soldItemsLock.tryLock();

                        if (totalGainLocked && soldItemsLocked) {
                            int itemsSum = computeCurrentSum(soldItems);
                            System.out.println(String.format("%d ? %d ", totalGain.getTotal(), itemsSum));

                            totalGain.getTotalLock().unlock();
                            soldItemsLock.unlock();
                            break;
                        }
                        if (totalGainLocked) totalGain.getTotalLock().unlock();
                        if (soldItemsLocked) soldItemsLock.unlock();

                        Thread.sleep(3000);
                    }

                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            };
            threads.add(new Thread(r));
        }

        for (Thread thread : threads) {
            thread.start();
        }
        for (Thread thread : threads) {
            thread.join();
        }

        System.out.println("Done...");
    }

    static private int computeCurrentSum(List<Bill> soldItems) {
        return soldItems.stream().mapToInt(bill -> bill.getSum()).sum();
    }

}
