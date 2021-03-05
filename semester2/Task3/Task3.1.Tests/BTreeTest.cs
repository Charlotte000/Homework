using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Task3._1.Tests
{
    [TestClass]
    public class BTreeTest
    {
        private BTree tree;

        [TestInitialize]
        public void Init()
        {
            tree = new BTree(3);
        }

        [TestMethod]
        public void AddValueTest()
        {
            tree.AddValue(1, 0);
            tree.AddValue(2, 0);
            tree.AddValue(20, 0);
            tree.AddValue(21, 0);
            tree.AddValue(22, 0);

            tree.AddValue(30, 0);
            tree.AddValue(31, 0);
            tree.AddValue(32, 0);

            tree.AddValue(3, 0);
            tree.AddValue(4, 0);
            tree.AddValue(5, 0);

            tree.AddValue(6, 0);
            tree.AddValue(7, 0);
            tree.AddValue(8, 6);

            tree.AddValue(23, 3);
            tree.AddValue(24, 0);
            tree.AddValue(25, 0);
            tree.AddValue(26, 0);
            tree.AddValue(27, 1);
            tree.AddValue(28, 0);
        }

        [TestMethod]
        public void FindValueTest()
        {
            tree.AddValue(1, 1);
            tree.AddValue(2, 2);
            tree.AddValue(20, 3);
            tree.AddValue(21, 4);
            tree.AddValue(22, 5);

            tree.AddValue(30, 6);
            tree.AddValue(31, 7);
            tree.AddValue(32, 8);

            tree.AddValue(3, 9);
            tree.AddValue(4, 10);
            tree.AddValue(5, 11);

            tree.AddValue(6, 12);
            tree.AddValue(7, 13);
            tree.AddValue(8, 14);

            tree.AddValue(23, 15);
            tree.AddValue(24, 16);
            tree.AddValue(25, 17);
            tree.AddValue(26, 18);
            tree.AddValue(27, 19);
            tree.AddValue(28, 20);

            Assert.AreEqual(13, tree.FindValue(7));
            Assert.AreEqual(15, tree.FindValue(23));
            Assert.AreEqual(1, tree.FindValue(1));
            Assert.ThrowsException<ArgumentOutOfRangeException>(() => tree.FindValue(0));
        }

        [TestMethod]
        public void IsExistsTest()
        {
            tree.AddValue(1, 2);
            tree.AddValue(2, 3);
            tree.AddValue(3, 4);
            tree.AddValue(4, 5);
            tree.AddValue(5, 6);
            tree.AddValue(6, 7);
            tree.AddValue(7, 8);

            Assert.AreEqual(true, tree.IsExists(5));
            Assert.AreEqual(false, tree.IsExists(0));
        }

        [TestMethod]
        public void PrintTreeTest()
        {
            tree.AddValue(1, 2);
            tree.AddValue(2, 3);
            tree.AddValue(3, 4);
            tree.AddValue(4, 5);
            tree.AddValue(5, 6);
            tree.AddValue(6, 7);
            tree.AddValue(7, 8);
            tree.PrintTree();
        }

        [TestMethod]
        public void DeleteValueTest()
        {
            tree.AddValue(1, 2);
            tree.AddValue(2, 3);
            tree.AddValue(3, 4);
            tree.AddValue(4, 5);
            tree.AddValue(5, 6);
            tree.AddValue(6, 7);
            tree.AddValue(7, 8);
            tree.DeleteValue(4);
            Assert.ThrowsException<ArgumentOutOfRangeException>(() => tree.DeleteValue(456));
            Assert.ThrowsException<ArgumentOutOfRangeException>(() => tree.FindValue(4));
        }
    }
}
