using System;

namespace Task3._1
{
    /// <summary>
    /// B-tree data structure implementation  
    /// </summary>
    public class BTree
    {
        private readonly int t;
        private BNode head;

        public BTree(int t)
        {
            this.t = t;
            head = new BNode(t, null);
        }

        /// <summary>
        /// Adds value into the tree if isn't existed;
        /// Otherwise changes it's value
        /// </summary>
        public void AddValue(int key, int value)
        {
            head.InsertValue(key, value, t);
        }

        /// <summary>
        /// Get's value by its key
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">Throws if value not found</exception>
        public int FindValue(int key)
        {
            return head.FindValue(key);
        }

        /// <summary>
        /// Checks object availability
        /// </summary>
        public bool IsExists(int key)
        {
            return head.IsExists(key);
        }

        /// <summary>
        /// Recursively draws entire tree
        /// </summary>
        public void PrintTree()
        {
            head.PrintValues();
        }

        /// <summary>
        /// Deletes values by the key
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">Throws if value not found</exception>
        public void DeleteValue(int key)
        {
            head.DeleteValue(key);
        }

        /// <summary>
        /// Node in the tree
        /// </summary>
        private class BNode
        {
            private bool isLeaf;
            private Data[] values;
            private BNode[] children;
            private int realLen;
            private BNode parent;

            public BNode(int t, BNode parent)
            {
                values = new Data[2 * t - 1];
                children = new BNode[2 * t];
                isLeaf = true;
                realLen = 0;
                this.parent = parent;
            }

            /// <summary>
            /// Prints node's information
            /// </summary>
            /// <param name="margin">Offset</param>
            public void PrintValues(int margin = 0)
            {
                for (int j = 0; j < margin; j++) Console.Write(' ');
                for (int i = 0; i < realLen; i++)
                {
                    Console.Write($"{values[i].Key}({values[i].Value}) ");
                }
                Console.WriteLine();

                for (int i = 0; i <= realLen; i++)
                {
                    if (children[i] != null) children[i].PrintValues(margin + 2);
                }
            }

            /// <summary>
            /// Recursively adds values into itself or it's children
            /// </summary>
            /// <param name="degree">Tree's degree</param>
            public void InsertValue(int key, int value, int degree)
            {
                if (isLeaf)
                {
                    if (realLen == 0)
                    {
                        values[0] = new Data(key, value);
                        realLen++;
                        return;
                    }
                    for (int i = 0; i < realLen; i++)
                    {
                        if (values[i].Key == key)
                        {
                            values[i].Value = value;
                            return;
                        }
                        if (values[i].Key > key)
                        {
                            values[realLen] = new Data(0, 0);
                            for (int j = realLen - 1; j >= i; j--)
                            {
                                values[j + 1].Key = values[j].Key;
                                values[j + 1].Value = values[j].Value;
                            }
                            values[i].Value = value;
                            realLen++;
                            TrySplit(degree);
                            return;
                        }
                    }
                    values[realLen] = new Data(key, value);
                    realLen++;
                    TrySplit(degree);
                    return;
                }

                if (key < values[0].Key)
                {
                    children[0].InsertValue(key, value, degree);
                    return;
                }
                if (values[realLen - 1].Key < key)
                {
                    children[realLen].InsertValue(key, value, degree);
                    return;
                }
                for (int i = 0; i < realLen; i++)
                {
                    if (values[i].Key < key && key < values[i + 1].Key)
                    {
                        children[i + 1].InsertValue(key, value, degree);
                        return;
                    }
                }
            }

            /// <summary>
            /// Recursively finds value 
            /// </summary>
            /// <exception cref="ArgumentOutOfRangeException">Throws if value not found</exception>
            public int FindValue(int key)
            {
                if (isLeaf)
                {
                    for (int i = 0; i < realLen; i++)
                    {
                        if (values[i].Key == key)
                        {
                            return values[i].Value;
                        }
                    }
                    throw new ArgumentOutOfRangeException("Value not found");
                }
                for (int i = 0; i < realLen; i++)
                {
                    if (values[i].Key == key)
                    {
                        return values[i].Value;
                    }
                    if (key < values[i].Key)
                    {
                        return children[i].FindValue(key);
                    }
                }
                if (values[realLen - 1].Key < key)
                {
                    return children[realLen].FindValue(key);
                }
                throw new ArgumentOutOfRangeException("Value not found");
            }

