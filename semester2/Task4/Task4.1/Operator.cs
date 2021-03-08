using System;

namespace Task4._1
{
    /// <summary>
    /// Operator tree node, calculates its value by its left and right child
    /// </summary>
    class Operator : ITreeNode
    {
        private ITreeNode left;
        private ITreeNode right;

        private char op;

        public Operator(char op, ITreeNode left, ITreeNode right)
        {
            this.op = op;
            this.left = left;
            this.right = right;
        }

        public double Calculate()
        {
            return op switch
            {
                '+' => left.Calculate() + right.Calculate(),
                '-' => left.Calculate() - right.Calculate(),
                '*' => left.Calculate() * right.Calculate(),
                '/' => Divide(left, right),
                _ => throw new ArgumentException()
            };
        }

        public void Draw(int offset)
        {
            if (left is not null)
            {
                left.Draw(offset + 1);
            }
            for (int i = 0; i < offset; i++)
            {
                Console.Write('\t');
            }
            Console.WriteLine(op);
            if (right is not null)
            {
                right.Draw(offset + 1);
            }
        }

        private static double Divide(ITreeNode left, ITreeNode right)
        {
            double v1 = left.Calculate();
            double v2 = right.Calculate();
            if (Math.Abs(v2) < .0001)
            {
                throw new DivideByZeroException();
            }
            return v1 / v2;
        }
    }
}
