import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class PeopleList {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int nPeople = scanner.nextInt();

        int[] receivers = new int[nPeople];
        for (int i = 0; i < nPeople; ++i) {
            receivers[i] = scanner.nextInt();
        }

        final int CEO_INDEX = 0;
        Integer[] peopleList = new Integer[nPeople + 1];
        for (int i = CEO_INDEX; i <= nPeople; ++i) {
            peopleList[i] = i;
        }

        List<Integer> resultList = Arrays.stream(peopleList)
                .filter(person -> !Arrays.stream(receivers).anyMatch(r -> r == person))
                .collect(Collectors.toList());

        System.out.println(String.join(" ", resultList.stream().map(String::valueOf).collect(Collectors.toList())));

        scanner.close();
    }
}