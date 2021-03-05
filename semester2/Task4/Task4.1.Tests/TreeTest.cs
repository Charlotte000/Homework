using System;
using NUnit.Framework;

namespace Task4._1.Tests
{
    public class TreeTest
    {
        [Test]
        public void CalculateTest()
        {
            var tree = new Tree("(+ 1 (* 9 2))");
            Assert.AreEqual(19, tree.Calculate());

            tree = new Tree("(- 0 (/ 1 3)");
            Assert.Less(Math.Abs(tree.Calculate() + .3333), .001);
        }

        [Test]
        public void DivizionByZeroTest()
        {
            var tree = new Tree("(/ 1 0)");
            Assert.Throws<DivideByZeroException>(() => tree.Calculate());

            tree = new Tree("(/ 1 (/ 1 (* 9 (* 9 (* 9 (* 9 (* 9 (* 9 9))))))))");
            Assert.Throws<DivideByZeroException>(() => tree.Calculate());
        }
    }
}