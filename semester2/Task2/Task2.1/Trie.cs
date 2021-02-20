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
            children = new Trie[10];
            characters = new char[10];
        }

        public Trie AddChild(char charChild)
        {
            if (childrenLen < children.Length)
            {
                Extend();
            }
            children[childrenLen] = new Trie();
            children[childrenLen].parent = this;
            characters[childrenLen++] = charChild;
            return children[childrenLen - 1];
        }

        private void Extend()
        {
            Array.Resize(ref children, children.Length * 2);
            Array.Resize(ref characters, characters.Length * 2);
        }
    }
}
