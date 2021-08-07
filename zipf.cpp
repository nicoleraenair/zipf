#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool sortByVal(const pair<string, int> &a, const pair<string, int> &b);

int main(int argc, char *argv[]) {

  map<string,int> words_by_frequency;
  map<string,int>::iterator it;
  string word;

  ifstream textFile(argv[1]);

  while (textFile >> word)
  {
    for(int i = 0; i < word.length(); i++){
      if(ispunct(word[i]) || !isalpha(word[i])){
        word.erase(word.begin() + i);
      }
      word[i] = tolower(word[i]);
    }
    it = words_by_frequency.find(word);
    if (it == words_by_frequency.end())
      words_by_frequency[word] = 1;
    else
      words_by_frequency[word]++;
  }

  textFile.close();

  vector< pair<string, int> > vec;
  for (it=words_by_frequency.begin(); it!=words_by_frequency.end(); it++) {
    if(it->second > 9 && it->first.length() > 0){
      vec.push_back(make_pair(it->first, it->second));
    }
  }
  sort(vec.begin(), vec.end(), sortByVal);

  for (int i = 0; i < atoi(argv[3]); i++)
	{
		cout << i + 1 << ". " << vec[i].first << ": " << vec[i].second << endl;
	}

  ofstream MyFile(argv[2]);

  for (it=words_by_frequency.begin(); it!=words_by_frequency.end(); it++) {
    if(it->second > 9 && it->first.length() > 0)
      MyFile << it->first.length() << ", " << it->second << endl;
  }

  MyFile.close();
  return 0;
}

bool sortByVal(const pair<string, int> &a, const pair<string, int> &b)
{
    return (a.second > b.second);
}
