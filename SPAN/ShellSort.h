#pragma once
class ShellSort {
public:
	template <typename elementType, typename function>
	static void sort(elementType* arr, unsigned int numberOfItems, function comparison)
	{
		unsigned int distance = 1;

		while (distance < numberOfItems) {
			distance *= 2;
		}

		distance /= 2;

		distance--;

		do
		{
			for (unsigned int i = 0; i < (numberOfItems - distance); i++)
			{
				for (int j = i; j >= 0; j -= distance)
				{
					if (comparison(arr[j], arr[j + distance]))
					{
						break;
					}
					else
					{
						elementType temp = arr[j];
						arr[j] = arr[j + distance];
						arr[j + distance] = temp;
					}
				}
			}

			distance--;
		} while (distance > 0);
	}
};