using System;

namespace Task4._1
{
    class Program
    {
        static void Main()
        {
            Console.Write("Input expression: ");
            string input = Console.ReadLine();
            var tree = new Tree(input);
            tree.DrawTree();
            Console.WriteLine("==========");
            Console.WriteLine($"Result: {tree.Calculate()}");
        }
    }
}
