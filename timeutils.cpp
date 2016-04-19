#include "timeutils.h"
#include "time.h"


int timeMinute() {
	time_t now = time(0);
	struct tm timestruct = *localtime(&now);
	return timestruct.tm_min;
}

int timeHour() {
	time_t now = time(0);
	struct tm timestruct = *localtime(&now);
	return timestruct.tm_hour;
}

int timeSecond() {
	time_t now = time(0);
	struct tm timestruct = *localtime(&now);
	return timestruct.tm_sec;
}
