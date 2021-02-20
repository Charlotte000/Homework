using System;
using System.IO;

namespace Task2._1
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 2)
            {
                if (args[0] == "-c" || args[1] == "-c")
                {
                    string path = args[0] == "-c" ? args[1] : args[0];
                    string uncompressed = File.ReadAllText(path);
                    string compressed = LZWalgoritm.Compress(uncompressed);

                    string compressedPath = Path.ChangeExtension(path, "zipped");
                    File.WriteAllText(compressedPath, compressed);
                }
                else if (args[0] == "-u" || args[1] == "-u")
                {
                    string path = args[0] == "-u" ? args[1] : args[0];
                    string compressed = File.ReadAllText(path);
                    string uncompressed = LZWalgoritm.Decompress(compressed);

                    string uncompressedPath = Path.ChangeExtension(path, "txt");
                    File.WriteAllText(uncompressedPath, uncompressed);

                }
            }


        }
    }
}
