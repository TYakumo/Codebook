class Solution {
    static long modPow(long n, long p, long mod) {
        if (n == 0) {
            return 1;
        }

        long hf = modPow(n/2, p, mod);
        long mul = (n&1)*(p-1) + 1;
        return (((hf*hf)%mod)*mul) % mod;
    }

    static boolean primalityTest(long n, ArrayList <Long> primeWitness) {
        if (n <= 1 || n == 4) {
            return false;
        }

        for (int i = 0; i < primeWitness.size(); i++) {
            long phi = n-1;
            long pw = primeWitness.get(i).longValue();

            if (pw+2 >= n) {
                continue;
            }

            if (modPow(phi, pw, n) != 1) {
                return false;
            }

            long d = n-1;
            while (d % 2 == 0) {
                d /= 2;
            }

            boolean testOK = false;
            if (modPow(d, pw, n) == 1 || modPow(d, pw, n) == n-1) {
                testOK = true;
            }

            d *= 2;
            while (d < n-1 && !testOK) {
                if(modPow(d, pw, n) == n-1) {
                    testOK = true;
                }
                d *= 2;
            }

            if (!testOK) {
                return false;
            }
        }

        return true;
    }

    static ArrayList<Long> defaultWitness() {
        ArrayList<Long> ret = new ArrayList<Long>();

        ret.add(new Long(2));
        ret.add(new Long(3));
        ret.add(new Long(5));
        ret.add(new Long(7));
        ret.add(new Long(11));
        ret.add(new Long(13));
        ret.add(new Long(17));
        ret.add(new Long(19));
        ret.add(new Long(23));
        ret.add(new Long(29));
        ret.add(new Long(31));
        ret.add(new Long(37));

        return ret;
    }

    // Complete the primality function below.
    static String primality(int n) {
        if (primalityTest(n, defaultWitness())) {
            return "Prime";
        }
        return "Not prime";
    }
}