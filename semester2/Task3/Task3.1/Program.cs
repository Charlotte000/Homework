using System;

namespace Task3._1
{
    class Program
    {
        static void Main(string[] args)
        {
            BTree tree = new BTree(3);
            tree.AddValue(1, 0);
            tree.AddValue(2, 0);
            tree.AddValue(20, 0);
            tree.AddValue(21, 0);
            tree.AddValue(22, 0);

            tree.AddValue(30, 0);
            tree.AddValue(31, 0);
            tree.AddValue(32, 0);

            tree.AddValue(3, 0);
            tree.AddValue(4, 0);
            tree.AddValue(5, 0);

            tree.AddValue(6, 0);
            tree.AddValue(7, 0);
            tree.AddValue(8, 6);

            tree.AddValue(23, 3);
            tree.AddValue(24, 0);
            tree.AddValue(25, 0);
            tree.AddValue(26, 0);
            tree.AddValue(27, 1);
            tree.AddValue(28, 0);

            // tree.AddValue(27, 2);

            tree.PrintTree();
        }
    }
}
