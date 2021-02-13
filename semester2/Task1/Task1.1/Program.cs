using System;

namespace Task1._1
{
    class Program
    {
        static void BubbleSort(int[] array)
        {
            for (int i = 0; i < array.Length - 1; i++)
            {
                for (int j = i + 1; j < array.Length; j++)
                {
                    if (array[i] > array[j])
                    {
                        int temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;
                    }
                }
            }
        }

        static bool Test()
        {
            bool isPassed = true;

            int[] testArray1 = new int[3] { 1, 3, 2 };
            BubbleSort(testArray1);
            isPassed = testArray1[0] == 1 && testArray1[1] == 2 && testArray1[2] == 3;

            int[] testArray2 = new int[4] { -1, 0, -1, -1 };
            BubbleSort(testArray2);
            isPassed = testArray2[0] == -1 && testArray2[1] == -1 && testArray2[2] == -1 && testArray2[3] == 0;

            int[] testArray3 = new int[1] { 5 };
            BubbleSort(testArray3);
            isPassed = testArray3[0] == 5;

            return isPassed;
        }

        static void Main(string[] args)
        {
            if (!Test())
            {
                Console.WriteLine("Test Failed!");
                Environment.Exit(1);
            }

            Console.Write("Input numbers: ");
            string input = Console.ReadLine();
            string[] strNumbers = input.Split(' ');
            int[] numbers = new int[strNumbers.Length];

            for (int i = 0; i < strNumbers.Length; i++)
            {
                numbers[i] = int.Parse(strNumbers[i]);
            }

            BubbleSort(numbers);
            foreach (int num in numbers)
            {
                Console.Write($"{num} ");
            }
        }
    }
}
