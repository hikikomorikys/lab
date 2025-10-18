while true; do
    nc -l 1337
    echo "Сообщение получено" | nc localhost 1337
done
