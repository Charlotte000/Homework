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
            string btw = BWT(input);
            string reverse = ReversedBWT(btw);
            Console.WriteLine($"Encoded string:\t{btw}");
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

            for (int i = 0; i < input.Length; i++)
            {
                array[0][i] = input[i];
            }

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
            var array = new char[input.Length][];
            for (int i = 0; i < input.Length; i++)
            {
                array[i] = new char[input.Length];
            }

            for (int i = 0; i < input.Length; i++)
            {
                for (int j = 0; j < input.Length; j++)
                {
                    array[input.Length - 1 - i][j] = input[j];
                }
                SortTable2(array, input.Length - 1 - i);
            }

            var result = new char[input.Length - 1];
            for (int i = 1; i < input.Length; i++)
            {
                result[i - 1] = array[i][0];
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
        static void SortTable2(char[][] array, int lineIndex)
        {
            for (int compare1 = 0; compare1 < array[0].Length; compare1++)
            {
                for (int compare2 = 0; compare2 < compare1 + 1; compare2++)
                {
                    for (int k = lineIndex; k < array.Length; k++)
                    {
                        if (array[k][compare1] < array[k][compare2])
                        {
                            for (int l = lineIndex; l < array.Length; l++)
                            {
                                char temp = array[l][compare1];
                                array[l][compare1] = array[l][compare2];
                                array[l][compare2] = temp;
                            }
                            break;
                        }
                        else if (array[k][compare1] > array[k][compare2])
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}
