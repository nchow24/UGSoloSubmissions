#include <stdio.h>
#define MIN_IN_DAY 1440

int main(void)
{
	int timeDay, timeDuration;
	int validDay = 0, validDuration = 0;
	int dayMinutes, durationMinutes, totalMinutes, convertedTotal;
	
	while ( (validDay == 0) || (validDuration == 0) ){

		printf("Enter the Time of Day & Time Duration: ");
		scanf("%d%d", &timeDay, &timeDuration);
		
		//
		//check if valid timeDay
		//
		if ( (0 <= timeDay) && (timeDay < 10) ){
			validDay = 1;
		} else {
			//
			//check if minutes is less than 60
			//
			if ( (10 <= timeDay) && (timeDay < 100) ){
				if (timeDay <= 59){
					validDay = 1;
				} else {
					validDay = 0;
				}
			} else {
				//
				//check if minutes is less than 60 and hours is less than 24
				//
				if ( (100 <= timeDay) && (timeDay < 2360) ){
					if ( (timeDay % 100) <= 59 ){
						validDay = 1;
					} else {
						validDay = 0;
					}	
				} else {
					validDay = 0;
				}
			}
		}
		
		//
		//check if timeDuration minutes is less than 60
		//
		if ( ( -59 <= (timeDuration % 100)) && ((timeDuration % 100) <= 59) ){
			validDuration = 1;
		} else {
			validDuration = 0;
		}

		//
		// check if both timeDay and timeDuration are valid (0 = not valid, 1 = valid)
		//		
		if ( (validDay == 0) || (validDuration == 0) ){
			printf("Input valid Time of Day and Time Duration.\n");
		}
	}
	
	//
	//convert timeDay and timeDuration to minutes
	//
	dayMinutes = ( ( (timeDay/100) * 60) + (timeDay % 100) );
	durationMinutes = ( ( (timeDuration/100) * 60) + (timeDuration % 100) );
	
	//
	//adding/subtracting more than a day's worth is the same as adding/subtracting the portion of the duration that is less than 1 day.
	//
	if ( (durationMinutes > MIN_IN_DAY) || (durationMinutes < -MIN_IN_DAY)){
		durationMinutes = durationMinutes - ( (durationMinutes/MIN_IN_DAY) * MIN_IN_DAY);
	}

	//
	//subtracting a duration is the same as adding the difference of a day's worth minus the duration.
	//
	if (durationMinutes < 0){
		durationMinutes = MIN_IN_DAY + durationMinutes;
	}
	
	totalMinutes = dayMinutes + durationMinutes;

	//
	//format totalMinutes so it is within the number of minutes within 1 day
	//
	totalMinutes = totalMinutes - ( (totalMinutes/MIN_IN_DAY) * MIN_IN_DAY);

	//
	//convert to 24hr clock
	//
	convertedTotal = ( (totalMinutes/60) * 100 ) + ( totalMinutes % 60 );

	printf("New time: ");
	printf("%.4d\n", convertedTotal);
	
	
}