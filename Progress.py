import numpy as np
import matplotlib.pyplot as plt
from time import sleep

UserFileName = ".UserNameList.txt"
RunFileName = ".RunNumberList.txt"
ProgressFileName = ".ProgressID"

while True:
    with open(UserFileName) as f:
        UserList = [s.strip() for s in f.readlines()]
        UserScore = []
    for i in range(len(UserList)):
        Score = 0
        with open(ProgressFileName
                  +"{0:02d}.txt".format(i+1)) as f:
            for s_line in f:            
                if len(s_line.split())>1:
                    Score = Score + int(s_line.split()[1])
        UserScore.append(Score)

    plt.bar(np.array(range(1, len(UserList)+1)), np.array(UserScore),
            tick_label=UserList, align="center", color="b")
    plt.pause(1)