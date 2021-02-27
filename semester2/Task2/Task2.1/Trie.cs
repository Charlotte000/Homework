using System;
using System.IO;
using System.Collections;

namespace Task2._1
{
    /// <summary>
    /// Prefix tree realization
    /// </summary>
    class Trie
    {
        private int counter;
        private TrieElement head;
        private TrieElement cursor;

        public Trie()
        {
            counter = 1;
            head = new TrieElement();
            cursor = head;
        }

        /// <summary>
        /// Adds a value to the tree
        /// </summary>
        /// <returns>True - if new node is created, otherwise - false</returns>
        public bool TryAdd(byte value)
        {
            if (cursor.HasChild(value))
            {
                cursor = cursor.GetChild(value);
                return false;
            }
            cursor.AddChild(counter, value);
            counter++;
            return true;
        }

        /// <summary>
        /// Saves node in file
        /// </summary>
        public void SaveTrieElement(byte value, FileStream file)
        {
            int writeValue = cursor.HasParent() ? cursor.Value : 0;
            byte[] bytes = BitConverter.GetBytes(writeValue);
            Array.Resize(ref bytes, (int)(Math.Ceiling(Math.Log2(counter) / 8)));
            file.Write(bytes);
            file.WriteByte(value);
        }

        /// <summary>
        /// Saves node count
        /// </summary>
        public void SaveTrieCount(FileStream file)
            => file.Write(BitConverter.GetBytes(counter));

        /// <summary>
        /// Sets the cursor back to the head
        /// </summary>
        public void ResetCursor()
            => cursor = head;

        private class TrieElement
        {
            public int Value { get; set; }
            private TrieElement parent;
            private Hashtable children;

            public TrieElement()
                => children = new Hashtable();

            public void AddChild(int value, byte keyByte)
            {
                var newChild = new TrieElement();
                newChild.parent = this;
                newChild.Value = value;
                children.Add(keyByte, newChild);
            }

            public bool HasChild(byte keyByte)
                => children.ContainsKey(keyByte);

            public TrieElement GetChild(byte keyByte)
                => (TrieElement)children[keyByte];

            public bool HasParent()
                => parent != null;
        }
    }


}
