using System;
using System.Runtime.Serialization;

namespace Task4._2
{
    /// <summary>
    /// Exception throws if values doesn't exist in the container
    /// </summary>
    [Serializable]
    public class ValueDoesNotExist : Exception
    {
        public ValueDoesNotExist() { }

        public ValueDoesNotExist(string message) : base(message) { }

        public ValueDoesNotExist(string message, Exception inner)
            : base(message, inner) { }

        protected ValueDoesNotExist(SerializationInfo info, StreamingContext context)
            : base(info, context) { }
    }
}
