using System;

namespace Task2._2
{
    class Calculator
    {
        static public (string, double) Calculate(string[] commands, IStack stack)
        {
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
                                return ("Wrong Expression", -1);
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
    }
}
