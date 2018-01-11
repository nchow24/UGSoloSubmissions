#nchow24, 250725575 (Nicole Anne Chow)
# Computations for Various Vehicle Rentals

name = raw_input("Please enter your name: ")
code = raw_input("Please enter your classification code: ")

#checking for invalid code input
while code not in ["b", "B", "d", "D", "w", "W"]:
    print("Invalid code")
    code = raw_input("Please re-enter code (B,D or W): ")

#gathering user input for total cost calculations
days = int(input("Please enter the number of rental days: "))
odStart = int(input("Odometer reading at the start of the rental period: "))
odEnd = int(input("Odometer reading at the end of the rental period: "))
#determining distance travelled
km = float(odEnd - odStart)

#budget cost calcuations
if code in["b", "B"]:
    baseCharge = 40*days
    kmCharge = 0.25*km                                             #additional charge based on distance travelled
#daily cost calculations
elif code in["d", "D"]:
    baseCharge = 60*days
    if km/days <= 100:
        kmCharge = 0                                               #no additional charge if distance travelled <= 100km/day
    else:
        kmCharge = 0.25*((km/days)-100)*days                       #additional charge if distance travelled >100km/day
#weekly cost calculations
elif code in["w", "W"]:
    weeks = int((days/7)+(days % 7 > 0))                            #weekly determination with fractions of a week
    baseCharge = 190*weeks
    if (km/weeks) > 1500:
        kmCharge = (100*weeks)+(0.25*((km/weeks)-1500)*weeks)      #additional charge if distance travelled +1500km/week
    elif (km/weeks) > 900:
        kmCharge = 50*weeks                                        #additional charge if distance travelled >900km/week and <1500km/week
    else:
        kmCharge=0

#total balance calculation
total = baseCharge + kmCharge

#Printing total balance details
print("\nCustomer Name: " + name)
print("Classification Code: " + code)
print("Rental Time: " + str(days) + " days")
print("Starting Odometer reading: " + str(odStart) + "km")
print("Ending Odometer reading: " + str(odEnd) + "km")
print("Distance Driven: " + str(km) + "km")
print("Total Balance Due: $" + "%.2f" % total)

