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

    UID = []
    Max = -1
    for i in range(len(UserScore)):
        if len(UID)==0:
            UID = [i]
        else:
            for j in range(len(UID)):
                if UserScore[i]>UserScore[UID[j]]:
                    UID[j:j] = [i]
                    break
                else:
                    UID[j+1:j+1] = [i]
                    break
    Color = []
    Hatch = []
    for i in range(len(UserScore)):
        if i<len(UID):
            if UID[0]==i:
                Color.append("r")
                Hatch.append("*")
            if UID[1]==i:
                Color.append("b")
                Hatch.append("")
            else:
                Color.append("k")
                Hatch.append("")
        else:
            Color.append("k")
            Hatch.append("")
    plt.bar(np.array(range(1, len(UserList)+1)), np.array(UserScore),
            tick_label=UserList, align="center", color=Color)
    plt.pause(1)
