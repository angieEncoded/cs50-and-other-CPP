-- In 10.sql, write a SQL query to list the names of all people who have
-- directed a movie that received a rating of at least 9.0.
-- Your query should output a table with a single column for the name of each person.
-- If a person directed more than one movie that received a rating of at least 9.0,
-- they should only appear in your results once.

-- Same thing here. I was selecting distinct name and should have been
-- grouping by the ids.

SELECT name FROM people
JOIN ratings on ratings.movie_id = movies.id
JOIN directors ON directors.person_id = people.id
JOIN movies ON movies.id = directors.movie_id
WHERE ratings.rating >= 9.0
GROUP BY people.id;