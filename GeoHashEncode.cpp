// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include<math.h>
using namespace std;
typedef unsigned long long ullong;
char Base32LUT[32] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k', 'm', 'n', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
void showbits(ullong integer, int LengthOfBits) {
	ullong one = 1;
	for (size_t i = 0; i < LengthOfBits; i++)
	{
		cout << ((integer & (one << LengthOfBits - i - 1)) > 0 ? "1" : "0");
	}
	cout << endl;
}
string GeoHashEncode(double L, double B, int n) {//n 为偶数
	const int LengthOfGeoHash = n;
	char* geohashcode = new char[LengthOfGeoHash + 1];
	int LengthOfLatBits = n * 5 / 2;
	int LengthOfLngBits = n * 5 / 2;
	ullong morton = 0;
	ullong probe;
	if (n % 2 != 0) LengthOfLngBits += 1;
	ullong row = (B + 90) / 180 * (1 << LengthOfLatBits);
	ullong col = (L + 180) / 360 * (1 << LengthOfLngBits);
	//cout << "row:" << row << ",col:" << col << endl;

	//showbits(row, LengthOfLatBits);
	//showbits(col, LengthOfLngBits);
	//cout << row << endl;
	//cout << col << endl;
	for (size_t i = 0; i < LengthOfLngBits; i++)
	{
		probe = 1 << i;
		//showbits(probe & row, LengthOfBits);
		//showbits(probe & col, LengthOfBits);
		if (n % 2 != 0) {//对于不同的n有不同的交叉编码方式
			morton |= (row & probe) << i + 1;
			morton |= (col & probe) << i;
		}
		else {
			morton |= (row & probe) << i;
			morton |= (col & probe) << i + 1;
		}
	}
	//showbits(morton, LengthOfGeoHash * 5);
	for (size_t i = 0; i < LengthOfGeoHash; i++)
	{
		probe = 32 - 1;
		int subint = probe & (morton >> ((LengthOfGeoHash - i - 1) * 5));
		//showbits(subint, 5);
		geohashcode[i] = Base32LUT[subint];
	}
	geohashcode[LengthOfGeoHash] = '\0';
	return geohashcode;
}

int main()
{
	double B = -25.382708;
	double L = -49.265506 ;
	B = 42.583;
	L = -5.581;
	cout << endl;
	cout << GeoHashEncode(L, B, 8) << endl;
	cout << GeoHashEncode(L, B, 9) << endl;
	cout << GeoHashEncode(L, B, 10) << endl;
	cout << GeoHashEncode(L, B, 11) << endl;
	cout << GeoHashEncode(L, B, 12) << endl;
	cout << "test end -------------" << endl;

}
