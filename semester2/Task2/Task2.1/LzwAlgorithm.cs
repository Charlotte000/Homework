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
                    int index = 1;
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
                    fileWrite.Write(BitConverter.GetBytes(index));
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
                    fileRead.Seek(-4, SeekOrigin.End);
                    byte[] sizeByte = new byte[4];
                    sizeByte[0] = (byte)fileRead.ReadByte();
                    sizeByte[1] = (byte)fileRead.ReadByte();
                    sizeByte[2] = (byte)fileRead.ReadByte();
                    sizeByte[3] = (byte)fileRead.ReadByte();
                    int size = BitConverter.ToInt32(sizeByte);
                    fileRead.Seek(0, SeekOrigin.Begin);
                    dictionary = new byte[size][];
                    byte[] valueBytes = new byte[4];
                    for (int i = 0; i < dictionary.GetLength(0); i++)
                    {
                        int bytesLength = fileRead.ReadByte();
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

        static private void WriteTrie(Trie cursor, byte valueByte, FileStream file)
        {
            int writeValue = cursor.HasParent() ? cursor.value : 0;
            // byte[] bytes = BitConverter.GetBytes(writeValue);
            byte[] bytes = GetBytes(writeValue);
            file.WriteByte(BitConverter.GetBytes(bytes.Length)[0]);
            file.Write(bytes);
            file.WriteByte(valueByte);
        }

        static private byte[] GetBytes(int value)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            int length = 0;
            for (int i = 3; i >= 0; i--)
            {
                if (bytes[i] != 0)
                {
                    length = i + 1;
                    break;
                }
            }
            Array.Resize(ref bytes, length);
            return bytes;
        }
    }
}
