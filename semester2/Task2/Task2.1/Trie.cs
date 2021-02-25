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

        public Trie AddChild(byte keyByte)
        {
            Trie newChild = new Trie();
            newChild.parent = this;
            children.Add(keyByte, newChild);
            return newChild;
        }

        public bool HasChild(byte keyByte)
        {
            return children.ContainsKey(keyByte);
        }

        public Trie GetChild(byte keyByte)
        {
            return (Trie)children[keyByte];
        }

        public bool HasParent()
        {
            return parent != null;
        }
    }
}
