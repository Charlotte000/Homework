namespace Task2._2
{
    class ListStack: IStack
    {
        private StackElement head;

        public void Push(double value)
            => head = head == null ? new StackElement(value, null) : new StackElement(value, head);

        public bool TryPop(out double value)
        {
            if (head == null)
            {
                value = -1;
                return false;
            }
            value = head.value;
            head = head.next;
            return true;
        }

        private class StackElement
        {
            public double value;
            public StackElement next;    

            public StackElement(double value, StackElement next)
            {
                this.value = value;
                this.next = next;
            }
        }
    }
}
