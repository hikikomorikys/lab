echo "Введите сообщение: "
while true; do
    read message
    echo "$message" | nc localhost 1337
done
