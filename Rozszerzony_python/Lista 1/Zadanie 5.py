from collections import Counter

testlist = ["Cyprian", "cyberotoman", "cynik", "ceniąc", "czule"]
testlist2 = ["Sakura","Sasuke","Shikamaru","Sakurcia","SakutoxD"]


def common_prefix(list):
    list=[slowo.lower() for slowo in list]
    prefixes=[]

    for i in range(len(list)):
        slowo=list[i]
        for j in range(1,len(slowo)+1):
            prefixes.append(slowo[:j])

    licznik = {}
    for i in prefixes:
        if i not in licznik:
            licznik[i]=1
        else:
            licznik[i]+=1

    najdluzsze=""
    for key in licznik:
        if licznik[key]>=3:
            if len(key)>len(najdluzsze):
                najdluzsze=key

    return najdluzsze

print(common_prefix(testlist))
print(common_prefix(testlist2))

