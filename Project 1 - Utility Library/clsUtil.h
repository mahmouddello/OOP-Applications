#pragma once
#include <iostream>

class clsUtil
{
private:
	int x;

public:

	enum enCharType {
		smallLetter = 1,
		capitalLetter = 2,
		sepcialChar = 3,
		digit = 4,
		mixChars = 5
	};

	static double readNumber(const std::string& message = "Enter a number: ")
	{
		double number = 0;

		std::cout << message;
		std::cin >> number;

		return number;
	}

	static bool isPerfectNumber(const int& number)
	{
		int sum = 0;

		for (int i = 1; i < number; i++)
			if (number % i == 0)
				sum += i;

		return number == sum;
	}

	static unsigned int sumOfDigits(int number)
	{
		unsigned int reminder = 0, sum = 0;

		while (number > 0)
		{
			reminder = number % 10;
			sum += reminder;
			number = number / 10;
		}

		return sum;
	}

	static int reverseNumber(int number)
	{
		bool isNegative = number < 0;
		if (isNegative)
			number = abs(number);

		int remainder = 0, revNumber = 0;

		while (number > 0)
		{
			remainder = number % 10;
			number = number / 10;
			revNumber = revNumber * 10 + remainder;
		}

		return isNegative ? -revNumber : revNumber;
	}

	static short countDigitFrequency(const short& digitToCheck, int number)
	{
		int freqCount = 0, remainder = 0;

		while (number > 0)
		{
			remainder = number % 10; // getting the digit in ones place
			number = number / 10; // dividing by 10 to remove the digit in ones place
			if (digitToCheck == remainder)
				freqCount++;
		}

		return freqCount;
	}

	static void countAllDigitsFrequncies(const int& number)
	{
		for (int i = 0; i <= 9; i++) // trying all possible digits from 0 - 9
		{
			short digitFreq = clsUtil::countDigitFrequency(i, number);

			if (digitFreq > 0)
				std::cout << "Digit " << i << " frequency is " << digitFreq << " time(s)." << std::endl;

		}
	}

	static std::string encryptMessage(std::string message, const short& encryptionKey)
	{

		for (int i = 0; i < message.length(); i++)
		{

			char encryptedChar = char(message[i]) + encryptionKey;

			message[i] = encryptedChar;
		}

		return message;
	}

	static std::string decryptMessage(std::string message, const short& encryptionKey)
	{

		for (int i = 0; i < message.length(); i++)
		{

			char encryptedChar = char(message[i]) - encryptionKey;

			message[i] = encryptedChar;
		}

		return message;
	}

	static void sRand()
	{
		srand((unsigned)time(NULL));
	}

	static int randomNumber(const int& from, const int& to)
	{	
		return rand() % (to - from + 1) + from;;
	}

	static char getRandomCharacter(enCharType charType)
	{
		switch (charType)
		{
			case enCharType::smallLetter: return char(randomNumber(97, 122));
			case enCharType::capitalLetter: return char(randomNumber(65, 90));
			case enCharType::sepcialChar: return char(randomNumber(33, 47));
			case enCharType::digit: return char(randomNumber(48, 57));
			case enCharType::mixChars: return char(randomNumber(0, 1) ? randomNumber(97, 122) : randomNumber(65, 90));
		}
	}

	static std::string generateWord(enCharType charType, short length)
	{
		std::string word = "";

		for (int i = 0; i < length; i++)
		{
			word += getRandomCharacter(charType);
		}

		return word.substr(0, word.length() - 1);
	}

	static std::string generateKey(enCharType charType, short segments = 4, short segmentLength = 4)
	{
		std::string key = "";

		for (short i = 0; i < segments; i++)
		{
			for (short j = 0; j < segmentLength; j++)
			{
				key += getRandomCharacter(charType);
			}

			key += "-";
		}

		return key.substr(0, key.length() - 1);
	}

	static void generateKeys(short keys, enCharType charType)
	{
		for (short i = 0; i < keys; i++)
			std::cout << generateKey(charType) << std::endl;
	}

	static void swap(int& x, int& y)
	{
		int temp = x;
		x = y;
		y = temp;
	}

	static void swap(std::string& x, std::string& y)
	{
		std::string temp = x;
		x = y;
		y = temp;
	}

	static void swap(double& x, double& y)
	{
		double temp = x;
		x = y;
		y = temp;
	}

	static void swap(char& x, char& y)
	{
		char temp = x;
		x = y;
		y = temp;
	}

	static void fillArrayWithRandomNumbers(int arr[100], int length, int start, int finish)
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = randomNumber(start, finish);
		}
	}

	static void printArray(int array[100], const int& length)
	{

		for (int i = 0; i < length; i++)
			std::cout << array[i] << " ";

		std::cout << "\n";
	}

	static void tabs(short tabCount)
	{
		for (short i = 0; i < tabCount; i++)
			std::cout << "\t";
	}

	static void shuffleArray(int array[100], const int& length)
	{
		for (int i = 0; i < length; i++)
		{
			int randomIndex = randomNumber(1, length - 1);
			swap(array[i], array[randomIndex]);
		}
	}
};

