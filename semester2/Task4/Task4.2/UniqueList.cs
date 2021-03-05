namespace Task4._2
{
    /// <summary>
    /// Unique list on pointers implementation
    /// </summary>
    public class UniqueList: List
    {

        /// <summary>
        /// Adds unique value to the list
        /// </summary>
        /// <exception cref="ValueAlreadyExistsException">Throws if the value is already in the list</exception>
        public override void AddValue(int value)
        {
            if (head is null)
            {
                head = new ListElement(value);
            }
            else
            {
                if (head.Value == value)
                {
                    throw new ValueAlreadyExistsException();
                }
                ListElement cursor = head;
                while (cursor.Next is not null)
                {
                    cursor = cursor.Next; 
                    if (cursor.Value == value)
                    {
                        throw new ValueAlreadyExistsException();
                    }
                }
                cursor.Next = new ListElement(value);
            }
        }
    }
}
