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
                if (args[0] == "-c")
                {
                    string path = args[1];
                    if (File.Exists(path + ".zipped"))
                    {
                        Console.WriteLine("File is already exists");
                        return;
                    }
                    LzwAlgorithm.Compress(path);
                    var origin = new FileInfo(path);
                    int originLength = (int)origin.Length;
                    var compressed = new FileInfo(path + ".zipped");
                    int compressedLength = (int)compressed.Length;
                    Console.WriteLine($"Compression ratio: {Math.Round((float) originLength / compressedLength, 3)}");
                }
                else if (args[0] == "-u")
                {
                    string path = args[1];
                    if (File.Exists(path.Remove(path.Length - 7)))
                    {
                        Console.WriteLine("File is already exists");
                        return;
                    }
                    LzwAlgorithm.Decompress(path);
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
