-- In 13.sql, write a SQL query to list the names of all people who starred in
-- a movie in which Kevin Bacon also starred.
-- Your query should output a table with a single column for the name of each person.
-- There may be multiple people named Kevin Bacon in the database.
-- Be sure to only select the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.

-- Get the correct Kevin Bacon
-- SELECT id FROM people
-- WHERE name = "Kevin Bacon"
-- AND birth = 1958;


-- Get All the movies he starred in
-- SELECT title FROM movies
-- JOIN stars ON stars.movie_id = movies.id
-- JOIN people ON people.id = stars.person_id
-- JOIN ratings ON ratings.movie_id = movies.id
-- WHERE people.id =
-- (SELECT id FROM people
-- WHERE name = "Kevin Bacon"
-- AND birth = 1958);

-- Now get the names of all the OTHER people who starred in those and filter Kevin

SELECT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title IN (SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
JOIN ratings ON ratings.movie_id = movies.id
WHERE people.id =
(SELECT id FROM people
WHERE name = "Kevin Bacon"
AND birth = 1958)
) AND people.name != "Kevin Bacon";














