#ifndef __1352847_KMP_H__
#define __1352847_KMP_H__

#include <vector>
#include <string>
using std::vector;
using std::string;

vector<unsigned int> prefixFunction(const string& source)
{
	vector<unsigned int> pi(source.length());
	pi[0] = 0;
	for (unsigned int i = 1; i < source.length(); ++i) {
		int j = pi[i - 1];
		while (j > 0 && source[j] != source[i]) {
			j = pi[j - 1];
		}
		if (source[j] != source[i]) {
			pi[i] = 0;
			continue;
		}
		pi[i] = j + 1;
	}
	return pi;
}

#endif