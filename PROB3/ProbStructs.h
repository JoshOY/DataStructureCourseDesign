#ifndef __1352847_PROBSTRUCT_H__
#define __1352847_PROBSTRUCT_H__

typedef struct _Pos
{
public:
	int x;
	int y;

	bool operator<(const _Pos& rhs) const {
		if (this->x < rhs.x) {
			return true;
		}
		else if (this->x == rhs.x) {
			if (this->y < rhs.y) {
				return true;
			}
			return false;
		}
		else {
			return false;
		}
	}
} Pos;

#endif