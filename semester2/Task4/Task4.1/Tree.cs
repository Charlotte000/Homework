using System;

namespace Task4._1
{
    /// <summary>
    /// Expression tree implementation
    /// </summary>
    public class Tree
    {
        private Operator head;

        public Tree(string expression)
        {
            string[] commands = expression.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            int index = 0;
            head = Read(commands, 0, ref index) as Operator;
        }

        /// <summary>
        /// Draws tree structure in the console
        /// </summary>
        public void DrawTree()
            => head.Draw(0);

        /// <summary>
        /// Recursively calculates expression value
        /// </summary>
        public double Calculate()
            => head.Calculate();

        private ITreeNode Read(string[] commands, int indexIn, ref int indexOut)
        {
            char op = commands[indexIn][1];

            ITreeNode left;
            ITreeNode right;
            indexOut = indexIn + 2;

            if (commands[indexIn + 1][0] != '(')
            {
                left = new Operand(int.Parse(commands[indexIn + 1]));
            }
            else
            {
                left = Read(commands, indexIn + 1, ref indexOut);
            }

            if (commands[indexOut][0] != '(')
            {
                string rValue = commands[indexOut].Remove(commands[indexOut].Length - 1, 1);
                while (rValue.Length > 0)
                {
                    if (rValue[rValue.Length - 1] == ')')
                    {
                        rValue = rValue.Remove(rValue.Length - 1, 1);
                    }
                    else
                    {
                        break;
                    }
                }
                right = new Operand(int.Parse(rValue));
                indexOut++;
            }
            else
            {
                right = Read(commands, indexOut, ref indexOut);
            }

            ITreeNode head = new Operator(op, left, right);
            return head;
        }
    }
}
