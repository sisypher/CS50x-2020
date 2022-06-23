SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE movies.id IN (SELECT id FROM movies WHERE name = "Johnny Depp")
INTERSECT
SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE movies.id IN (SELECT id FROM movies WHERE name = "Helena Bonham Carter");