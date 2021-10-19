#include <iostream>
#include <vector>
#include <string.h>
#include "lib/crow_all.h"
#include <iostream>

using namespace std;

const string abc = "abcdefghijklmnopqrstuvwxyz";
vector<string> dict = {};

vector<string> AddWord(string word)
{
    vector<string> wordlist = {};
    for (int i = 0; i < abc.size(); i++)
    {
        for (int j = 0; j < word.size(); j++)
        {
            string w = word;
            wordlist.push_back(w.insert(j, abc.substr(i, 1)));
        }
    }

    for (int i = 0; i < abc.size(); i++)
    {
        string w = word + abc[i];
        wordlist.push_back(w);
    }
    return wordlist;
}

vector<string> RemoveWord(string word)
{
    vector<string> wordlist = {};
    for (int j = 0; j < word.size(); j++)
    {
        string w = word;
        wordlist.push_back(w.erase(j, 1));
    }
    return wordlist;
}

vector<string> ReplaceWord(string word)
{
    vector<string> wordlist;
    for (int i = 0; i < abc.size(); i++)
    {
        for (int j = 0; j < word.size(); j++)
        {
            string w = word;
            w[j] = abc[i];
            wordlist.push_back(w);
        }
    }
    return wordlist;
}

vector<string> SwapWord(string word)
{
    vector<string> wordlist = {};
    for (int i = 1; i < word.size(); i++)
    {
        string w = word;
        swap(w[i - 1], w[i]);
        wordlist.push_back(w);
    }
    return wordlist;
}

void printArry(vector<string> vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << "\n"; 
    }
}

vector<string> test(vector<string> a)
{
    vector<string> words;

    for (string x : a)
    {
        vector<string> addWords = AddWord(x);
        vector<string> removeWord = RemoveWord(x);
        vector<string> replaceWord = ReplaceWord(x);
        vector<string> swapWord = SwapWord(x);

        words.insert(words.end(), addWords.begin(), addWords.end());
        words.insert(words.end(), removeWord.begin(), removeWord.end());
        words.insert(words.end(), replaceWord.begin(), replaceWord.end());
        words.insert(words.end(), swapWord.begin(), swapWord.end());
    }

    return words;
}

vector<string> getCandicates(string word)
{
    std::vector<string> words;

    std::vector<string> addWords = AddWord(word);
    std::vector<string> removeWord = RemoveWord(word);
    std::vector<string> replaceWord = ReplaceWord(word);
    std::vector<string> swapWord = SwapWord(word);

    words.insert(words.end(), addWords.begin(), addWords.end());
    words.insert(words.end(), removeWord.begin(), removeWord.end());
    words.insert(words.end(), replaceWord.begin(), replaceWord.end());
    words.insert(words.end(), swapWord.begin(), swapWord.end());

    for (size_t i = 0; i < 1; i++)
        words = test(words);

    return words;
}

vector<string> GetCurretWord(string w)
{
    vector<string> words = {};

    auto candicates = getCandicates(w);
    for (string corretWord : dict)
    {
        for (string cadicateWord : candicates)
        {
            if(cadicateWord == corretWord)
            {
                words.push_back(corretWord);
                break;
            }
        }
    }

    return words;
}


int main()
{

    string myText;
    ifstream MyReadFile("words.txt");

    while (getline (MyReadFile, myText)) {
        // Output the text from the file
        dict.push_back(myText);
    }
    MyReadFile.close();

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](const crow::request& req, crow::response& res){
        auto w = GetCurretWord(req.url_params.get("word"));
        if(w.size() == 0)
        {
            res.code = 404;
            res.end();
            return;
        }

        string body = "[\n";
        for(string x : w)
        {
            body +="\t\"" + x + "\",\n";
        }
        body += "]";

        res.add_header("Content-Type", "application/json");
        res.body = body;
        res.end();
    });

    app.port(18080).multithreaded().run();
}