echo "Все запущенные процессы:"
ps aux
echo -e "\nКоличество процессов:"
# wc -l = word count lines
ps aux | wc -l