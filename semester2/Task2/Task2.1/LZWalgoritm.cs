namespace Task2._1
{
    class LZWalgoritm
    {

        static public string Compress(string input)
        {
            Trie head = new Trie();
            Trie cursor = head;
            int index = 0;
            string result = "";
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
                    cursor.AddChild(input[charIndex]).value = index;
                    if (cursor.parent != null && charIndex != input.Length - 1)
                    {
                        result += $"{cursor.value}\t{input[charIndex]}\t\t";
                    }
                    else
                    {
                        result += $"-1\t{input[charIndex]}\t\t";
                    }
                    index++;
                    cursor = head;
                }
            }
            return result.Remove(result.Length - 2, 2);
        }

        static public string Decompress(string input)
        {
            string[] dictionary = input.Split("\t\t");

            string result = "";
            for (int i = 0; i < dictionary.Length; i++)
            {
                result += ParseDictionary(dictionary, i);
            }
            return result;
        }

        static private string ParseDictionary(string[] dictionary, int index)
        {
            var parameters = dictionary[index].Split('\t');
            int parentIndex = int.Parse(parameters[0]);
            return parentIndex == -1 ? parameters[1] : $"{ParseDictionary(dictionary, parentIndex)}{parameters[1]}";
        }
    }
}
