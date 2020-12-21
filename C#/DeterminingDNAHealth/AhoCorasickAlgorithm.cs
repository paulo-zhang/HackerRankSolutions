using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DeterminingDNAHealth
{
    class AhoCorasickAlgorithm
    {
		private const int MaxStates = 1000000;
		private const int MaxChars = 26;

		private static int[] Out = new int[MaxStates];
		private static int[] FF = new int[MaxStates];
		private static int[,] GF = new int[MaxStates, MaxChars];
        private string[] keywords;

        public AhoCorasickAlgorithm(string[] keywords, char lowestChar = 'a', char highestChar = 'z')
        {
			this.keywords = keywords;
			BuildMatchingMachine(keywords, lowestChar, highestChar);
		}

		private int BuildMatchingMachine(string[] words, char lowestChar, char highestChar)
		{
			Out = Enumerable.Repeat(0, Out.Length).ToArray();
			FF = Enumerable.Repeat(-1, FF.Length).ToArray();

			for (int i = 0; i < MaxStates; ++i)
			{
				for (int j = 0; j < MaxChars; ++j)
				{
					GF[i, j] = -1;
				}
			}

			int states = 1;

			for (int i = 0; i < words.Length; ++i)
			{
				string keyword = words[i];
				int currentState = 0;

				for (int j = 0; j < keyword.Length; ++j)
				{
					int c = keyword[j] - lowestChar;

					if (GF[currentState, c] == -1)
					{
						GF[currentState, c] = states++;
					}

					currentState = GF[currentState, c];
				}

				Out[currentState] |= (1 << i);
			}

			for (int c = 0; c < MaxChars; ++c)
			{
				if (GF[0, c] == -1)
				{
					GF[0, c] = 0;
				}
			}

			List<int> q = new List<int>();
			for (int c = 0; c <= highestChar - lowestChar; ++c)
			{
				if (GF[0, c] != -1 && GF[0, c] != 0)
				{
					FF[GF[0, c]] = 0;
					q.Add(GF[0, c]);
				}
			}

			while (Convert.ToBoolean(q.Count))
			{
				int state = q[0];
				q.RemoveAt(0);

				for (int c = 0; c <= highestChar - lowestChar; ++c)
				{
					if (GF[state, c] != -1)
					{
						int failure = FF[state];

						while (GF[failure, c] == -1)
						{
							failure = FF[failure];
						}

						failure = GF[failure, c];
						FF[GF[state, c]] = failure;
						Out[GF[state, c]] |= Out[failure];
						q.Add(GF[state, c]);
					}
				}
			}

			return states;
		}

		private int FindNextState(int currentState, char nextInput, char lowestChar = 'a')
		{
			int answer = currentState;
			int c = nextInput - lowestChar;

			while (GF[answer, c] == -1)
			{
				answer = FF[answer];
			}

			return GF[answer, c];
		}

		public List<int> FindAllStates(string text, char lowestChar = 'a', char highestChar = 'z')
		{
			int currentState = 0;
			List<int> retVal = new List<int>();

			for (int i = 0; i < text.Length; ++i)
			{
				currentState = FindNextState(currentState, text[i], lowestChar);

				if (Out[currentState] == 0)
					continue;

				for (int j = 0; j < keywords.Length; ++j)
				{
					if (Convert.ToBoolean(Out[currentState] & (1 << j)))
					{
						retVal.Insert(0, i - keywords[j].Length + 1);
					}
				}
			}

			return retVal;
		}

		public int [] FindAllKeywordNextSearch(string text, char lowestChar = 'a', char highestChar = 'z')
		{
			int currentState = 0;
			int [] retVal = new int[keywords.Length];

			for (int i = 0; i < text.Length; ++i)
			{
				currentState = FindNextState(currentState, text[i], lowestChar);

				if (Out[currentState] == 0)
					continue;

				for (int j = 0; j < keywords.Length; ++j)
				{
					if (Convert.ToBoolean(Out[currentState] & (1 << j)))
					{
						retVal[j] ++;
					}
				}
			}

			return retVal;
		}
	}
}
