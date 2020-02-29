import java.util.Random;

public class createRandomNum{
    public static void main(String [] args){
        int [] arr = new int [1000000];
        Random random = new Random();
        for (int i = 0; i < arr.length; i++) {
            arr[i] = random.nextInt(1000000) + 1; // random number between 1 and ...
        }
        for (int i = 0; i < arr.length; i++) {
            System.out.println(arr[i]);
        }
    }
}