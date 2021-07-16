cd build
echo "Running Valgrind..."
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=../valgrind-report-full.txt ./membot
echo "Filtering logs..."
cd ..
python leak-check-filter.py
gedit valgrind-leak-report.txt
echo "Done..."