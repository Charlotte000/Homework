using System;

namespace Task2._1
{
    class Trie
    {
        public int value;
        public Trie[] children;
        public Trie parent;
        public char[] characters;
        public int childrenLen;

        public Trie()
        {
            childrenLen = 0;
            children = new Trie[300];
            characters = new char[300];
        }

        public Trie AddChild(char charChild)
        {
            if (childrenLen + 1 >= children.Length)
            {
                Extend();
            }
            children[childrenLen] = new Trie();
            children[childrenLen].parent = this;
            characters[childrenLen] = charChild;
            return children[childrenLen++];
        }

        private void Extend()
        {
            int length = children.Length * 2;
            Array.Resize(ref children, length);
            Array.Resize(ref characters, length);
        }
    }
}
