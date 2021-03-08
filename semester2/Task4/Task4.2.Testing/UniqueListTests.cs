using NUnit.Framework;

namespace Task4._2.Testing
{
    public class UniqueListTests
    {
        private UniqueList list;

        [SetUp]
        public void Setup()
        {
            list = new UniqueList();
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
        public void AddExistingValueTest()
        {
            for (int i = 0; i < 10; i++)
            {
                list.AddValue(i);
            }
            for (int i = 0; i < 10; i++)
            {
                Assert.Throws<ValueAlreadyExistsException>(() => list.AddValue(i));
            }

            Assert.Throws<ValueAlreadyExistsException>(() => list[0] = 0);
            list[0] = 123;
        }
    }
}