using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DeterminingDNAHealth
{
    class Program
    {
        static void Main(string[] args)
        {
            byte[] inputBuffer = new byte[1024 * 1024];
            Stream inputStream = Console.OpenStandardInput(inputBuffer.Length);
            Console.SetIn(new StreamReader(inputStream, Console.InputEncoding, false, inputBuffer.Length));


            int n = Convert.ToInt32(Console.ReadLine());

            string[] genes = Console.ReadLine().Split(' ');

            int[] health = Array.ConvertAll(Console.ReadLine().Split(' '), healthTemp => Convert.ToInt32(healthTemp));
            int s = Convert.ToInt32(Console.ReadLine());

            int min = -1, max = 0;
            for (int sItr = 0; sItr < s; sItr++)
            {
                string[] firstLastd = Console.ReadLine().Split(' ');

                int first = Convert.ToInt32(firstLastd[0]);

                int last = Convert.ToInt32(firstLastd[1]);

                string d = firstLastd[2];

                int h = GetHealthWithAhoCorasickAlgorithm2(genes, health, first, last, d);

                if (min == -1 || min > h)
                {
                    min = h;
                }

                if (max < h)
                {
                    max = h;
                }
            }

            Console.Write("{0} {1}", min, max);
            Console.Read();
        }

        private static int GetHealthWithAhoCorasickAlgorithm2(string[] genes, int[] health, int first, int last, string d)
        {
            int h = 0;
            AhoCorasickAlgorithm ahoCorasickAlgorithm = new AhoCorasickAlgorithm(genes);
            int[] result = ahoCorasickAlgorithm.FindAllKeywordNextSearch(d);
            
            for(int i = first; i <= last; i ++)
            {
                h += result[i] * health[i];
            }

            return h;
        }

        private static int GetHealthByTraverseStrandOnce(string[] genes, int[] health, int first, int last, string d)
        {
            int h = 0;
            for (int i = 0; i < d.Length; i++)
            {
                for(int j = first; j <= last;j ++)
                {
                    if (i + genes[j].Length <= d.Length && genes[j] == d.Substring(i, genes[j].Length))
                    {
                        // matched.
                        h += health[j];
                    }
                }
            }

            return h;
        }

        private static int GetHealthWithAhoCrosickAlgorithm(string[] genes, int[] health, int first, int last, string d)
        {
            int len = last - first + 1;
            string[] keywords = new string[len];
            Array.Copy(genes, first, keywords, 0, len);
            StringSearch stringSearch = new StringSearch(keywords);
            var result = stringSearch.FindKeywordOccurency(d);

            int h = 0;
            for (int i = first; i <= last; i++)
            {
                string key = genes[i];
                result.TryGetValue(key, out int count);
                h += count * health[i];
            }

            return h;
        }
    }
}
