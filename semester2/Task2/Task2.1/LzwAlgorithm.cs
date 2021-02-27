using System;
using System.IO;

namespace Task2._1
{
    class LzwAlgorithm
    {
        static public void Compress(string path)
        {
            string compressedPath = path + ".zipped";

            if (File.Exists(compressedPath))
            {
                File.Delete(compressedPath);
            }

            using FileStream fileRead = File.OpenRead(path);
            using FileStream fileWrite = File.OpenWrite(compressedPath);
            Trie trie = new Trie();
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

        static public void Decompress(string path)
        {
            string uncompressedPath = path.Remove(path.Length - 7);
            if (File.Exists(uncompressedPath))
            {
                File.Delete(uncompressedPath);
            }
            using FileStream fileRead = File.OpenRead(path);
            using FileStream fileWrite = File.OpenWrite(uncompressedPath);
            fileRead.Seek(-4, SeekOrigin.End);
            byte[] sizeByte = new byte[4];
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
