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
                    if (args.Length == 3 && args[2] == "-b")
                    {
                        File.WriteAllText(path, BWTalgoritm.BWT(File.ReadAllText(path)));
                    }
                    LZWalgoritm.Compress(path);
                    FileInfo origin = new FileInfo(path);
                    int originLength = (int)origin.Length;
                    FileInfo compressed = new FileInfo(Path.ChangeExtension(path, "zipped"));
                    int compressedLength = (int)compressed.Length;
                    Console.WriteLine($"Compression ratio: {Math.Round((float) originLength / compressedLength, 3)}");
                }
                else if (args[0] == "-u")
                {
                    string path = args[1];
                    LZWalgoritm.Decompress(path);
                    if (args.Length == 3 && args[2] == "-b")
                    {
                        string uncompressedPath = Path.ChangeExtension(path, "txt");
                        File.WriteAllText(uncompressedPath, BWTalgoritm.BWT(File.ReadAllText(uncompressedPath)));
                    }

                }
            }
            else
            {
                Console.WriteLine("Welcome to Lempel–Ziv–Welch data compression program.");
                Console.WriteLine("-c filepath  :To compress file");
                Console.WriteLine("-u filepath  :To uncompress file");
                Console.WriteLine("-b           :Additional parameter to use BTW algoritm");

            }
        }
    }
}
