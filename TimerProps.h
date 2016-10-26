#pragma once

class CTimerProps
{
public:
	CTimerProps();
	~CTimerProps();

	enum Type { CountDown = 0, CountUp = 1 };

public:
	CString name;
	COLORREF color;
	LOGFONT font;
	Type type;
	int unit;
	time_t value;
};
