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
            
            using (FileStream fileRead = File.OpenRead(path))
            {
                using FileStream fileWrite = File.OpenWrite(compressedPath);
                {
                    var head = new Trie();
                    Trie cursor = head;
                    int index = 0;
                    for (int charIndex = 0; charIndex < fileRead.Length; charIndex++)
                    {
                        byte valueByte = (byte)fileRead.ReadByte();
                        if (charIndex == fileRead.Length - 1)
                        {
                            WriteTrie(cursor, valueByte, fileWrite);
                        }
                        else
                        {
                            if (cursor.HasChild(valueByte))
                            {
                                cursor = cursor.GetChild(valueByte);
                            }
                            else
                            {
                                cursor.AddChild(valueByte).value = index;
                                index++;
                                WriteTrie(cursor, valueByte, fileWrite);
                                cursor = head;
                            }
                        }
                    }
                }
            }
        }

        static public void Decompress(string path)
        {
            byte[][] dictionary;

            string uncompressedPath = path.Remove(path.Length - 7);
            if (File.Exists(uncompressedPath))
            {
                File.Delete(uncompressedPath);
            }
            using (FileStream fileRead = File.OpenRead(path))
            {
                using (FileStream fileWrite = File.OpenWrite(uncompressedPath))
                {
                    dictionary = new byte[fileRead.Length / 5][];
                    byte[] valueBytes = new byte[4];
                    for (int i = 0; i < fileRead.Length / 5; i++)
                    {
                        valueBytes[0] = (byte)fileRead.ReadByte();
                        valueBytes[1] = (byte)fileRead.ReadByte();
                        valueBytes[2] = (byte)fileRead.ReadByte();
                        valueBytes[3] = (byte)fileRead.ReadByte();
                        int value = BitConverter.ToInt32(valueBytes);
                        byte character = (byte)fileRead.ReadByte();

                        if (value == -1)
                        {
                            dictionary[i] = new byte[1];
                            dictionary[i][0] = character;
                            fileWrite.WriteByte(character);
                        }
                        else
                        {
                            dictionary[i] = new byte[dictionary[value].Length + 1];
                            for (int j = 0; j < dictionary[i].Length; j++)
                            {
                                dictionary[i][j] = j != dictionary[i].Length - 1 ? dictionary[value][j] : character;
                                fileWrite.WriteByte(dictionary[i][j]);
                            }
                        }
                    }
                }
            }
        }

        static private void WriteTrie(Trie cursor, byte valueByte, FileStream file)
        {
            int writeValue = cursor.HasParent() ? cursor.value : -1;
            byte[] bytes = BitConverter.GetBytes(writeValue);
            foreach (var b in bytes)
            {
                file.WriteByte(b);
            }
            file.WriteByte(valueByte);
        }
    }
}
