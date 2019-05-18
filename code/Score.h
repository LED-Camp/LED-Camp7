#ifndef __SCORE_H__
#define __SCORE_H__

#include <string>
using namespace std;

class Score{
private:
    int NextScoreTable[4];
    int SensorID;
public:
    Score();
    ~Score();
    void getNextScoreTable(int NextScoreTable[4]);
    int getSensorID(void);
    int ParsePayload(string Payload);
};


#endif
