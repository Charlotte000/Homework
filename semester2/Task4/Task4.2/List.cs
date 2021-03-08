using System;

namespace Task4._2
{
    /// <summary>
    /// List on pointers implementation
    /// </summary>
    public class List
    {
        protected ListElement head;
        protected ListElement tail;
        
        /// <summary>
        /// Adds value to the list
        /// </summary>
        public virtual void AddValue(int value)
        {
            if (head is null)
            {
                head = new ListElement(value);
                tail = head;
            }
            else
            {
                tail.Next = new ListElement(value);
                tail = tail.Next;
            }
        }

        /// <summary>
        /// Gets value by its index
        /// </summary>
        /// <exception cref="IndexOutOfRangeException">Throws if index is out of lists length</exception>
        public int GetValue(int index)
            => GetElement(index).Value;

        /// <summary>
        /// Deletes value by the index
        /// </summary>
        /// <exception cref="ValueDoesNotExist">Throws if the index is out of boundaries</exception>
        public void DeleteValue(int index)
        {
            if (index == 0)
            {
                if (head == null)
                {
                    throw new ValueDoesNotExist();
                }
                head = head.Next;
            }
            else
            {
                try
                {
                    ListElement cursor = GetElement(index - 1);
                    if (cursor.Next is null)
                    {
                        throw new ValueDoesNotExist();
                    }
                    cursor.Next = cursor.Next.Next;
                }
                catch (IndexOutOfRangeException)
                {
                    throw new ValueDoesNotExist();
                }
            }
        }

        /// <summary>
        /// Checks object availability in the container
        /// </summary>
        public bool Exists(int value)
        {
            if (head is not null && head.Value == value)
            {
                return true;
            }
            ListElement cursor = head;
            while (cursor?.Next is not null)
            {
                cursor = cursor.Next;
                if (cursor.Value == value)
                {
                    return true;
                }
            }
            return false;
        }

        public virtual int this[int index]
        {
            get => GetElement(index).Value;
            set => GetElement(index).Value = value;
        }

        /// <summary>
        /// Returns value by its index
        /// </summary>
        /// <exception cref="IndexOutOfRangeException">Throws if index is out of lists length</exception>
        protected ListElement GetElement(int index)
        {
            if (head == null)
            {
                throw new IndexOutOfRangeException();
            }
            ListElement cursor = head;
            for (int i = 0; i < index; i++)
            {
                cursor = cursor.Next;
                if (cursor is null)
                {
                    throw new IndexOutOfRangeException();
                }
            }
            return cursor;
        }

        protected class ListElement
        {
            public ListElement(int value)
            {
                Value = value;
                Next = null;
            }

            public int Value { get; set; }

            public ListElement Next { get; set; }
        }
    }
}
