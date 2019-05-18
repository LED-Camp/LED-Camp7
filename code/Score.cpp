#include "CNetMqtt.h"
#include "Score.h"
#include <string.h>
#include <stdio.h>
#include <regex>


Score::Score(){
    int i;
    SensorID = 0;
    for(i = 0; i < 4; i++){
        NextScoreTable[i] = 0;
    }
}
Score::~Score(){
}

//余分なもの消去(念の為用意)
static string DeleteExtra(string str){
    const char* trimCharacterList = " ";
    size_t pos_space = str.find_first_of(trimCharacterList);

    while(pos_space != string::npos){
        str = str.erase(pos_space, 1);
        pos_space = str.find_first_of(trimCharacterList);
    }
    return str;
}

int Score::ParsePayload(string Payload){
    regex rex("(\\-?\\d{1}),(\\-?\\d{1}),(\\-?\\d{1}),(\\-?\\d{1}),(\\d{1})");
    smatch result;
    string str_result[5];
    int i;
    string temp;

    temp = DeleteExtra(Payload); //このPayloadhはグローバル変数
    if(!regex_match(temp, result, rex)){  //マッチしなければエラー
        return 0;
    }
    // result[0]にマッチした全体
    // result[1]以降にマッチした各要素が格納されている
    for(i = 1; i < 5; i++){
        NextScoreTable[i-1] = atoi(result[i].str().c_str());
    }
    SensorID = atoi(result[i].str().c_str());
    return 1;
}

void Score::getNextScoreTable(int NextScoreTable[4]){
    NextScoreTable[0] = this->NextScoreTable[0];
    NextScoreTable[1] = this->NextScoreTable[1];
    NextScoreTable[2] = this->NextScoreTable[2];
    NextScoreTable[3] = this->NextScoreTable[3];

}

int Score::getSensorID(){
    return SensorID;
}
