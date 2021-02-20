using System;

namespace Task2._2
{
    class Program
    {
        static void Main(string[] args)
        {
            if (!Test())
            {
                Console.WriteLine("Test Failed!");
                Environment.Exit(1);
            }

            Console.Write("Input expression: ");
            string[] commands = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);

            (string status, double value) = Calculator.Calculate(commands, new ArrayStack());
            if (status == "ok")
            {
                Console.WriteLine($"Result: {value}");
            }
            else
            {
                Console.WriteLine(status);
            }
        }

        static bool Test()
        {
            var isPassed = true;
            string status;
            double result;

            (status, result) = Calculator.Calculate(new string[] {"1", "2", "+" }, new ArrayStack());
            isPassed = isPassed && status == "ok" && result == 3;

            (status, _) = Calculator.Calculate(new string[] { "5", "1", "1", "-", "/" }, new ListStack());
            isPassed = isPassed && status == "Error! Division by zero";

            (status, _) = Calculator.Calculate(new string[] { "5", "1", "999999", "/", "/" }, new ArrayStack());
            isPassed = isPassed && status == "Error! Division by zero";

            (status, _) = Calculator.Calculate(new string[] { "5", "1", "1", "-" }, new ListStack());
            isPassed = isPassed && status == "Wrong Expression";

            return isPassed;
        }
    }
}
