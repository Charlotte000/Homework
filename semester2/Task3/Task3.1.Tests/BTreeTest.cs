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
            tree.AddValue("1", "0");
            tree.AddValue("2", "0");
            tree.AddValue("20", "0");
            tree.AddValue("21", "0");
            tree.AddValue("22", "0");

            tree.AddValue("30", "0");
            tree.AddValue("31", "0");
            tree.AddValue("32", "0");

            tree.AddValue("3", "0");
            tree.AddValue("4", "0");
            tree.AddValue("5", "0");

            tree.AddValue("6", "0");
            tree.AddValue("7", "0");
            tree.AddValue("8", "6");

            tree.AddValue("23", "3");
            tree.AddValue("24", "0");
            tree.AddValue("25", "0");
            tree.AddValue("26", "0");
            tree.AddValue("27", "1");
            tree.AddValue("28", "0");
        }

        [TestMethod]
        public void FindValueTest()
        {
            tree.AddValue("1", "0");
            tree.AddValue("2", "0");
            tree.AddValue("20", "0");
            tree.AddValue("21", "0");
            tree.AddValue("22", "0");

            tree.AddValue("30", "0");
            tree.AddValue("31", "0");
            tree.AddValue("32", "0");

            tree.AddValue("3", "0");
            tree.AddValue("4", "0");
            tree.AddValue("5", "0");

            tree.AddValue("6", "0");
            tree.AddValue("7", "0");
            tree.AddValue("8", "6");

            tree.AddValue("23", "3");
            tree.AddValue("24", "0");
            tree.AddValue("25", "0");
            tree.AddValue("26", "0");
            tree.AddValue("27", "1");
            tree.AddValue("28", "0");

            Assert.AreEqual("0", tree.FindValue("7"));
            Assert.AreEqual("3", tree.FindValue("23"));
            Assert.AreEqual("0", tree.FindValue("1"));
            Assert.ThrowsException<ArgumentOutOfRangeException>(() => tree.FindValue("0"));
        }

        [TestMethod]
        public void IsExistsTest()
        {
            tree.AddValue("1", "2");
            tree.AddValue("2", "3");
            tree.AddValue("3", "4");
            tree.AddValue("4", "5");
            tree.AddValue("5", "6");
            tree.AddValue("6", "7");
            tree.AddValue("7", "8");

            Assert.AreEqual(true, tree.Exists("5"));
            Assert.AreEqual(false, tree.Exists("0"));
        }

        [TestMethod]
        public void PrintTreeTest()
        {
            tree.AddValue("1", "2");
            tree.AddValue("2", "3");
            tree.AddValue("3", "4");
            tree.AddValue("4", "5");
            tree.AddValue("5", "6");
            tree.AddValue("6", "7");
            tree.AddValue("7", "8");
            tree.PrintTree();
        }

        [TestMethod]
        public void DeleteValueTest()
        {
            tree.AddValue("1", "2");
            tree.AddValue("2", "3");
            tree.AddValue("3", "4");
            tree.AddValue("4", "5");
            tree.AddValue("5", "6");
            tree.AddValue("6", "7");
            tree.AddValue("7", "8");
            tree.DeleteValue("4");
            Assert.ThrowsException<ArgumentOutOfRangeException>(() => tree.DeleteValue("456"));
            Assert.ThrowsException<ArgumentOutOfRangeException>(() => tree.FindValue("4"));
        }
    }
}
