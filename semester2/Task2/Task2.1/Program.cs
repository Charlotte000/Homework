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
                    LZWalgoritm.Compress(path);
                    FileInfo origin = new FileInfo(path);
                    int originLength = (int)origin.Length;
                    FileInfo compressed = new FileInfo(Path.ChangeExtension(path, "zipped"));
                    int compressedLength = (int)compressed.Length;
                    Console.WriteLine($"Compression ratio: {Math.Round((float) originLength / compressedLength, 3)}");
                }
                else if (args[0] == "-u" || args[1] == "-u")
                {
                    string path = args[0] == "-u" ? args[1] : args[0];
                    LZWalgoritm.Decompress(path);
                }
            }
            else
            {
                Console.WriteLine("Welcome to Lempel–Ziv–Welch data compression program.");
                Console.WriteLine("-c filepath  :To compress file");
                Console.WriteLine("-u filepath  :To uncompress file");
            }
        }
    }
}
