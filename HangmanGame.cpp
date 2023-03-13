#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <random>
#include <time.h>

using namespace std;
string GetWord();
string LoadRandomWord();
void Hangman(string word);
bool CheckContinue();

void main()
{
    srand(time(nullptr));

    string word = "";
    bool cont = true;

    while (cont)
    {
        word = GetWord();
        if (word.length() > 1)
        {
            Hangman(word);
            cont = CheckContinue();
        }
        else
        {
            cout << "Could not load valid word. Check dictionary and try again." << endl;
            cont = false;
            return;
        }
    }

    cout << endl << "Press Enter to exit" << endl;

    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();
}

void Hangman(string w)
{
    string letter;
    string output = "";
    string guesses = "";
    int tries = 0;

    if (w.length() == 0)
    {
        cout << "Invalid Word." << endl;
        return;
    }

    // fill the output word with underscores.
    // This will be used to show which letters we guessed correctly.
    // Using 'resize' makes this easy
    output.resize(w.length(), '_');

    while (output != w)
    {
        // ask the player for a letter
        cout << "Enter a letter: " << endl;
        cin >> letter;
        tries++;
        guesses = guesses + " " + letter;

        // ensure they entered only 1 letter by trimming the input
        if (letter.length() > 1)
            letter.resize(1);

        // search for the letter in the word
        // If the letter is found, replace the underscore at the corresponding position
        // in the output string with the correctly guessed letter
        int startPos = 0;
        size_t searchPos = w.find(letter, startPos);
        // the while loop ensures we keep searching the string until no more letters
        // are found
        while (searchPos != string::npos)
        {
            // replace the underscore in the output string with the letter that was
            // guessed (The input string used for the letter variable contains only 1
            // letter, so we can access it using the subscript operator at index 0)
            output[searchPos] = letter[0];
            startPos = searchPos + 1;
            // If the search position returned was the last letter in the string, then
            // we must exit now (there is no more string left to search)
            if (startPos >= w.length())
                break;
            // continue searching. If there are no more matches then searchPos will
            // equal string::npos and the loop will exit
            searchPos = w.find(letter, startPos);
        }

        // display our guessed output
        cout << output << endl;
        cout << "Guesses:" << guesses << "\n" << endl;

    }

    cout << "You solved the word "<< w << " in " << tries <<" tries!" << endl;
}

string GetWord()
{
    string tempWord = "";
    int tries = 0;

    while (tempWord.length() == 0 && tries < 3)
    {
        tempWord = LoadRandomWord();
        tries++;
    }

    return tempWord;
}

string LoadRandomWord()
{
    ifstream in;
    in.open("dictionary.txt", ifstream::in);

    if (in.is_open() == false)
    {
        cout << "The dictionary file could not be opened";
        return "";
    }

    // new lines will be skipped unless we stop it from happening:   
    in.unsetf(ios_base::skipws);

    // count the newlines with an algorithm specialized for counting.
    // this will read (and throw away) all the data on a line (up to the
    // new line separator we've specified)
    // the result is we get back the number of lines in our text file
    unsigned line_count = std::count(
        istream_iterator<char>(in),
        istream_iterator<char>(),
        '\n');

    // create a random number within the range 0-line_count
    int selection = rand() % line_count;

    // reset the error flags (the eof flag was set during the count()
    // function call)
    in.clear();
    // reset the file pointer to the start of the file
    // (you *must* call clear before resetting the file pointer, or else
    // it won't reset)
    in.seekg(0, ios::beg);

    // declare a string to hold the word we read from the file
    string text;

    // find the word on the selected random line
    for (int i = 0; i < selection; i++) {
        // read (and throw away) each line
        std::getline(in, text);
    }

    // close the file
    in.close();

    // return the word in the text buffer as a std::string
    return text;
}

bool CheckContinue()
{
    //initialise variables to work with
    bool temp = false;
    string input = "";

    //while the input is an empty string
    //prompt the use for input and try read from console
    while (input.length() == 0)
    {
        cout << "Play Again? (y/n): " << endl;
        cin >> input;
    }

    //if the input is y or Y set temp to true
    //else set as false
    if (input == "y" || input == "Y")
    {
        temp = true;
    }
    else
    {
        temp = false;
    }

    //return our bool
    return temp;
}