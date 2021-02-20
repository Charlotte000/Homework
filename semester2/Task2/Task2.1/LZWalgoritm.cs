using System.IO;

namespace Task2._1
{
    class LZWalgoritm
    {
        static public void Compress(string path)
        {
            string input = File.ReadAllText(path);
            string compressedPath = Path.ChangeExtension(path, "zipped");
            FileStream file = File.OpenWrite(compressedPath);
            Trie head = new Trie();
            Trie cursor = head;
            int index = 0;
            for (int charIndex = 0; charIndex < input.Length; charIndex++)
            {
                bool isExists = false;
                for (int childIndex = 0; childIndex < cursor.childrenLen; childIndex++)
                {
                    if (cursor.characters[childIndex] == input[charIndex])
                    {
                        cursor = cursor.children[childIndex];
                        isExists = true;
                        break;
                    }
                }
                if (!isExists || charIndex == input.Length - 1)
                {
                    cursor.AddChild(input[charIndex]).value = index++;
                    if (cursor.parent != null && charIndex != input.Length - 1)
                    {
                        file.WriteByte((byte)cursor.value);
                    }
                    else
                    {
                        file.WriteByte(255);
                    }
                    file.WriteByte((byte)input[charIndex]);
                    cursor = head;
                }
            }
            file.Close();
        }

        static public void Decompress(string path)
        {
            FileStream fileRead = File.OpenRead(path);
            string uncompressedPath = Path.ChangeExtension(path, "txt");

            int[,] dictionary = new int[fileRead.Length / 2, 2];
            for (int i = 0; i < fileRead.Length / 2; i++)
            {
                int value = fileRead.ReadByte();
                int character = fileRead.ReadByte();
                dictionary[i, 0] = value;
                dictionary[i, 1] = character;
            }
            fileRead.Close();
            
            for (int i = 0; i < dictionary.GetLength(0); i++)
            {
                File.AppendAllText(uncompressedPath, ParseDictionary(dictionary, i));
            }
        }

        static private string ParseDictionary(int[,] dictionary, int index)
        {
            string result = ((char)dictionary[index, 1]).ToString();
            int parentIndex = dictionary[index, 0];
            while (parentIndex != 255)
            {
                result = (char)dictionary[parentIndex, 1] + result;
                parentIndex = dictionary[parentIndex, 0];
            }
            return result;
        }
    }
}
