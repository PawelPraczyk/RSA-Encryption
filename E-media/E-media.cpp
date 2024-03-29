#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class KeyMemory
{
public:
	int e, n, d, Fi;
	KeyMemory()
	{
		n = 0;
		e = 0;
		d = 0;
		Fi = 0;
	}
};
bool CzyPierwsza(int liczba)
{

	if (liczba < 2)
		return false;
	for (int i = 2; i*i <= liczba; i++)
		if (liczba%i == 0)
			return false;
	return true;
}
int LiczbaPierwsza()
{
	srand(time(NULL));
	int p;
	bool s = false;
	while (s == false)
	{
		p = rand();
		if (CzyPierwsza(p))
		{
			s = true;
		}
	}
	return p;
}

int NWD(long long a, long long b)
{
	int pom;
	while (b != 0)
	{
		pom = b;
		b = a % b;
		a = pom;
	}
	return a;
}
int calculateE(long long Fi)
{

	int e;

	for (e = 2; e < Fi; e++)
	{
		if (NWD(e, Fi) == 1)
		{
			return e;
		}
	}

	return -1;
}
long int calculateD(long long int e, long long int t)
{
	long int d;
	long int k = 1;

	while (1)
	{
		k = k + t;

		if (k % e == 0)
		{
			d = (k / e);
			return d;
		}
	}

}
KeyMemory RSAkeyCreate()
{
	KeyMemory user1;
	long long int p1=0, p2=0, Fi, e, d = 0;
	long long int n;
	while(p1 ==p2)
	{
		p1 = LiczbaPierwsza();
		p2 = LiczbaPierwsza();
	}
	
	cout <<"P1: " << p1 << " P2: " << p2 << endl;

	Fi = (p1 - 1)*(p2 - 1);
	n = p1 * p2;

	e = calculateE(Fi);

	d = calculateD(e, Fi);
	user1.d = d;
	user1.Fi = Fi;
	user1.n = n;
	user1.e = e;

	return user1;
}
int Encryption(long long int e, long long int n, long long int t)
{
	long long int j, k, r, c = 1, pot, pom = 1, p1, p2 = 0;
	long long int y;
	pot = e;
	vector<long long int> rozklad;
	vector<long long int> wykladniki, index, ost;

	while (pot != 0)
	{
		while (pom <= pot)
		{
			pom = pom * 2;
		}
		pom = pom / 2;
		pot = pot - pom;
		rozklad.push_back(pom);
		pom = 1;
	}

	for (int i = 0; i < rozklad.size(); i++)
	{
		cout << rozklad[i] << endl;
	}

	p1 = rozklad[0];
	if (p1 == 1)
	{
		c = p1 % n;
	}

	else
	{
		while (p1 != 1)
		{
			index.push_back(p1);
			wykladniki.push_back(p1);
			p1 = p1 / 2;
		}
		y = t % n;
		index.push_back(1);
		wykladniki.push_back(y);

		for (int i = index.size() - 2; i >= 0; i--)
		{
			p1 = wykladniki[i + 1];
			p1 = p1 * p1 % n;
			wykladniki[i] = p1;
		}
		for (int i = 0; i < rozklad.size(); i++)
		{
			for (int j = 0; j < index.size(); j++)
			{
				if (rozklad[i] == index[j])
					ost.push_back(wykladniki[j]);
			}
		}
		for (int i = 0; i < ost.size(); i++)
		{
			c = c * ost[i];
		}

	}
	c = c % n;
	cout << "Encryption: " << c << endl;
	return c;

}
int Decryption(long long int c, long long int n, long long int d)
{
	long long int j, k, r, pot, pom = 1, p1, p2 = 0;
	long long int t = 1;
	long long int y;
	pot = d;
	vector<long long int> rozklad;
	vector<long long int> wykladniki, index, ost;

	while (pot != 0)
	{
		while (pom <= pot)
		{
			pom = pom * 2;
		}
		pom = pom / 2;
		pot = pot - pom;
		rozklad.push_back(pom);
		pom = 1;
	}

	for (int i = 0; i < rozklad.size(); i++)
	{
		cout << rozklad[i] << endl;
	}

	p1 = rozklad[0];
	if (p1 == 1)
	{
		t = p1 % n;
	}

	else
	{
		while (p1 != 1)
		{
			index.push_back(p1);
			wykladniki.push_back(p1);
			p1 = p1 / 2;
		}
		y = c % n;
		index.push_back(1);
		wykladniki.push_back(y);

		for (int i = index.size() - 2; i >= 0; i--)
		{
			p1 = wykladniki[i + 1];
			p1 = p1 * p1 % n;
			wykladniki[i] = p1;
		}
		for (int i = 0; i < rozklad.size(); i++)
		{
			for (int j = 0; j < index.size(); j++)
			{
				if (rozklad[i] == index[j])
					ost.push_back(wykladniki[j]);
			}
		}
		for (int i = 0; i < ost.size(); i++)
		{
			t = t * ost[i];
			t = t % n;
		}

	}
	
	cout << "Decryption: " << t << endl;
	return t;
}


int main()
{
	KeyMemory user1;

	user1 = RSAkeyCreate();
	cout << "Public Key [" << user1.e << ", " << user1.n << "] " << endl;
	cout << "Private Key [" << user1.d << ", " << user1.n << "] " << endl;
	Decryption(encription(user1.e, user1.n, 135532), user1.n, user1.d);

}

