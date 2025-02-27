#pragma hdrstop
#pragma argsused

#include <chrono>
#include <ctime>
#include <iostream>
#include <bitset>
#include <map>
#include <cstring>
#include <cmath>
#include <vector>

#include <stdio.h>

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

using namespace std;
using namespace std::chrono;
class primeSieve
{
	private:
		long sieveSize = 0;
		vector<bool> Bits;
		const std::map<const long long, const int> resultsDictionary =
      {
            {          10LL, 4         },               // Historical data for validating our results - the number of primes
            {         100LL, 25        },               // to be found under some limit, such as 168 primes under 1000
            {        1000LL, 168       },
            {       10000LL, 1229      },
            {      100000LL, 9592      },
            {     1000000LL, 78498     },
            {    10000000LL, 664579    },
            {   100000000LL, 5761455   },
            {  1000000000LL, 50847534  },
            { 10000000000LL, 455052511 },

		};

      bool validateResults()
      {
          auto result = resultsDictionary.find(sieveSize);
          if (resultsDictionary.end() == result)
              return false;
          return result->second == countPrimes();
		}
   public:

		primeSieve(long n)
        : Bits(n, true), sieveSize(n)
      {
      }

		~primeSieve()
      {
      }

      void runSieve()
      {
          int factor = 3;
          int q = (int) sqrt(sieveSize);

          while (factor <= q)
          {
              for (int num = factor; num < sieveSize; num += 2)
              {
                  if (Bits[num])
                  {
                      factor = num;
                      break;
                  }
              }
              for (int num = factor * factor; num < sieveSize; num += factor * 2)
                  Bits[num] = false;

              factor += 2;
          }
      }

      void printResults(bool showResults, double duration, int passes)
      {
          if (showResults)
              printf("2, ");

          int count = (sieveSize >= 2);                             // Starting count (2 is prime)
          for (int num = 3; num <= sieveSize; num+=2)
          {
              if (Bits[num])
              {
                  if (showResults)
                      printf("%d, ", num);
                  count++;
              }
          }

          if (showResults)
              printf("\n");

          printf("Passes: %d, Time: %lf, Avg: %lf, Limit: %ld, Count1: %d, Count2: %d, Valid: %d\n",
                 passes,
                 duration,
                 duration / passes,
                 sieveSize,
                 count,
                 countPrimes(),
                 validateResults());
      }

      int countPrimes()
      {
          int count =  (sieveSize >= 2);;
          for (int i = 3; i < sieveSize; i+=2)
              if (Bits[i])
                  count++;
          return count;
		}
};
int _tmain(int argc, _TCHAR* argv[]) 
{
    auto passes = 0;
	auto tStart = steady_clock::now();

    while (true)
    {
		  primeSieve sieve(1000000L);
        sieve.runSieve();
        passes++;
        if (duration_cast<seconds>(steady_clock::now() - tStart).count() >= 5)
        {
            sieve.printResults(false, duration_cast<microseconds>(steady_clock::now() - tStart).count() / 1000000, passes);
            break;
        }
	 }
	 std::cin.ignore();
	return 0;
}
