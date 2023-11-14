import java.util.Scanner;

public class PalindromeSubstring {

    public static boolean isPalindrome(String s) {
        for (int i = 0; i < s.length() / 2; i++) {
            if (s.charAt(i) != s.charAt(s.length() - i - 1)) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int palindromeLen = scanner.nextInt();
        int len = scanner.nextInt();
        String s = scanner.next();

        for (int i = 0; i <= s.length() - palindromeLen; i++) {
            String substrToCheck = s.substring(i, i + palindromeLen);
            if (isPalindrome(substrToCheck)) {
                System.out.println(substrToCheck);
                break;
            }
        }

        scanner.close();
    }
}