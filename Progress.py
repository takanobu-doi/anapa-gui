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
        if UserScore[i]>Max:
            UID = [i]
            Max = UserScore[i]
        elif UserScore[i]==Max:
            UID.append(i)
    Color = []
    j = 0
    for i in range(len(UserScore)):
        if j<len(UID):
            if UID[j]==i:
                Color.append("r")
                j += 1
            else:
                Color.append("b")
        else:
            Color.append("b")
    plt.bar(np.array(range(1, len(UserList)+1)), np.array(UserScore),
            tick_label=UserList, align="center", color=Color)
    plt.pause(1)
