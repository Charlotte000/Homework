using System;
using System.IO;
using System.Text;

namespace Task2._1
{
    class LzwAlgoritm
    {
        static public void Compress(string path)
        {
            string input = File.ReadAllText(path);
            string compressedPath = path + ".zipped";

            if (File.Exists(compressedPath))
            {
                File.Delete(compressedPath);
            }

            using FileStream file = File.OpenWrite(compressedPath);
            {
                var head = new Trie();
                Trie cursor = head;
                int index = 0;
                for (int charIndex = 0; charIndex < input.Length; charIndex++)
                {
                    if (charIndex == input.Length - 1)
                    {
                        WriteTrie(cursor, input[charIndex], file);
                    }
                    else
                    {
                        if (cursor.HasChild(input[charIndex]))
                        {
                            cursor = cursor.GetChild(input[charIndex]);
                        }
                        else
                        {
                            cursor.AddChild(input[charIndex]).value = index;
                            index++;
                            WriteTrie(cursor, input[charIndex], file);
                            cursor = head;
                        }
                    }
                }
            }
        }

        static public void Decompress(string path)
        {
            string[] dictionary;

            string uncompressedPath = path.Remove(path.Length - 7);
            if (File.Exists(uncompressedPath))
            {
                File.Delete(uncompressedPath);
            }
            using FileStream fileRead = File.OpenRead(path);
            {
                using FileStream fileWrite = File.OpenWrite(uncompressedPath);
                {
                    dictionary = new string[fileRead.Length / 5];
                    byte[] valueBytes = new byte[4];
                    for (int i = 0; i < fileRead.Length / 5; i++)
                    {
                        valueBytes[0] = (byte)fileRead.ReadByte();
                        valueBytes[1] = (byte)fileRead.ReadByte();
                        valueBytes[2] = (byte)fileRead.ReadByte();
                        valueBytes[3] = (byte)fileRead.ReadByte();
                        int value = BitConverter.ToInt32(valueBytes);
                        int character = fileRead.ReadByte();

                        if (value == -1)
                        {
                            dictionary[i] = ((char)character).ToString();
                        }
                        else
                        {
                            dictionary[i] = dictionary[value] + ((char)character).ToString();
                        }
                        fileWrite.Write(Encoding.Unicode.GetBytes(dictionary[i]));
                    }
                }
            }
        }

        static private void WriteTrie(Trie cursor, char character, FileStream file)
        {
            int writeValue = cursor.HasParent() ? cursor.value : -1;
            byte[] bytes = BitConverter.GetBytes(writeValue);
            foreach (var b in bytes)
            {
                file.WriteByte(b);
            }
            file.WriteByte((byte)character);
        }
    }
}
