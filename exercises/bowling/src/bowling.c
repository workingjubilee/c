#include "bowling.h"
#include <stddef.h>

typedef bool (*roller_t)(int16_t points);

static bool firstRollOfFrame(int16_t points);
static bool secondRollOfOpenFrame(int16_t points);
static bool thirdRollOfSpare(int16_t points);

const int16_t FRAMES_PER_GAME = 10;
const int16_t PINS_PER_FRAME = 10;

int16_t frameCount = 0;
int16_t frameScore = 0;
int16_t totalScore = 0;
roller_t roller = firstRollOfFrame;

static bool firstRollOfFrame(int16_t points)
{
   frameScore = points;

   if (frameScore < PINS_PER_FRAME)
      roller = secondRollOfOpenFrame;
   else {
      totalScore += frameScore;
      ++frameCount;
      roller = firstRollOfFrame;
   }
   return true;
}

static bool secondRollOfOpenFrame(int16_t points)
{
   frameScore += points;
   ++frameCount;

   if (frameScore < PINS_PER_FRAME) {
      totalScore += frameScore;
      frameScore = 0;
      if (frameCount < FRAMES_PER_GAME)
         roller = firstRollOfFrame;
      else
         roller = NULL;
   } else {
      roller = thirdRollOfSpare;
   }

   return true;
}

static bool thirdRollOfSpare(int16_t points)
{
   totalScore += frameScore;
   totalScore += points;
   frameScore = points;

   if (frameCount < FRAMES_PER_GAME)
      roller = secondRollOfOpenFrame;
   else
      roller = NULL;

   return true;
}

static bool thirdRollOfStrike(int16_t points)
{
   // totalScore += frameScore;
   // totalScore += points;
   // frameScore = points;

   // if (frameCount < FRAMES_PER_GAME)
   //    roller = secondRollOfOpenFrame;
   // else
   //    roller = NULL;

   // return true;
}

static bool fourthRollOfStrike(int16_t points)
{

}

void new_game(void)
{
   frameCount = 0;
   frameScore = 0;
   totalScore = 0;
   roller = firstRollOfFrame;
}

bool roll(int16_t points)
{
   if (!roller)
      return false;

   return roller(points);
}

int16_t score(void)
{
   int16_t result = -1;

   if (!roller)
      result = totalScore;

   return result;
}
