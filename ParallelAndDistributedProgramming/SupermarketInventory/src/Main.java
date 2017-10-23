import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
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

    private static List<Bill> initBills(int ln) {
        Random rn = new Random();
        List<Bill> ret = new ArrayList<>();
        for(int i=0;i<ln;++i){
            ret.add(new Bill().withAmount(Math.abs(rn.nextInt()%3) + 1).withProductIdx(Math.abs(rn.nextInt()%4)));
        }
        return ret;
    }

    public static void main(String[] args) throws InterruptedException {

        List<Product> products = initProducts();
        int billNo = 50;
        List<Bill> bills = initBills(billNo);

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

                    while(true){
                        boolean productLocked = productRef.getProductLock().tryLock();
                        if(productLocked) break;
                        Thread.sleep(3000);
                    }
                    int gain = productRef.getAmount() * productRef.getPrice();
                    productRef.setAmount(productRef.getAmount() - bill.getAmount());

                    while (true) {
                        boolean soldItemsLocked = soldItemsLock.tryLock();
                        boolean totalGainLocked = totalGain.getTotalLock().tryLock();
                        if (soldItemsLocked && totalGainLocked) {
                            soldItems.add(bill.withSum(gain));

                            totalGain.add(gain);

                            productRef.getProductLock().unlock();
                            soldItemsLock.unlock();
                            totalGain.getTotalLock().unlock();
                            break;
                        }

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
