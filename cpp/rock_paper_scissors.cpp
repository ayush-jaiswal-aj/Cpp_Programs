#include<iostream>
#include<unordered_map>
#include<cstdlib>
#include<ctime>
using namespace std;

int main(){
    unordered_map<string, int> choices = {{"rock", 0}, {"paper", 1}, {"scissors", 2}};
    string names[3] = {"rock", "paper", "scissors"}, player;
    int pScore = 0, cScore = 0;
    char again;
    srand(time(0));

    do{
        cout<<"Enter rock, paper or scissors: ";
        cin>>player;
        for(auto &c : player) c = tolower(c);
        if(choices.find(player) == choices.end()) continue;

        int p = choices[player], c = rand() % 3;
        cout<<"Computer chose: "<<names[c]<<endl;

        if(p==c) cout<<"Draw!\n";
        else if((p+1)%3==c) cout<<"Computer wins!\n", cScore++;
        else cout<<"You win!\n", pScore++;

        cout<<"Score - You: "<<pScore<<" | Computer: "<<cScore<<endl;
        cout<<"Play again? (y/n): ";
        cin>>again;
    } while(tolower(again) == 'y');

    cout<<"Final Score - You: "<<pScore<<" | Computer: "<<cScore<<"\nThanks for playing!\n";
}
