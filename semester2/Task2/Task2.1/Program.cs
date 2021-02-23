using System;
using System.IO;

namespace Task2._1
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 2 || args.Length == 3)
            {
                if (args[0] == "-c")
                {
                    string path = args[1];
                    LzwAlgoritm.Compress(path);
                    var origin = new FileInfo(path);
                    int originLength = (int)origin.Length;
                    FileInfo compressed = new FileInfo(path + ".zipped");
                    int compressedLength = (int)compressed.Length;
                    Console.WriteLine($"Compression ratio: {Math.Round((float) originLength / compressedLength, 3)}");
                }
                else if (args[0] == "-u")
                {
                    string path = args[1];
                    LzwAlgoritm.Decompress(path);
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
