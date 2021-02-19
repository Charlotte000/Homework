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

            string[] commands = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);

            (string status, double value) = Calculate(commands);
            if (status == "ok")
            {
                Console.WriteLine($"Result: {value}");
            }
            else
            {
                Console.WriteLine(status);
            }
        }

        static (string, double) Calculate(string[] commands)
        {
            IStack stack = new ArrayStack();  // Or ListStack();
            foreach (var command in commands)
            {
                if (int.TryParse(command, out int valueIn))
                {
                    stack.Push(valueIn);
                }
                else
                {
                    if (stack.TryPop(out double valueOut2) && stack.TryPop(out double valueOut1))
                    {
                        switch (command)
                        {
                            case "+":
                                stack.Push(valueOut1 + valueOut2);
                                break;
                            case "-":
                                stack.Push(valueOut1 - valueOut2);
                                break;
                            case "*":
                                stack.Push(valueOut1 * valueOut2);
                                break;
                            case "/":
                                if (Math.Abs(valueOut2) < .001)
                                {
                                    return ("Error! Division by zero", -1);
                                }
                                stack.Push(valueOut1 / valueOut2);
                                break;
                            default:
                                return("Wrong Expression", -1);
                        }
                    }
                    else
                    {
                        return ("Wrong Expression", -1);
                    }
                }
            }

            if (stack.TryPop(out double result) && !stack.TryPop(out _))
            {
                return ("ok", result);
            }

            return ("Wrong Expression", -1);
        }

        static bool Test()
        {
            var isPassed = true;
            string status;
            double result;

            (status, result) = Calculate(new string[] {"1", "2", "+" });
            isPassed = isPassed && status == "ok" && result == 3;

            (status, _) = Calculate(new string[] { "5", "1", "1", "-", "/" });
            isPassed = isPassed && status == "Error! Division by zero";

            (status, _) = Calculate(new string[] { "5", "1", "999999", "/", "/" });
            isPassed = isPassed && status == "Error! Division by zero";

            (status, _) = Calculate(new string[] { "5", "1", "1", "-" });
            isPassed = isPassed && status == "Wrong Expression";

            return isPassed;
        }
    }
}
