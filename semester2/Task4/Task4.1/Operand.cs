using System;

namespace Task4._1
{
    /// <summary>
    /// A number tree node without child
    /// </summary>
    class Operand: ITreeNode
    {
        private double value;

        public Operand(int value)
            => this.value = value;

        public double Calculate()
            => value;

        public void Draw(int offset)
        {
            for (int i = 0; i < offset; i++)
            {
                Console.Write('\t');
            }
            Console.WriteLine(value);
        }
    }
}
