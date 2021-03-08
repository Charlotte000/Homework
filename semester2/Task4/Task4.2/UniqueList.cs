namespace Task4._2
{
    /// <summary>
    /// Unique list on pointers implementation
    /// </summary>
    public class UniqueList: List
    {
        public override int this[int index]
        {
            get => GetElement(index).Value;
            set
            {
                if (IsExists(value))
                {
                    throw new ValueAlreadyExistsException();
                }
                GetElement(index).Value = value;
            }
        }


        /// <summary>
        /// Adds unique value to the list
        /// </summary>
        /// <exception cref="ValueAlreadyExistsException">Throws if the value is already in the list</exception>
        public override void AddValue(int value)
        {
            if (IsExists(value))
            {
                throw new ValueAlreadyExistsException();
            }
            base.AddValue(value);
        }

    }
}
