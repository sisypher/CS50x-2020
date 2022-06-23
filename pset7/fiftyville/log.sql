-- Keep a log of any SQL queries you execute as you solve the mystery.

-- maintaining the info about the crime scene --
SELECT description FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28
AND street = "Chamberlin Street";
-- Theft of the CS50 duck took place at 10:15am
-- at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses
-- who were present at the time — each of their interview
-- transcripts mentions the courthouse.

-- maintaining the interviews--
SELECT name, transcript FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28
AND transcript LIKE "%courthouse%";

-- Ruth | Sometime within ten minutes of the theft,
-- I saw the thief get into a car in the courthouse parking
-- lot and drive away. If you have security footage from the
-- courthouse parking lot, you might want to look for cars
-- that left the parking lot in that time frame.

-- Eugene | I don't know the thief's name, but it was someone
-- I recognized. Earlier this morning, before I arrived at the
-- courthouse, I was walking by the ATM on Fifer Street and
-- saw the thief there withdrawing some money.

-- Raymond | As the thief was leaving the courthouse,
-- they called someone who talked to them for less than
-- a minute. In the call, I heard the thief say that they were
-- planning to take the earliest flight out of Fiftyville
-- tomorrow. The thief then asked the person on the other end
-- of the phone to purchase the flight ticket.

-- maintaing info from courthouse security logs --
SELECT hour, minute, activity, license_plate
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28
AND hour = 10 AND minute BETWEEN 15 AND 25;

-- hour | minute | activity | license_plate
-- 10 | 16 | exit | 5P2BI95
-- 10 | 18 | exit | 94KL13X
-- 10 | 18 | exit | 6P58WS2
-- 10 | 19 | exit | 4328GD8
-- 10 | 20 | exit | G412CB7
-- 10 | 21 | exit | L93JTIZ
-- 10 | 23 | exit | 322W7JE
-- 10 | 23 | exit | 0NTHK55

-- identifying those people --
SELECT name FROM people
WHERE license_plate
IN
(SELECT license_plate
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28
AND hour = 10 AND minute BETWEEN 15 AND 25);

-- list of suspects --
-- name
-- Patrick
-- Amber
-- Elizabeth
-- Roger
-- Danielle
-- Russell
-- Evelyn
-- Ernest

-- maintaining info from atm transactions --
SELECT name FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
WHERE account_number
IN
(SELECT account_number
FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28
AND atm_location = "Fifer Street"
AND transaction_type = "withdraw");

-- list of suspects --
-- name
-- Ernest
-- Russell
-- Roy
-- Bobby
-- Elizabeth
-- Danielle
-- Madison
-- Victoria

-- intersection of the two lists of suspects --
SELECT name FROM people
WHERE license_plate
IN
(SELECT license_plate
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28
AND hour = 10 AND minute BETWEEN 15 AND 25)
INTERSECT
SELECT name FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
WHERE account_number
IN
(SELECT account_number
FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28
AND atm_location = "Fifer Street"
AND transaction_type = "withdraw");
-- name
-- Danielle
-- Elizabeth
-- Ernest
-- Russell

-- maintaining info of the earliest --
-- flights out of Fiftyville --

-- maintaing info about airport in Fiftyville --
SELECT id, abbreviation, full_name FROM airports
WHERE city = "Fiftyville";
-- id | abbreviation | full_name
-- 8 | CSF | Fiftyville Regional Airport

-- maintaining the list of people who took the earliest
-- flight out of Fiftyville
SELECT name, destination_airport_id, hour, minute
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE year = 2020 AND month = 7 AND day = 29
AND origin_airport_id = 8
ORDER BY hour ASC, minute;

-- name | destination_airport_id | hour | minute
-- Ernest | 4 | 8 | 20

-- the city that the suspect went to --
SELECT city
FROM airports
WHERE id = 4;
-- city
-- London

-- maintaining info about the accomplice --
SELECT name
FROM people
WHERE phone_number IN
(SELECT receiver FROM phone_calls
JOIN people
ON phone_calls.caller = people.phone_number
WHERE name = "Ernest" AND duration < 60);
-- name
-- Charlotte
-- Berthold

-- the accomplice is Berthold