            /// <summary>
            /// Checks key-value availability
            /// </summary>
            public bool IsExists(int key)
            {
                if (isLeaf)
                {
                    for (int i = 0; i < realLen; i++)
                    {
                        if (values[i].Key == key)
                        {
                            return true;
                        }
                    }
                    return false;
                }
                for (int i = 0; i < realLen; i++)
                {
                    if (values[i].Key == key)
                    {
                        return true;
                    }
                    if (key < values[i].Key)
                    {
                        return children[i].IsExists(key);
                    }
                }
                if (values[realLen - 1].Key < key)
                {
                    return children[realLen].IsExists(key);
                }
                return false;
            }

            /// <summary>
            /// Recursively deletes value by the key
            /// </summary>
            public void DeleteValue(int key)
            {
                for (int i = 0; i < realLen; i++)
                {
                    if (values[i].Key == key)
                    {
                        if (isLeaf)
                        {
                            for (int j = i; j < realLen - 1; j++)
                            {
                                values[j] = values[j + 1];
                            }
                            realLen--;
                        }
                        else
                        {
                            if (children[i].realLen >= 1)
                            {
                                int keyTmp = values[i].Key;
                                int valueTmp = values[i].Value;
                                values[i].Key = children[i].values[children[i].realLen - 1].Key;
                                values[i].Value = children[i].values[children[i].realLen - 1].Value;
                                children[i].values[children[i].realLen - 1].Key = keyTmp;
                                children[i].values[children[i].realLen - 1].Value = valueTmp;
                                children[i].DeleteValue(key);
                            }
                        }
                        return;
                    }
                }
                
                if (isLeaf)
                {
                    throw new ArgumentOutOfRangeException("Value not found");
                }

                if (key < values[0].Key)
                {
                    children[0].DeleteValue(key);
                    return;
                }
                if (values[realLen - 1].Key < key)
                {
                    children[realLen].DeleteValue(key);
                    return;
                }
                for (int i = 0; i < realLen - 1; i++)
                {
                    if (values[i].Key < key && key < values[i + 1].Key)
                    {
                        children[i + 1].DeleteValue(key);
                        return;
                    }
                }
            }

            /// <summary>
            /// Splits node in case of overflow with children
            /// </summary>
            /// <param name="degree">Tree's degree</param>
            private void TrySplit(int degree)
            {
                if (realLen == 2 * degree - 1)
                {
                    isLeaf = false;
                    BNode left = new BNode(degree, this);
                    for (int i = 0; i < degree; i++)
                    {
                        if (i != degree - 1)
                        {
                            left.values[i] = values[i].Copy();
                        }
                        if (children[i] != null)
                        {
                            children[i].parent = left;
                            left.isLeaf = false;
                        }
                        left.children[i] = children[i];
                    }
                    left.realLen = degree - 1;
                    BNode right = new BNode(degree, this);
                    for (int i = 0; i < degree; i++)
                    {
                        if (i != degree - 1)
                        {
                            right.values[i] = values[degree + i].Copy();
                        }
                        if (children[degree + i] != null)
                        {
                            children[degree + i].parent = right;
                            right.isLeaf = false;
                        }
                        right.children[i] = children[degree + i];
                    }
                    right.realLen = degree - 1;
                    Data middle = values[(2 * degree - 1) / 2].Copy();

                    if (parent == null)
                    {
                        Array.Clear(values, 0, values.Length);
                        Array.Clear(children, 0, children.Length);
                        realLen = 1;
                        values[0] = middle;
                        children[0] = left;
                        children[1] = right;
                        return;
                    }
                    left.parent = parent;
                    right.parent = parent;
                    for (int i = 0; i < parent.realLen; i++)
                    {
                        if (parent.values[i].Key > middle.Key)
                        {
                            for (int j = parent.realLen - 1; j >= i; j--)
                            {
                                parent.values[j + 1] = parent.values[j].Copy();
                            }
                            parent.values[i].Key = middle.Key;
                            parent.values[i].Value = middle.Value;

                            for (int j = parent.realLen + 1; j > i; j--)
                            {
                                parent.children[j] = parent.children[j - 1];
                            }
                            parent.children[i] = left;
                            parent.children[i + 1] = right;
                            parent.realLen++;
                            parent.TrySplit(degree);
                            return;
                        }
                    }
                    parent.values[parent.realLen] = middle;
                    parent.children[parent.realLen] = left;
                    parent.children[parent.realLen + 1] = right;
                    parent.realLen++;
                    parent.TrySplit(degree);
                    return;
                }
            }
        }

        /// <summary>
        /// Key-value structure
        /// </summary>
        private class Data
        {
            public Data(int key, int value)
            {
                Key = key;
                Value = value;
            }

            public Data Copy()
            {
                return new Data(Key, Value);
            }

            public int Key { get; set; }

            public int Value { get; set; }
        }
    }
}
