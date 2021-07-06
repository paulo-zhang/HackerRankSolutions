using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;


struct TrieNodeValue
{
    public int Index;
    public int Health;
}

class TrieNode
{
    public TrieNode[] Children = new TrieNode[26];
    public List<TrieNodeValue> TrieNodeValues = new List<TrieNodeValue>();
}

class Solution
{
    private TrieNode root = new TrieNode();

    public void BuildTrie(string word, int index, int health)
    {
        TrieNode node = root;
        for(int i = 0; i < word.Length; ++i)
        {
            int wordIndex = word[i] - 'a';
            var n = node.Children[wordIndex];
            if(n == null)
            {
                n = new TrieNode();
                node.Children[wordIndex] = n;
            }

            node = n;
        }

        node.TrieNodeValues.Add(new TrieNodeValue() { Index = index, Health = health });
    }

    public long GetHealth(string sequence, int start, int end)
    {
        long result = 0;

        for(int i = 0;i < sequence.Length; i ++)
        {
            int j = i;
            TrieNode node = root.Children[sequence[j] - 'a'];
            while(node != null)
            {
                foreach(var v in node.TrieNodeValues)
                {
                    if(v.Index >= start && v.Index <= end)
                    {
                        result += v.Health;
                        // Console.Write("gen: {0}, health: {1}; ", sequence.Substring(i, j - i + 1), v.Health);
                    }
                }

                if (++j >= sequence.Length) break;

                node = node.Children[sequence[j] - 'a'];
            }
        }

        // Console.WriteLine("result: {0}", result);
        return result;
    }

    public static void Main(string[] args)
    {
        var start = DateTime.Now;
        FileStream fileStream = new FileStream("input13.txt", FileMode.Open);
        using (StreamReader sr = new StreamReader(fileStream))
        {
            int n = Convert.ToInt32(sr.ReadLine().Trim());

            List<string> genes = sr.ReadLine().TrimEnd().Split(' ').ToList();

            List<int> health = sr.ReadLine().TrimEnd().Split(' ').ToList().Select(healthTemp => Convert.ToInt32(healthTemp)).ToList();

            int s = Convert.ToInt32(sr.ReadLine().Trim());

            Solution solution = new Solution();
            for (int i = 0; i < genes.Count; ++i)
            {
                solution.BuildTrie(genes[i], i, health[i]);
            }

            long minHealth = long.MaxValue, maxHealth = long.MinValue;
            for (int sItr = 0; sItr < s; sItr++)
            {
                string[] firstMultipleInput = sr.ReadLine().TrimEnd().Split(' ');

                int first = Convert.ToInt32(firstMultipleInput[0]);

                int last = Convert.ToInt32(firstMultipleInput[1]);

                string d = firstMultipleInput[2];

                long result = solution.GetHealth(d, first, last);

                minHealth = Math.Min(result, minHealth);
                maxHealth = Math.Max(result, maxHealth);
            }

            Console.Write("{0} {1}", minHealth, maxHealth);
            Console.WriteLine("\n" + (DateTime.Now - start).TotalMilliseconds);
            Console.Read();
        }
    }
}
