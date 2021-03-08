using NUnit.Framework;
using System;

namespace Task4._2.Testing
{
    public class ListTests
    {
        private List list;

        [SetUp]
        public void Setup()
        {
            list = new List();
        }

        [Test]
        public void AddValueTest()
        {
            for (int i = 0; i < 10; i++)
            {
                list.AddValue(10 - i);
            }
            for (int i = 0; i < 10; i++)
            {
                Assert.AreEqual(10 - i, list[i]);
            }
        }

        [Test]
        public void IndexOutOfBoundariesTest()
        {
            Assert.Throws<IndexOutOfRangeException>(() => list.GetValue(0));
            Assert.Throws<IndexOutOfRangeException>(() => list.GetValue(10));

            for (int i = 0; i < 10; i++)
            {
                list.AddValue(10 - i);
            }
            Assert.Throws<IndexOutOfRangeException>(() => list.GetValue(10));
            Assert.Throws<IndexOutOfRangeException>(() => list.GetValue(15));
        }

        [Test]
        public void DeleteValueTest()
        {
            for (int i = 0; i < 5; i++)
            {
                list.AddValue(5 - i);
            }
            list.DeleteValue(0);
            list.DeleteValue(2);
            Assert.AreEqual(4, list[0]);
            Assert.AreEqual(3, list[1]);
            Assert.AreEqual(1, list[2]);
        }

        [Test]
        public void DeleteNonExistentValueTest()
        {
            Assert.Throws<ValueDoesNotExist>(() => list.DeleteValue(0));
            Assert.Throws<ValueDoesNotExist>(() => list.DeleteValue(10));
            for (int i = 0; i < 10; i++)
            {
                list.AddValue(10 - i);
            }
            Assert.Throws<ValueDoesNotExist>(() => list.DeleteValue(10));
            Assert.Throws<ValueDoesNotExist>(() => list.DeleteValue(20));
        }

        [Test]
        public void IsExistsTest()
        {
            Assert.AreEqual(false, list.IsExists(12));
            list.AddValue(5);
            Assert.AreEqual(true, list.IsExists(5));
            list.AddValue(90);
            list.AddValue(123);
            Assert.AreEqual(true, list.IsExists(123));
        }
    }
}