import sys

with open("G18_Project1_xv6CustomizeSystemCalls/Makefile", "r") as f:
    text = f.read()

text = text.replace("$U/_alarmtest\\n $U/_mylocktest", "$U/_alarmtest\\\n\t$U/_mylocktest")

with open("G18_Project1_xv6CustomizeSystemCalls/Makefile", "w") as f:
    f.write(text)
