import java.util.Scanner;

public class RamaNumber {

    public static boolean isRamaNo(long n) {
        if ((n % 7) == 3 || (n % 7) == 4) {
            return false;
        }
        int j = (int) Math.floor(Math.cbrt(n));
        int j_cube = (int) Math.pow(j, 3);
        int i = (int) Math.floor(Math.cbrt(n - j_cube));
        int count = 0;
        while (i <= j) {
            long val = (long) Math.pow(i, 3) + j_cube;
            if (val == n) {
                count += 1;
            } else if (val > n) {
                j -= 1;
                j_cube = (int) Math.pow(j, 3);
                i = (int) Math.floor(Math.cbrt(n - j_cube));
                continue;
            }
            i += 1;
        }
        return count >= 2;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        long numberToCheck;
        while (T-- > 0) {
            numberToCheck = scanner.nextLong();
            if (isRamaNo(numberToCheck)) {
                System.out.println(1);
            } else {
                System.out.println(0);
            }
        }
        scanner.close();
    }
}
