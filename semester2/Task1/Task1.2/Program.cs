using System;

namespace Task1._2
{
    class Program
    {

        const char StopCharacter = '$';

        static void Main(string[] args)
        {
            if (!Test())
            {
                Console.WriteLine("Test Failed!");
                Environment.Exit(1);
            }
            Console.Write("Input string:\t");
            string input = Console.ReadLine();
            string bwt = BWT(input);
            string reverse = ReversedBWT(bwt);
            Console.WriteLine($"Encoded string:\t{bwt}");
            Console.WriteLine($"Decoded string:\t{reverse}");
        }

        static bool Test()
        {
            bool isPassed = true;
            isPassed = isPassed && ReversedBWT(BWT("hello")) == "hello";
            isPassed = isPassed && ReversedBWT(BWT("banana")) == "banana";
            isPassed = isPassed && ReversedBWT(BWT("abcabc")) == "abcabc";
            isPassed = isPassed && ReversedBWT(BWT("ananas")) == "ananas";
            isPassed = isPassed && ReversedBWT(BWT("mississippi")) == "mississippi";
            return isPassed;
        }

        static string BWT(string input)
        {
            input += StopCharacter;
            var array = new char[input.Length][];
            for (int i = 0; i < input.Length; i++)
            {
                array[i] = new char[input.Length];
            }
            array[0] = input.ToCharArray();

            for (int i = 1; i < input.Length; i++)
            {
                for (int j = 0; j < input.Length; j++)
                {
                    int index = j - 1;
                    if (index < 0)
                    {
                        index += input.Length;
                    }
                    array[i][j] = array[i - 1][index];
                }
            }

            SortTable(array);

            var output = new char[input.Length];
            for (int i = 0; i < input.Length; i++)
            {
                output[i] = array[i][input.Length - 1];
            }
            return new string(output);
        }

        static string ReversedBWT(string input)
        {
            var array = input.ToCharArray();

            int[] permutation = GetPermutation(input);

            var newArray = new char[input.Length];
            var result = new char[input.Length - 1];
            for (int i = 0; i < input.Length; i++)
            {
                for (int j = 0; j < input.Length; j++)
                {
                    newArray[permutation[j]] = array[j];
                }

                for (int j = 0; j < input.Length; j++)
                {
                    array[j] = newArray[j];
                }
                if (i != 0)
                {
                    result[i - 1] = array[0];
                }
            }
            return new string(result);
        }

        static void SortTable(char[][] array)
        {
            for (int compare1 = 0; compare1 < array.Length; compare1++)
            {
                for (int compare2 = 0; compare2 < compare1 + 1; compare2++)
                {
                    for (int k = 0; k < array.Length; k++)
                    {
                        if (array[compare1][k] < array[compare2][k])
                        {
                            char[] temp = array[compare1];
                            array[compare1] = array[compare2];
                            array[compare2] = temp;
                            break;
                        }
                        else if (array[compare1][k] > array[compare2][k])
                        {
                            break;
                        }
                    }
                }
            }
        }

        static int[] GetPermutation(string input)
        {
            var array = input.ToCharArray();
            var permutation = new int[input.Length];

            for (int i = 0; i < input.Length; i++)
            {
                int minIndex = -1;
                for (int j = 0; j < input.Length; j++)
                {
                    if (array[j] != '\0')
                    {
                        if (minIndex == -1 || array[minIndex] > array[j])
                        {
                            minIndex = j;
                        }
                    }
                }
                permutation[minIndex] = i;
                array[minIndex] = '\0';
            }
            return permutation;
        }
    }
}
