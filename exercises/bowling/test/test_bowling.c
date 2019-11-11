#include <stddef.h>
#include <stdio.h>
#include "vendor/unity.h"
#include "../src/bowling.h"

#define ARRAY_LENGTH(A) (sizeof(A) / sizeof(A[0]))

void setUp(void)
{
   new_game();
}

void tearDown(void)
{
}

static void roll_previous_scores(size_t score_count, int16_t scores[])
{
   for (size_t score = 0; score < score_count; ++score) {
      char scoreNumber[3] = { 0 };
      snprintf(scoreNumber, 3, "%zu", score);
      TEST_ASSERT_TRUE_MESSAGE(roll(scores[score]), scoreNumber);
   }
}

static void test_a_game_with_all_zeros(void)
{
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 0;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_a_game_with_no_strikes_or_spares(void)
{
   // TEST_IGNORE();               // delete this line to run test
   int16_t previousRolls[] = {
      3, 6, 3, 6, 3, 6, 3, 6, 3, 6,
      3, 6, 3, 6, 3, 6, 3, 6, 3, 6
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 90;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_a_spare_followed_by_zeros(void)
{
   // TEST_IGNORE();
   int16_t previousRolls[] = {
      6, 4, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 10;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_points_scored_in_roll_after_spare_are_counted_twice(void)
{
   // TEST_IGNORE();
   int16_t previousRolls[] = {
      6, 4, 3, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 16;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_consecutive_spares_each_get_one_roll_bonus(void)
{
   // TEST_IGNORE();
   int16_t previousRolls[] = {
      5, 5, 3, 7, 4, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 31;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_spare_in_last_frame_gets_one_roll_bonus_counted_twice(void)
{
   // TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 7, 3, 7
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 17;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_strike_in_frame_with_single_roll(void)
{
   // TEST_IGNORE();
   int16_t previousRolls[] = {
      10, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 10;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_two_rolls_after_strike_are_counted_twice(void)
{
   // TEST_IGNORE();
   int16_t previousRolls[] = {
      10, 5, 3, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 26;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_consecutive_strikes_each_get_two_roll_bonus(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      10, 10, 10, 5, 3, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 81;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_strike_in_last_frame_gets_two_roll_bonus_counted_once(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10, 7, 1
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 18;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_spare_with_two_roll_bonus_does_not_get_bonus_roll(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10, 7, 3
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 20;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_strikes_with_two_roll_bonus_do_not_get_bonus_rolls(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 30;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_strike_with_one_roll_bonus_after_spare_in_last_frame_does_not_get_bonus(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 7, 3, 10
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 20;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_all_strikes_is_perfect_game(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      10, 10, 10, 10, 10, 10,
      10, 10, 10, 10, 10, 10
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 300;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_rolls_cannot_score_negative_points(void)
{
   TEST_IGNORE();
   int16_t score = -1;

   TEST_ASSERT_FALSE(roll(score));
}

static void test_roll_cannot_score_more_than_10_points(void)
{
   TEST_IGNORE();
   int16_t score = 11;

   TEST_ASSERT_FALSE(roll(score));
}

static void test_two_rolls_in_frame_cannot_score_more_than_10_points(void)
{
   TEST_IGNORE();
   int16_t previousScore = 5;
   int16_t score = 6;
   TEST_ASSERT_TRUE(roll(previousScore));

   TEST_ASSERT_FALSE(roll(score));
}

static void test_bonus_roll_after_strike_in_last_frame_cannot_score_more_than_10(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t score = 11;

   TEST_ASSERT_FALSE(roll(score));
}

static void test_two_bonus_rolls_after_strike_in_last_frame_cannot_score_more_than_10(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10, 5
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t score = 6;

   TEST_ASSERT_FALSE(roll(score));
}

static void test_two_bonus_rolls_after_strike_in_last_frame_can_score_more_than_10_if_one_is_strike(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 6
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);

   int16_t expected = 26;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_second_bonus_rolls_after_strike_in_last_frame_cannot_be_strike_if_first_one_not_a_strike(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10, 6
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t score = 6;

   TEST_ASSERT_FALSE(roll(score));
}

static void test_second_bonus_roll_after_strike_in_last_frame_cannot_score_more_than_10(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10, 10
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t score = 11;

   TEST_ASSERT_FALSE(roll(score));
}

static void test_unstarted_game_cannot_be_scored(void)
{
   TEST_IGNORE();
   int16_t expected = -1;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_incomplete_game_cannot_be_scored(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = { 0, 0 };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t expected = -1;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_cannot_roll_more_than_ten_frames(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t score = 0;

   TEST_ASSERT_FALSE(roll(score));
}

static void test_bonus_rolls_for_strike_in_last_frame_must_be_rolled_before_score_calculated(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t expected = -1;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_both_bonus_rolls_for_strike_in_last_frame_must_be_rolled_before_score_calculated(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10, 10
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t expected = -1;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_bonus_roll_for_spare_in_last_frame_must_be_rolled_before_score_calculated(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 7, 3
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t expected = -1;
   int16_t actual = score();

   TEST_ASSERT_EQUAL_INT16(expected, actual);
}

static void test_cannot_roll_after_bonus_roll_for_spare(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 7, 3, 2
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t score = 2;

   TEST_ASSERT_FALSE(roll(score));
}

static void test_cannot_roll_after_bonus_rolls_for_strike(void)
{
   TEST_IGNORE();
   int16_t previousRolls[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 10, 3, 2
   };
   size_t numberOfPreviousRolls = ARRAY_LENGTH(previousRolls);
   roll_previous_scores(numberOfPreviousRolls, previousRolls);
   int16_t score = 2;

   TEST_ASSERT_FALSE(roll(score));
}

int main(void)
{
   UnityBegin("test/test_bowling.c");

   RUN_TEST(test_a_game_with_all_zeros);
   RUN_TEST(test_a_game_with_no_strikes_or_spares);
   RUN_TEST(test_a_spare_followed_by_zeros);
   RUN_TEST(test_points_scored_in_roll_after_spare_are_counted_twice);
   RUN_TEST(test_consecutive_spares_each_get_one_roll_bonus);
   RUN_TEST(test_spare_in_last_frame_gets_one_roll_bonus_counted_twice);
   RUN_TEST(test_strike_in_frame_with_single_roll);
   RUN_TEST(test_two_rolls_after_strike_are_counted_twice);
   RUN_TEST(test_consecutive_strikes_each_get_two_roll_bonus);
   RUN_TEST(test_strike_in_last_frame_gets_two_roll_bonus_counted_once);
   RUN_TEST(test_spare_with_two_roll_bonus_does_not_get_bonus_roll);
   RUN_TEST(test_strikes_with_two_roll_bonus_do_not_get_bonus_rolls);
   RUN_TEST(test_strike_with_one_roll_bonus_after_spare_in_last_frame_does_not_get_bonus);
   RUN_TEST(test_all_strikes_is_perfect_game);
   RUN_TEST(test_rolls_cannot_score_negative_points);
   RUN_TEST(test_roll_cannot_score_more_than_10_points);
   RUN_TEST(test_two_rolls_in_frame_cannot_score_more_than_10_points);
   RUN_TEST(test_bonus_roll_after_strike_in_last_frame_cannot_score_more_than_10);
   RUN_TEST(test_two_bonus_rolls_after_strike_in_last_frame_cannot_score_more_than_10);
   RUN_TEST(test_two_bonus_rolls_after_strike_in_last_frame_can_score_more_than_10_if_one_is_strike);
   RUN_TEST(test_second_bonus_rolls_after_strike_in_last_frame_cannot_be_strike_if_first_one_not_a_strike);
   RUN_TEST(test_second_bonus_roll_after_strike_in_last_frame_cannot_score_more_than_10);
   RUN_TEST(test_unstarted_game_cannot_be_scored);
   RUN_TEST(test_cannot_roll_more_than_ten_frames);
   RUN_TEST(test_incomplete_game_cannot_be_scored);
   RUN_TEST(test_bonus_rolls_for_strike_in_last_frame_must_be_rolled_before_score_calculated);
   RUN_TEST(test_both_bonus_rolls_for_strike_in_last_frame_must_be_rolled_before_score_calculated);
   RUN_TEST(test_bonus_roll_for_spare_in_last_frame_must_be_rolled_before_score_calculated);
   RUN_TEST(test_cannot_roll_after_bonus_roll_for_spare);
   RUN_TEST(test_cannot_roll_after_bonus_rolls_for_strike);

   return UnityEnd();
}
