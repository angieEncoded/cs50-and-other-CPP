for arg in "$@"
do
    sqlite3 movies.db < $arg | awk 'END { print NR-1 }'
done