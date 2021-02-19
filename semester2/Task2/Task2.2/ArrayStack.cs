namespace Task2._2
{
    class ArrayStack: IStack
    {
        private double[] array;
        private int maxLength;
        private int length;

        public ArrayStack()
        {
            this.maxLength = 10;
            this.length = 0;
            this.array = new double[this.maxLength];
        }

        public void Push(double value)
        {
            if (length >= maxLength)
            {
                Extend();
            }
            array[length++] = value;
        }

        public bool TryPop(out double value)
        {
            if (length > 0)
            {
                value = array[--length];
                return true;
            }
            value = -1;
            return false;
        }

        private void Extend()
        {
            maxLength *= 2;
            var newArray = new double[maxLength];
            for (int i = 0; i < array.Length; i++)
            {
                newArray[i] = array[i];
            }
            array = newArray;
        }
    }
}
