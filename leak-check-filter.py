import os

lines = []
line_to_print = 0

if os.path.exists("valgrind-report-full.txt"):
    valgrind_full_report = open("valgrind-report-full.txt", "r")
    leak_report = open("valgrind-leak-report.txt", "w")
    full_report_lines = valgrind_full_report.readlines()
    count = 0
    for line in full_report_lines:
        count += 1
        if "LEAK SUMMARY" in line:
            line_to_print+=1
        if (line_to_print != 0):
            leak_report.write(line)
        if (line_to_print == 9):
            line_to_print = 0
else:
    print("Log file does not exist, please, run ./leak-check.sh first")
        