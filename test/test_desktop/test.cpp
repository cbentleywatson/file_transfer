#include <unity.h>
#define EQUAL true
#define UNEQUAL false
#include <testSWE.h>

/*
	Most of the errors demonstrated in the example are type errors that are caught by
	the compiler in c++. For that reason, I added some additional requirements that might occur in hardware project. The main additional requirement is that the output must always be a positive number. The program must also ensure that the result would not cause an overflow. The first arg must be greater than the second arg.
*/

// This function tests the ordinary case when two acceptable numbers have been
// passed in
void test_plain_mult(void)
{
	int out = multiply(11, 10);
	TEST_ASSERT_EQUAL_INT32(out, (11 * 10));
}
/*
* This function tests that the system won't allow inputs that would yield negative outputs

*/
void test_negative_val(void)
{
	int out = multiply(1, -1);
	TEST_ASSERT_EQUAL_INT32(out, NEGATIVE_ERROR);
}
/*
* This function checks that the result of multiplying the two values being considered will result in a number that can fit inside of a 4 byte integer. In other words,
this test is focused on preventing overflows.
*/

void test_overflow(void)
{
	int a = 2147483640; // max int value minus seven
	int out = multiply(a, 2);
	TEST_ASSERT_EQUAL_INT32(out, OVERFLOW_ERROR);
}
/*
 * In the specifications for this function it says that the function must only return positive values.
 * The function checks if positive * poistive works, the prior checks that negative * positive  fails, and so this checks that negative times negative works.
 */

void test_double_negative(void)
{
	int a = -11; // max int value minus seven
	int b = -12;
	int out = multiply(a, b);
	TEST_ASSERT_EQUAL_INT32(out, a * b);
}
/*
 * Specs for this funct request that the arguments are sorted by size. This checks that.
 */
void test_order(void)
{
	int a = 3; // max int value minus seven
	int b = 7;
	int out = multiply(a, b);
	TEST_ASSERT_EQUAL_INT32(out, ORDER_ERROR);
}

/*
 * Checks if an ordinary string with a few vowles will be processed correctly.
 */

void test_ordinary_string(void)
{

	String input = "Hello"; // max int value minus seven
	String expec = "Hll";
	String out = stripVowels(input);

	bool comp = expec.equals(out);
	TEST_ASSERT_EQUAL_INT32(int(EQUAL), int(comp));
}
/*
 * Tests that empty strings do not cause an exception.
 */

void test_empty_string(void)
{
	bool shouldBe = EQUAL;
	String input = ""; // max int value minus seven
	String expec = "";
	String out = stripVowels(input);

	bool comp = expec.equals(out);
	TEST_ASSERT_EQUAL_INT32(int(shouldBe), int(comp));
}
/*
 * Checks that all lowercase letters are removed/
 */

void test_lowercase_vowel_string(void)
{
	bool shouldBe = EQUAL;
	String input = "aeiou"; // max int value minus seven
	String expec = "";
	String out = stripVowels(input);

	bool comp = expec.equals(out);
	TEST_ASSERT_EQUAL_INT32(int(shouldBe), int(comp));
}
/*
 * Checks that all upper case letters are removed.
 */
void test_uppercase_vowel_string(void)
{
	bool shouldBe = EQUAL;
	String input = "AEIOU"; // max int value minus seven
	String expec = "";
	String out = stripVowels(input);

	bool comp = expec.equals(out);
	TEST_ASSERT_EQUAL_INT32(int(shouldBe), int(comp));
}
/*
 * This function checks that relatively long strings do not cause an issue.
 */
void test_long_string(void)
{
	bool shouldBe = EQUAL;
	String input = "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"; // max int value minus seven
	String expec = input;
	String out = stripVowels(input);

	bool comp = expec.equals(out);
	// UNITY_TEST_ASSERT(false, 12, "Check");
	TEST_ASSERT_EQUAL_INT32(int(shouldBe), int(comp));
}

void setup()
{

	UNITY_BEGIN();
	// Serial.println("Object Section Tests:");
	Serial.println("\nThis function tests the ordinary case when two acceptable numbers have been entered");
	RUN_TEST(test_plain_mult);
	Serial.println("\nThis fnction isn't supposed to return negative values, so this is the first check.");
	RUN_TEST(test_negative_val);

	Serial.println("\nThis test checks that overflow protection is working");
	RUN_TEST(test_overflow);
	// UNITY_TEST_ASSERT(false, 12, "Check");
	Serial.println("\nTests that the function accepts two negatives");
	RUN_TEST(test_double_negative);
	Serial.println("\nTests that the specified order is enforced");
	RUN_TEST(test_order);
	Serial.println("\nChecks that ordinary string are stripped of vowels");
	RUN_TEST(test_ordinary_string);
	Serial.println("\ncheck that empty strings do not cause exceptions");
	RUN_TEST(test_empty_string);
	Serial.println("\nCheck that all lower case vowels are caught");
	RUN_TEST(test_uppercase_vowel_string);
	Serial.println("\nCheck that all upper case vowels are caught");
	RUN_TEST(test_lowercase_vowel_string);
	Serial.println("\nCheck that long strings do not cause errors");
	RUN_TEST(test_long_string);
	UNITY_END();
}

void loop()
{
}