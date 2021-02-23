using System;
using System.Collections;

namespace Task2._1
{
    class Trie
    {
        public int value;
        private Trie parent;
        private Hashtable children;

        public Trie()
        {
            children = new Hashtable();
        }

        public Trie AddChild(char charChild)
        {
            Trie newChild = new Trie();
            newChild.parent = this;
            children.Add(charChild, newChild);
            return newChild;
        }

        public bool HasChild(char charChild)
        {
            return children.ContainsKey(charChild);
        }

        public Trie GetChild(char charChild)
        {
            return (Trie)children[charChild];
        }

        public bool HasParent()
        {
            return parent != null;
        }
    }
}
