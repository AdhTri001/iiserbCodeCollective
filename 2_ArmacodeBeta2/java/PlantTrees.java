import java.util.*;

public class OxygenLevels {

    static class TupleL3 implements Comparable<TupleL3> {
        long first, second, third;

        TupleL3(long a, long b, long c) {
            first = a;
            second = b;
            third = c;
        }

        @Override
        public int compareTo(TupleL3 other) {
            return Long.compare(this.second, other.second);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int N = scanner.nextInt();
        TupleL3[] vals = new TupleL3[N];

        for (int i = 0; i < N; ++i) {
            long i_start = scanner.nextLong();
            long i_end = scanner.nextLong();
            long i_oxygen = scanner.nextLong();
            vals[i] = new TupleL3(i_start, i_end, i_oxygen);
        }

        Arrays.sort(vals);

        TreeMap<Long, Long> oxygenSoFar = new TreeMap<>();
        oxygenSoFar.put(0L, 0L);
        long maxOxygen = 0;

        for (int i = 0; i < N; ++i) {
            long start = vals[i].first;
            long end = vals[i].second;
            long oxy = vals[i].third;

            Map.Entry<Long, Long> lowerBound = oxygenSoFar.floorEntry(start - 1);

            oxy += lowerBound.getValue();
            maxOxygen = Math.max(oxy, maxOxygen);
            oxygenSoFar.put(end, maxOxygen);
        }

        System.out.println(maxOxygen);
        scanner.close();
    }
}
