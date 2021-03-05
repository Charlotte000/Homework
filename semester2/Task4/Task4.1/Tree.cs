using System;

namespace Task4._1
{
    enum OPERATOR
    {
        ADD,
        SUB,
        MULT,
        DIV
    }

    public class Tree
    {
        private Node head;

        public Tree(string expression)
        {
            head = Read(expression, 0, out _);
        }

        private Node Read(string expression, int index, out int indexOut)
        {
            char operand = expression[index + 1];
            int leftIndex = index + 3;
            int rightIndex = index + 5;
            indexOut = index + 8;
            Node left;
            Node right;

            // Left
            if (expression[leftIndex] == '(')
            {
                left = Read(expression, leftIndex, out rightIndex);
            }
            else
            {
                left = new(' ');
                left.Result = int.Parse(expression[leftIndex].ToString());
            }

            // Right
            if (expression[rightIndex] == '(')
            {
                right = Read(expression, rightIndex, out indexOut);
            }
            else
            {
                right = new(' ');
                right.Result = int.Parse(expression[rightIndex].ToString());
            }
            var result = new Node(operand);
            result.Left = left;
            result.Right = right;
            return result;
        }

        public void DrawTree()
        {
            head.Draw(0);
        }

        public double Calculate()
        {
            head.Calculate();
            return head.Result;
        }

        private class Node
        {
            private readonly OPERATOR op;

            public Node(char operand)
            {
                switch (operand)
                {
                    case '+':
                        {
                            op = OPERATOR.ADD;
                            break;
                        }
                    case '-':
                        {
                            op = OPERATOR.SUB;
                            break;
                        }
                    case '*':
                        {
                            op = OPERATOR.MULT;
                            break;
                        }
                    case '/':
                        {
                            op = OPERATOR.DIV;
                            break;
                        }

                }
            }

            public double Result { get; set; }
            public Node Left { get; set; }
            public Node Right { get; set; }

            public void Calculate()
            {
                if (Left is null || Right is null)
                {
                    return;
                }
                Left.Calculate();
                Right.Calculate();
                switch (op)
                {
                    case OPERATOR.ADD:
                    {
                        Result = Left.Result + Right.Result;
                        break;
                    }
                    case OPERATOR.SUB:
                    {
                        Result = Left.Result - Right.Result;
                        break;
                    }
                    case OPERATOR.MULT:
                    {
                        Result = Left.Result * Right.Result;
                        break;
                    }
                    case OPERATOR.DIV:
                    {
                        if (Math.Abs(Right.Result) < .0001)
                        {
                            throw new DivideByZeroException();
                        }
                        Result = Left.Result / Right.Result;
                        break;
                    }
                }
            }

            public void Draw(int offset)
            {
                if (Left is not null)
                {
                    Left.Draw(offset + 1);
                }
                for (int i = 0; i < offset; i++)
                {
                    Console.Write('\t');
                }
                if (Left is not null)
                {
                    Console.WriteLine(op);
                }
                else
                {
                    Console.WriteLine(Result);
                }
                if (Right is not null)
                {
                    Right.Draw(offset + 1);
                }
            }
        }
    }
}
