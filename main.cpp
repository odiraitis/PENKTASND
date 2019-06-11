#include "header.h"

// pair and map type
using WordInfo = std::pair<int, std::set<int> >;
using WordMap = std::map<std::string, WordInfo>;

int main()
{
     //read the input, keeping track of each word and how often we see it
     std::ifstream in("tekstas.txt"); // input file

    // my map
    WordMap wm;
    std::string eilute;

    std::map <std::string, int> linkas;
 
    // the line count
    int line_number = 1;
    
    while(std::getline(in, eilute))
    {
        std::transform(eilute.begin(), eilute.end(), eilute.begin(), ::tolower); // lowering letters so for example "Mom"= "mom"
        eilute.erase(std::remove_if(eilute.begin(),eilute.end(),::isnumber),eilute.end());
        std::stringstream read(eilute);
        std::string word;
        while (read >> word)
        {
            if(std::regex_match(word, std::regex("[(http(s)?):\\/\\/(www\\.)?a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)") )){
                linkas.insert(std::pair<std::string,int>(word,line_number));
            }
            
            
            
             word.erase (std::remove_if(word.begin(), word.end(), ::ispunct), word.end()); // istrinu skyrybos zenklus
            // we call map::insert, not `[ ]` to insert into a map
            
            auto pr = wm.insert({word, {0,std::set<int>()}});
            
            // the return value of map::insert gives us a pair, where the first is
            // an iterator to the item in the map
            auto& mapIter = pr.first;
            // increment the word count
            ++(mapIter->second.first);
            
            // insert the line number into the set
            mapIter->second.second.insert(line_number);
            
        }
        // increment the line counter
        ++line_number;
    
     }
     std::ofstream out("isvestis.txt");
    out<<"Words that appear more than once in the text: "<<std::endl;
    out<<std::endl;

    
    int did=0;
      for (auto& it : wm )
      {
          if(did<it.second.first)
          {
              did=it.second.first;
             
          }
      }

     for (auto& it : wm )
        {
            
            
            for (int i=0; i<=did ;i++)
            {
                if((it.second.first)==i && it.second.first>1)
                {
                    
                    out << "The word  \"" << it.first << "\" appears " << it.second.first << " times on the following lines:\n";
                    
                    for ( auto& it2 : it.second.second)
                        
                        out << it2 << " ";
                    
                    out<<std::endl;
                    
                }
            }
           
        }
   out<<std::endl;

    out<<"URL ADRESSES ARE : "<<std::endl;

    for(auto it = linkas.begin(); it != linkas.end(); ++it){
        out<<"URL: " <<it->first <<" in line : "<<it->second<<std::endl;
    }
        return 0;

}
