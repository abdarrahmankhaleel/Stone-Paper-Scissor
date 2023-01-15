// Stone-Paper-Scissor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;
enum enGameChoices
{
    Stone,Paper,Scissor
};
enum enWinner
{
    Player, Computer, Draw
};

struct stRoundInfo
{
    short roundNumber =0;
    enGameChoices enPlayerChoice;
    enGameChoices enComputerChoice;
    enWinner enWinner;
    string winnerName;
};

struct stGameResults
{
    short gameRoundsNumber = 0;
    short playerWinTimes = 0;
    short computerWinTimes = 0;
    short drawTimes = 0;
    enWinner enGameWinner;
    string winnerName;
};

int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

string WinnerName(enWinner enWinner) {
    string arrWinnerName[3] = { "Player", "Computer", "No Winner" };
    return arrWinnerName[enWinner];
}

string ChoiceName(enGameChoices enGameChoices) {
    string arrGameChoices[3] = { "Stone","Paper","Scissor" };
    return arrGameChoices[enGameChoices];
}
string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}
short ReadHowManyRound() {
    short roundsNumber = 1;
    do
    {
        cout << "\nHow Many round do you want 1 to 10 ? ";
        cin >> roundsNumber;
        
    } while (roundsNumber<1||roundsNumber>10);
    return roundsNumber;
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
void ShowGameOverScreen()
{
    cout << Tabs(2) <<
        "__________________________________________________________\n\n";
    cout << Tabs(2) << " +++ G a m e O v e r ++ + \n";
        cout << Tabs(2) <<
        "__________________________________________________________\n\n";
}
void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F"); //turn screen to Green
        break;
    case enWinner::Computer:
        system("color 4F"); //turn screen to Red
        cout << "\a";
        break;
    default:
        system("color 6F"); //turn screen to Yellow
        break;
    }
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________Round [" << RoundInfo.roundNumber << "]____________\n\n";
        cout << "Player1 Choice: " << ChoiceName(RoundInfo.enPlayerChoice) << endl;
    cout << "Computer Choice: " <<
        ChoiceName(RoundInfo.enComputerChoice) << endl;
    cout << "Round Winner : [" << RoundInfo.winnerName << "]\n";
        cout << "__________________________________\n" << endl;
    SetWinnerScreenColor(RoundInfo.enWinner);
}
void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "_____________________ [Game Results]_____________________\n\n";
cout << Tabs(2) << "Game Rounds : " <<
GameResults.gameRoundsNumber << endl;
    cout << Tabs(2) << "Player1 won times : " <<
        GameResults.playerWinTimes << endl;
    cout << Tabs(2) << "Computer won times : " <<
        GameResults.computerWinTimes << endl;
    cout << Tabs(2) << "Draw times : " <<
        GameResults.drawTimes << endl;
    cout << Tabs(2) << "Final Winner : " <<
        GameResults.winnerName << endl;
    cout << Tabs(2) <<
        "___________________________________________________________\n";
    SetWinnerScreenColor(GameResults.enGameWinner);
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.enPlayerChoice == RoundInfo.enComputerChoice)
    {
        return enWinner::Draw;
    }
    switch (RoundInfo.enPlayerChoice)
    {
    case Stone:
        if (RoundInfo.enComputerChoice ==Paper)
        {
            return enWinner::Computer;
        }
        break;
    case Paper:
        if (RoundInfo.enComputerChoice == Scissor)
        {
            return enWinner::Computer;
        }
        break;
    case Scissor:
        if (RoundInfo.enComputerChoice == Stone)
        {
            return enWinner::Computer;
        }
        break;
    }
    //if you reach here then player1 is the winner.
    return enWinner::Player;
}
enGameChoices ReadPlayerChoice() {
    short playerChoice = 0;
    do
    {
        cout << "\nYour Choice: [0]:Stone, [1]:Paper, [2]:Scissors ? "; 
        cin >> playerChoice;
    } while (playerChoice<0||playerChoice>2);

    return (enGameChoices)playerChoice;
}
enGameChoices GetComputerChoice() {
   return (enGameChoices)RandomNumber(0,2);
}
enWinner GetWinnerGame(short playerWinTimes, short computerWinTimes) {
    if (playerWinTimes > computerWinTimes)
        return Player;
    else if (computerWinTimes > playerWinTimes)
        return Computer;
    else
        return Draw;
}
stGameResults FillGameResult(short gameRounds,short playerWinTimes,short computerWinTimes,short drawTimes) {
    stGameResults stGameResults;
    stGameResults.computerWinTimes = computerWinTimes;
    stGameResults.drawTimes = drawTimes;
    stGameResults.playerWinTimes;
    stGameResults.gameRoundsNumber = gameRounds;
    stGameResults.enGameWinner = GetWinnerGame(playerWinTimes, computerWinTimes);
    stGameResults.winnerName = WinnerName(stGameResults.enGameWinner);
    return stGameResults;
}
stGameResults PlayGame() {
    short playerWinTimes=0, computerWinTimes=0, drawTimes=0;
    short HowManyRounds = ReadHowManyRound();
    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        stRoundInfo stRoundInfo;
        cout << "Round [" << GameRound << "]";
        stRoundInfo.roundNumber = GameRound;
        stRoundInfo.enPlayerChoice = ReadPlayerChoice();
        stRoundInfo.enComputerChoice = GetComputerChoice();
        stRoundInfo.enWinner = WhoWonTheRound(stRoundInfo);
        if (stRoundInfo.enWinner == Player)
            ++playerWinTimes;
        else if (stRoundInfo.enWinner == Computer)
            ++computerWinTimes;
        else
            ++drawTimes;
        stRoundInfo.winnerName = WinnerName(stRoundInfo.enWinner);
        PrintRoundResults(stRoundInfo);
        SetWinnerScreenColor(stRoundInfo.enWinner);
    }
    return FillGameResult(HowManyRounds,playerWinTimes, computerWinTimes, drawTimes);
}

void StartGame() {
    short HowManyRound=0;
    char isAgain = 'Y';
    stGameResults stGameResults;
    do
    {
        ResetScreen();
        stGameResults =PlayGame();
        ShowGameOverScreen();
        ShowFinalGameResults(stGameResults);
        cout << "do want to play again ?";
        cin >> isAgain;
    } while (isAgain=='y'||isAgain=='Y');
}

int main()
{
    StartGame();
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
