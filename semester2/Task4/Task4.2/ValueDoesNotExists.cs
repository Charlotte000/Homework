using System;
using System.Runtime.Serialization;

namespace Task4._2
{
    [Serializable]
    public class ValueDoesNotExists : Exception
    {
        public ValueDoesNotExists() { }

        public ValueDoesNotExists(string message) : base(message) { }

        public ValueDoesNotExists(string message, Exception inner)
            : base(message, inner) { }

        protected ValueDoesNotExists(SerializationInfo info, StreamingContext context)
            : base(info, context) { }
    }
}
