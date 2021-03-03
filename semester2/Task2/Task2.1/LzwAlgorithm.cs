using System;
using System.IO;

namespace Task2._1
{
    /// <summary>
    /// Compress & decompress files using Lempel-Ziv-Welch algorithm
    /// </summary>
    static class LzwAlgorithm
    {
        /// <summary>
        /// Сompresses file, creating .zipped file
        /// </summary>
        /// <param name="path">Path to file</param>
        static public void Compress(string path)
        {
            string compressedPath = path + ".zipped";
            using FileStream fileRead = File.OpenRead(path);
            using FileStream fileWrite = File.OpenWrite(compressedPath);
            var trie = new Trie();
            for (int charIndex = 0; charIndex < fileRead.Length; charIndex++)
            {
                byte valueByte = (byte)fileRead.ReadByte();
                if (charIndex == fileRead.Length - 1)
                {
                    trie.SaveTrieElement(valueByte, fileWrite);
                }
                else
                {
                    if (trie.TryAdd(valueByte))
                    {
                        trie.SaveTrieElement(valueByte, fileWrite);
                        trie.ResetCursor();
                    }
                }
            }
            trie.SaveTrieCount(fileWrite);      
        }

        /// <summary>
        /// Uncompresses .zipped file
        /// </summary>
        /// <param name="path">Path to .zipped file</param>
        static public void Decompress(string path)
        {
            string uncompressedPath = path.Remove(path.Length - 7);
            using FileStream fileRead = File.OpenRead(path);
            using FileStream fileWrite = File.OpenWrite(uncompressedPath);
            fileRead.Seek(-4, SeekOrigin.End);
            var sizeByte = new byte[4];
            sizeByte[0] = (byte)fileRead.ReadByte();
            sizeByte[1] = (byte)fileRead.ReadByte();
            sizeByte[2] = (byte)fileRead.ReadByte();
            sizeByte[3] = (byte)fileRead.ReadByte();
            int size = BitConverter.ToInt32(sizeByte);
            fileRead.Seek(0, SeekOrigin.Begin);
            var dictionary = new byte[size][];
            var valueBytes = new byte[4];

            for (int i = 0; i < dictionary.GetLength(0); i++)
            {
                int bytesLength = (int)Math.Ceiling(Math.Log2(i + 2) / 8);
                for (int j = 0; j < 4; j++)
                {
                    valueBytes[j] = j < bytesLength ? (byte)fileRead.ReadByte() : (byte)0;
                }
                int value = BitConverter.ToInt32(valueBytes);
                byte character = (byte)fileRead.ReadByte();
                if (value == 0)
                {
                    dictionary[i] = new byte[1];
                    dictionary[i][0] = character;
                    fileWrite.WriteByte(character);
                }
                else
                {
                    dictionary[i] = new byte[dictionary[value - 1].Length + 1];
                    for (int j = 0; j < dictionary[i].Length; j++)
                    {
                        dictionary[i][j] = j != dictionary[i].Length - 1 ? dictionary[value - 1][j] : character;
                        fileWrite.WriteByte(dictionary[i][j]);
                    }
                }
            }
        }
    }
}
