# проверяем количество аргументов (if not equal)
if [ $# -ne 2 ]; then
    exit 1
fi
result=$(( $1 * $2 ))
echo "Результат: $result"