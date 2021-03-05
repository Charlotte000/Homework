using System;
using System.Runtime.Serialization;

namespace Task4._2
{
    [Serializable]
    public class ValueAlreadyExistsException: Exception
    {
        public ValueAlreadyExistsException() { }

        public ValueAlreadyExistsException(string message) : base(message) { }

        public ValueAlreadyExistsException(string message, Exception inner)
            : base(message, inner) { }

        protected ValueAlreadyExistsException(SerializationInfo info, StreamingContext context)
            : base(info, context) { }
    }
}
