#include <iostream>
#include <cstring>
#include <map>
#include <cctype>
#include <algorithm>
#include <set>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

using namespace std;


void abortWithUsage(char* programName)
{
        printf("usage: %s -b BASIC_WORDS_FILE -t TEST_FILE\n\n", programName);
        abort();
}




int main(int argc, char* argv[])
{

	char* basicWordsFilename = 0;
	char* testWordsFilename = 0;
	int c;
	opterr = 0;
        string line;
	set<string> basicWordsSet;
	set<string>::const_iterator basicWordsSetIt;
	map<string, unsigned int> wordmap;
	map<string, unsigned int>::const_iterator itmap;
	map<string, unsigned int>::const_reverse_iterator ritmap;
	multimap<unsigned int, string> wordMultimap;
	multimap<unsigned int, string>::const_iterator itmultimap;
	multimap<unsigned int, string>::const_reverse_iterator ritmultimap;
	char* strForStrTok = 0;
	const char delimiters[] = " ,.:;?!\"~_@#$%^&*()[]{}/\\|`'<>=+-\t0123456789";
	char* tokenPointer;


        while ((c = getopt(argc, argv, "b:t:")) != -1) {
                switch (c)
                {
                        case 'b':
                                basicWordsFilename = optarg;
                                break;
                        case 't':
                                testWordsFilename = optarg;
                                break;
                        default:
                                abortWithUsage(argv[0]);
                }
        }

        if (basicWordsFilename == 0 || testWordsFilename == 0) {
                abortWithUsage(argv[0]);
        }
 



        ifstream basicWordsFile(basicWordsFilename);
        if (!basicWordsFile.is_open()) {
                cerr << "ERROR: unable to open basicWordsFile '" << basicWordsFilename << "'" << endl;
		return -1;
        }
	while (basicWordsFile.good()) {
		getline(basicWordsFile, line);
		strForStrTok = 0;
		strForStrTok = new (nothrow) char[line.length() + 1];
		if (strForStrTok) {
			strncpy(strForStrTok, line.c_str(), line.length());
			*(strForStrTok + line.length()) = '\0';

			tokenPointer = strtok(strForStrTok, delimiters);
			while (tokenPointer != 0)
			{
				string token(tokenPointer);
				//transform(token.begin(), token.end(), token.begin(), tolower);
				unsigned int i;
				for (i = 0; i < token.length(); i++) {
					token[i] = tolower(token[i]);
				}
				basicWordsSet.insert(token);
				tokenPointer = strtok(0, delimiters);
			}
		}
		delete[] strForStrTok;
	}
	basicWordsFile.close();

	ifstream fileToBeTested(testWordsFilename);
	if (!fileToBeTested.is_open()) {
                cerr << "ERROR: unable to open testWordsFilename '" << testWordsFilename << "'" << endl;
		return -2;
	}
	cerr << "INFO: loaded testWordsFilename" << endl;
	while (fileToBeTested.good()) {
                getline(fileToBeTested, line);
		strForStrTok = 0;
		strForStrTok = new (nothrow) char[line.length() + 1];
		if (strForStrTok) {
			strncpy(strForStrTok, line.c_str(), line.length());
			*(strForStrTok + line.length()) = '\0';

			tokenPointer = strtok(strForStrTok, delimiters);
			while (tokenPointer != 0)
			{
				string token(tokenPointer);
				//transform(token.begin(), token.end(), token.begin(), tolower);
				unsigned int i;
				for (i = 0; i < token.length(); i++) {
					token[i] = tolower(token[i]);
				}
				wordmap[string(token)]++;
				tokenPointer = strtok(0, delimiters);
			}
		}
		delete[] strForStrTok;
        };
	fileToBeTested.close();


	// -------- remove basicWords from wordmap BEGIN --------------------
	for (basicWordsSetIt = basicWordsSet.begin(); basicWordsSetIt != basicWordsSet.end(); basicWordsSetIt++)
	{
		wordmap.erase(*basicWordsSetIt);
	}
	// -------- remove basicWords from wordmap END ----------------------


	cout << "wordmap (" << wordmap.size() << " concepts)" << endl;
	cout << "------------------------------------------------------" << endl;
	for (itmap = wordmap.begin(); itmap != wordmap.end(); itmap++)
	{
		cout << itmap->first << ": " << itmap->second << endl;
		wordMultimap.insert(pair<unsigned int, string>(itmap->second, itmap->first));
	}
	cout << "------------------------------------------------------" << endl << endl;

	cout << "wordMultimap (" << wordMultimap.size() << " concepts)" << endl;
	cout << "------------------------------------------------------" << endl;
	for (ritmultimap = wordMultimap.rbegin(); ritmultimap != wordMultimap.rend(); ritmultimap++)
	{
		cout << ritmultimap->second << ": " << ritmultimap->first << endl;
	}
	cout << "------------------------------------------------------" << endl << endl;

	cout << "wordMultimap (" << wordMultimap.size() << " concepts, top 10)" << endl;
	cout << "------------------------------------------------------" << endl;
	unsigned int i = 0;
	for (ritmultimap = wordMultimap.rbegin(); ritmultimap != wordMultimap.rend(); ritmultimap++)
	{
		if (i >= 10) {
			break;
		}
		cout << ritmultimap->second << ": " << ritmultimap->first << endl;
		i++;
	}
	cout << "------------------------------------------------------" << endl << endl;

	return 0;
}

