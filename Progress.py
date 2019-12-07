import numpy as np
import matplotlib.pyplot as plt
from time import sleep
import os

UserFileName = ".UserNameList.txt"
RunFileName = ".RunNumberList.txt"
ProgressFileName = ".ProgressID"

while True:
    with open(UserFileName) as f:
        UserList = [s.strip() for s in f.readlines()]
        UserScore = []
    for i in range(len(UserList)):
        Score = 0
        if os.path.isfile(ProgressFileName+"{0:02d}.txt".format(i+1)):
            with open(ProgressFileName
                      +"{0:02d}.txt".format(i+1)) as f:
                for s_line in f:            
                    if len(s_line.split())>1:
                        Score = Score + int(s_line.split()[1])            
        UserScore.append(Score)

    UID = [0]
    for i in range(1, len(UserScore)):
        for j in range(len(UID)):
            if UserScore[i]>UserScore[UID[j]]:
                UID[j:j] = [i]
                break
            elif j==len(UID)-1:
                UID[len(UID):len(UID)] = [i]
    Color = []
    Hatch = []
    for i in range(len(UserScore)):
        if i<len(UID):
            if UID[0]==i:
                Color.append("gold")
                Hatch.append("*")
            elif UID[1]==i:
                Color.append("silver")
                Hatch.append("")
            else:
                Color.append("b")
                Hatch.append("")
        else:
            Color.append("b")
            Hatch.append("")
    plt.bar(np.array(range(1, len(UserList)+1)), np.array(UserScore),
            tick_label=UserList, align="center", color=Color)
    plt.pause(30)
