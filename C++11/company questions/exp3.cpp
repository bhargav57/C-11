bool geyYesOrNo(string a, string b)
{
	bool res = true;
	int sizeA = a.size();
	int sizeB = b.size();

	int maxSize = sizeA > sizeB ? sizeA : sizeB;
	int miniSize = sizeA < sizeB ? sizeA : sizeB;

	int i, j;

	string A = a.size() > b.size() ? b : a;
	string B = a.size() > b.size() ? a : b;
	//small size is A
	//Big size is B
	bool isFirstMatched = false;
	for (int i = 0; i < miniSize; )
	{
		for (j = 0; (j < maxSize && i < miniSize);)
		{
			char caA = A[i];
			char caB = B[j];
			if (caA == caB || caA == toupper(caB))
			{
				i++;
				j++;
				if (!isFirstMatched)
				{
					isFirstMatched = true;
				}
			}
			else
			{
				if (!isFirstMatched)
				{
					if (isupper(caB))
					{
						res = false;
						break;
					}
					else if (islower(caB))
					{
						j++;
					}

				}
				else
				{
					if (isupper(caB))
					{
						res = false;
						break;
					}
					else if (islower(caB))
					{
						j++;
					}
				}
			}
		}
		if (res == false)
		{
			break;
		}
	}

	if (j != maxSize && res == true)
	{
		for (int k = j; k < maxSize; k++)
		{
			if (isupper(B[k]))
			{
				res = false;
				break;
			}
			else
			{
				k++;
			}
		}
	}
	return res;
}
