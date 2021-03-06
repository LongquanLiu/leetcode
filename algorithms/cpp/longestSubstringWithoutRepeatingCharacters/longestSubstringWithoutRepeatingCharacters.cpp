// Source : https://oj.leetcode.com/problems/longest-substring-without-repeating-characters/
// Author : Longquan Liu
// Date   : 2018-04-09

/********************************************************************************** 
* 
* Given a string, find the length of the longest substring without repeating characters. 
* For example, the longest substring without repeating letters for "abcabcbb" is "abc", 
* which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*               
**********************************************************************************/

#include <string.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;
/*
 * Keywords: sliding windows, hash map
 * Idea:
 * 
 * Using a map store each char's index.
 * 
 * So, we can be easy to know the when duplication and the previous duplicated char's index.
 * 
 * Then we can take out the previous duplicated char, and keep tracking the maxiumn length. 
 * 
 */
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        std::map<char, int> mymap;
        int maxLen = 0;
        int lastRepeatPos = -1;
        for(int i = 0; i < s.size(); i++){
            if(mymap.find(s[i]) != mymap.end() && lastRepeatPos < mymap[s[i]]){       
                // if s[i] already in the substring, update the lastRepeatPos
                lastRepeatPos = mymap[s[i]];
            }
            if(i - lastRepeatPos > maxLen){                                           
                // if current substring length larger than maxLen, update
                maxLen = i - lastRepeatPos;
            }
            mymap[s[i]] = i;                                                          
            // add current element to HashMap
        }
        return maxLen;
    }
        
};
//don't use <map>
int lengthOfLongestSubstring(string s) {
    const int MAX_CHARS = 256;
    int m[MAX_CHARS];
    memset(m, -1, sizeof(m));

    int maxLen = 0;
    int lastRepeatPos = -1;
    for(int i=0; i<s.size(); i++){
        if (m[s[i]]!=-1 && lastRepeatPos < m[s[i]]) {
            lastRepeatPos = m[s[i]];
        }
        if ( i - lastRepeatPos > maxLen ){
            maxLen = i - lastRepeatPos;
        }
        m[s[i]] = i;
    }
    return maxLen;
}

int main(int argc, char** argv)
{
    string s = "abcabcbb";
    cout << s << " : " << lengthOfLongestSubstring(s) << endl;

    s = "bbbbb";
    cout << s << " : " << lengthOfLongestSubstring(s) << endl;

    s = "bbabcdb";
    cout << s << " : " << lengthOfLongestSubstring(s) << endl;

    if (argc>1){
        s = argv[1];
        cout << s << " : " << lengthOfLongestSubstring(s) << endl;
    }

    return 0;
}
