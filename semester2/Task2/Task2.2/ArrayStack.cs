using System;

namespace Task2._2
{
    class ArrayStack: IStack
    {
        private double[] values;
        private int currentLength;

        public ArrayStack()
        {
            this.currentLength = 0;
            this.values = new double[10];
        }

        public void Push(double value)
        {
            if (currentLength >= values.Length)
            {
                Extend();
            }
            values[currentLength++] = value;
        }

        public bool TryPop(out double value)
        {
            if (currentLength > 0)
            {
                value = values[--currentLength];
                return true;
            }
            value = -1;
            return false;
        }

        private void Extend()
        {
            Array.Resize(ref values, values.Length * 2);
        }
    }
}
