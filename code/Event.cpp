/**
 * @file Event.cpp
 * @brief イベント管理
 * @author Naoki Okayama
 * @date 2017/06/28
 */
#include "Event.h"

#include "iostream"
#include "Controller.h"
#include <unistd.h>   //_getch
#include <termios.h>  //_getch
#include <fcntl.h>

#define ABS_FLOAT(a) ((a) < 0.0F?(a)*-1.0F:(a))


int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, F_SETFL, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ch = ungetc(ch, stdin);
        return 1;
    }

    return 0;

}

char getch() {
    char buf = 0;
    struct termios old = { 0 };
    fflush (stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
}

//////////////////////////////////////////////////////////
// public
//////////////////////////////////////////////////////////
/**
 * @brief コンストラクタ
 * @param -
 * @return -
 * @sa -
 */
Event::Event(Controller *controller) :
          distanceOld(0.0F),
          angleOld(0.0F),
          rangingDistanceOld(0){

    this->event = 0;
    this->controller = controller;
}

/**
 * @brief イベントを更新する
 * @parame -
 * @return -
 * @sa -
 */
int Event::updateEvent() {
    char c;
    float distance;
    float angle;

    float absDistanceDiff;
    float absAngleDiff;

    float rangingDistance;

    uint16_t red, green, blue, clear;
    
    bool left, center, right;

    if (kbhit()) {
        c = getchar();
    }

    if(c == 'q'){
      return -1;
    }

    controller->getPosition(&distance, &angle);
    absDistanceDiff = ABS_FLOAT(this->distanceOld - distance);
    absAngleDiff = ABS_FLOAT(this->angleOld - angle);
    controller->getLineValue(&left, &center, &right);
    controller->getColorValue(&red, &green, &blue, &clear);
    rangingDistance = controller->getRanging();

    if(rangingDistance != this->rangingDistanceOld){
      this->event |= E_CHANGE_RANGING;
    }else{
      this->event &= ~E_CHANGE_RANGING;
    }

    if(red   != this->redOld   ||
       green != this->greenOld ||
       blue  != this->blueOld
       ){
      this->event |= E_CHANGE_COLOR;
    }else{
      this->event &= ~E_CHANGE_COLOR;
    }


    // E_UPイベント判定
    if (c == 'w') {
        this->event |= E_UP;
    } else {
        this->event &= ~E_UP;
    }

    // E_DOWNイベント判定
    if (c == 's') {
        this->event |= E_DOWN;
    } else {
        this->event &= ~E_DOWN;
    }

    // E_LEFTイベント判定
    if (c == 'a') {
        this->event |= E_LEFT;
    } else {
        this->event &= ~E_LEFT;
    }

    // E_RIGHTイベント判定
    if (c == 'd') {
        this->event |= E_RIGHT;
    } else {
        this->event &= ~E_RIGHT;
    }

    if (absDistanceDiff > 0.005) {
        this->event |= E_CHANGE_DISTANCE;
    } else {
        this->event &= ~E_CHANGE_DISTANCE;
    }

    if (absAngleDiff > 0.01) {
        this->event |= E_CHANGE_ANGLE;
    } else {
        this->event &= ~E_CHANGE_ANGLE;
    }

    // if((controller->subscrTopic() == RET_SUCCESS) &&
    //    (controller->dequeueMessage() != RET_FAILED)){
    //      this->event |= E_REACH;
    // }else{
    //     this->event &= ~E_REACH;
    // }

    printf("distance=%f,angle=%f,ranging=%f,color_r=%d,color_g=%d,color_b=%d,line_l=%d,line_c=%d,line_r=%d\n",
	   distance, angle, rangingDistance, red, green, blue, left, center, right);
    this->distanceOld = distance;
    this->angleOld = angle;
    this->rangingDistanceOld = rangingDistance;
    this->redOld = red;
    this->greenOld = green;
    this->blueOld = blue;

    return 0;
}

/**
 * @brief イベントを取得する
 * @parame -
 * @return イベント
 * @sa -
 */
unsigned long Event::getEvent() {
    return this->event;
}
