import matplotlib.pyplot as plt
import requests

#Dane
url1 = "http://api.nbp.pl/api/cenyzlota/2021-01-01/2021-12-31/" #rok 2021
url2 = "http://api.nbp.pl/api/cenyzlota/2022-01-01/2022-12-31/" #rok 2022
url3 = "http://api.nbp.pl/api/cenyzlota/2023-01-01/2023-11-30/" #rok 2023

res1 = requests.get(url1)
res2 = requests.get(url2)
res3 = requests.get(url3)

dane2021 = res1.json()
dane2022 = res2.json()
dane2023 = res3.json()
months2021 = {}
months2022 = {}
months2023 = {}

for p in dane2021:
    data = p["data"][5:7]
    if data in months2021:
        months2021[data]+=p["cena"]
    else:
        months2021[data] = p["cena"]

for p in dane2022:
    data = p["data"][5:7]
    if data in months2022:
        months2022[data]+=p["cena"]
    else:
        months2022[data] = p["cena"]

for p in dane2023:
    data = p["data"][5:7]
    if data in months2023:
        months2023[data]+=p["cena"]
    else:
        months2023[data] = p["cena"]


#zaokraglam ze srednio miesiac ma 30 dni
srednie21 = [round(months2021[x]/30,2) for x in months2021]
srednie22 = [round(months2022[x]/30,2) for x in months2022]
srednie23 = [round(months2023[x]/30,2) for x in months2023]
srednie23.append(srednie22[11]+srednie22[11]*0.05) #nie ma danych na grudzien wiec w grudniu sa takie same jak przewidywane

#przewidywanie cen na 2023
predict23 = []
for i in range(len(srednie21)):
    predict23.append(round(srednie22[i]+0.05*srednie22[i]))

xs = [n for n in months2021]

# Wykres
plt.plot(xs, srednie21, color='blue',marker='o')
plt.plot(xs, srednie22, color='green',marker='o')
plt.plot(xs, predict23, color='orange',marker='o')
plt.plot(xs, srednie23, color='red',marker='o')
plt.legend(["2021","2022","2023-przewidywane","2023-faktyczne"])
plt.ylabel("cena")
plt.xlabel("miesiąc")
plt.title("CENA ZŁOTA")

plt.show()