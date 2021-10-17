-- In 13.sql, write a SQL query to list the names of all people who starred in
-- a movie in which Kevin Bacon also starred.
-- Your query should output a table with a single column for the name of each person.
-- There may be multiple people named Kevin Bacon in the database.
-- Be sure to only select the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.

-- This one was a little harder to track down the bug. Looking for movies.id
-- gave me the same number of rows


-- Get the correct Kevin Bacon
-- This kevin bacon is id 102
-- SELECT id FROM people
-- WHERE name = "Kevin Bacon"
-- AND birth = 1958;


-- Get All the movies he starred in
-- SELECT title FROM movies
-- JOIN stars ON stars.movie_id = movies.id
-- JOIN people ON people.id = stars.person_id
-- WHERE people.id =
-- (SELECT id FROM people
-- WHERE name = "Kevin Bacon"
-- AND birth = 1958);

-- Now get the names of all the OTHER people who starred in those

SELECT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN
-- The movies that Kevin starred in
    (SELECT movies.id FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON people.id = stars.person_id
    WHERE people.id =
    (SELECT people.id FROM people
    WHERE name = "Kevin Bacon"
    AND birth = 1958))
-- Filter Kevin Bacon
AND people.name != "Kevin Bacon"
-- Filter duplicate people
GROUP BY people.id;
























