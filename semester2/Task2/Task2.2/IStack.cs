namespace Task2._2
{
    interface IStack
    {
        void Push(double value);

        bool TryPop(out double value);
    }
}
