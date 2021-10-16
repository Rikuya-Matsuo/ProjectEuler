#include "Task9.h"


Task9::Task9()
{
}


Task9::~Task9()
{
}

void Task9::Run()
{
	// a + b + c = 1000ならびにa < b < cより、
	// a = 1から始めて、bをa + 1から増分しながらループ。
	// cはa, bから求めて、a, b, cがピタゴラス数であるかを調べる。
	// a < b < cが成立しなくなったらaを増分してbをa + 1からループしなおす、一種の二重ループである。
	
	uint16_t items[3];

	bool pythagorean = false;
	for (uint16_t a = 1; a <= 1000 - 2 - 3; ++a)
	{
		uint16_t b = a + 1;

		auto calcC = [a, &b]() -> uint16_t
		{
			return 1000 - a - b;
		};

		uint16_t c = calcC();

		while (a < b && b < c)
		{
			pythagorean = Check(a, b, c);
			if (pythagorean)
			{
				break;
			}

			++b;
			c = calcC();
		}

		if (pythagorean)
		{
			items[0] = a;
			items[1] = b;
			items[2] = c;

			break;
		}
	}

	if (!pythagorean)
	{
		std::cout << "pythagorean not found\n";
	}

	uint32_t product = items[0] * items[1] * items[2];
	std::cout << items[0] << " * " << items[1] << " * " << items[2] << " = " << product << std::endl;
}

bool Task9::Check(uint16_t a, uint16_t b, uint16_t c)
{
	uint32_t aSqr = a * a;
	uint32_t bSqr = b * b;
	uint32_t cSqr = c * c;

	bool isPythagoreanTriplet = (aSqr + bSqr == cSqr);

	return isPythagoreanTriplet;
}
