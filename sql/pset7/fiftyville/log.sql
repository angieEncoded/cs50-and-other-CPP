-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on July 28, 2020
-- and that it took place on Chamberlin Street.


-- Let's look at the crime reports first for that day
SELECT * FROM crime_scene_reports
WHERE year = 2020
AND day = 28
AND month = 7;
-- AND street = "Chamberlin Street";

-- id | year | month | day | street | description
-- 293 | 2020 | 7 | 28 | Axmark Road | Vandalism took place at 12:04. No known witnesses.
-- 294 | 2020 | 7 | 28 | Boyce Avenue | Shoplifting took place at 03:01. Two people witnessed the event.
295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
-- 296 | 2020 | 7 | 28 | Widenius Street | Money laundering took place at 20:30. No known witnesses.
-- 297 | 2020 | 7 | 28 | Humphrey Lane | Littering took place at 16:36. No known witnesses.

-- What was the duck doing at the courthouse? Did Brian get arrested and need a character witness?

-- Hmm. I don't see any join tables. I guess next I'll look at the interviews from that day that mention courthouse
SELECT * FROM interviews
WHERE year = 2020
AND day = 28
AND month = 7
AND transcript LIKE "%courthouse%";

-- id | name | year | month | day | transcript

LEAD FOLLOWED UP
-- 161 | Ruth | 2020 | 7 | 28 |
-- Sometime within ten minutes of the theft,
-- I saw the thief get into a car in the courthouse parking lot and drive away.
-- If you have security footage from the courthouse parking lot, you might want to look
-- for cars that left the parking lot in that time frame.


-- 162 | Eugene | 2020 | 7 | 28 |
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street
-- and saw the thief there withdrawing some money.


-- 163 | Raymond | 2020 | 7 | 28 |
-- As the thief was leaving the courthouse, they called someone who
-- talked to them for less than a minute. In the call, I heard the thief say that they were planning
-- to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other
-- end of the phone to purchase the flight ticket.

-- Leads:
--  thief drove away within 10 minutes
--  was at atm on fifer before 10:15 am
-- was on call less than a minute around 10:15
-- flight ticket will be one of the flights on 29th - whoever was on the other end of that call bought it


-- Lead 1 - the car
SELECT * FROM courthouse_security_logs
WHERE year = 2020
AND day = 28
AND month = 7
AND hour = 10
AND minute >= 15
AND minute <= 25;

id | year | month | day | hour | minute | activity | license_plate
260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55

-- Lead 2 - the ATM
SELECT * FROM atm_transactions
WHERE year = 2020
AND day = 28
AND month = 7
AND transaction_type = "withdraw"
AND atm_location = "Fifer Street";

id | account_number | year | month | day | atm_location | transaction_type | amount
246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35

-- Lead 3 - the call
SELECT * FROM phone_calls
WHERE year = 2020
AND day = 28
AND month = 7
AND duration <= 60;


id | caller | receiver | year | month | day | duration
221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
234 | (609) 555-5876 | (389) 555-5198 | 2020 | 7 | 28 | 60
251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54

-- Lead 4 - the flights
SELECT * FROM flights
WHERE year = 2020
AND day = 29
AND month = 7
AND hour < 12;

id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30


-- I guess I'll have a look at the passenger manifests
SELECT * FROM passengers
WHERE flight_id = 36;

flight_id | passport_number | seat
36 | 7214083635 | 2A
36 | 1695452385 | 3B
36 | 5773159633 | 4A
36 | 1540955065 | 5C
36 | 8294398571 | 6C
36 | 1988161715 | 6D
36 | 9878712108 | 7A
36 | 8496433585 | 7B

SELECT * from passengers
WHERE flight_id = 43;

flight_id | passport_number | seat
43 | 7597790505 | 7B
43 | 6128131458 | 8A
43 | 6264773605 | 9A
43 | 3642612721 | 2C
43 | 4356447308 | 3B
43 | 7441135547 | 4A

-- I wonder if I can now take this data and match up anything meaningful
SELECT * FROM people
WHERE passport_number IN (SELECT passport_number from passengers
WHERE flight_id = 43);

id | name | phone_number | passport_number | license_plate
210641 | Heather | (502) 555-6712 | 4356447308 |
341739 | Rebecca | (891) 555-5672 | 6264773605 |
354903 | Marilyn | (568) 555-3190 | 7441135547 | 0R0FW39
423393 | Carol | (168) 555-6126 | 6128131458 | 81MNC9R
745650 | Sophia | (027) 555-1068 | 3642612721 | 13FNH73
750165 | Daniel | (971) 555-6468 | 7597790505 | FLFN3W0


-- Nothing matches in that list. Let's check the other flight
SELECT * FROM people
WHERE passport_number IN (SELECT passport_number from passengers
WHERE flight_id = 36);

id | name | phone_number | passport_number | license_plate
395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
651714 | Edward | (328) 555-1152 | 1540955065 | 130LD9Z
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
953679 | Doris | (066) 555-9701 | 7214083635 | M51FA04

-- There's a few matches in here for the possible thief
398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- Time to check these four plates again the folks leaving the parking lot - looks like Roger is in the clear
449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X


-- Let's check these atm accounts for these three people
SELECT * FROM bank_accounts
JOIN people ON people.id = bank_accounts.person_id
WHERE people.id IN (449774,560886,686048);


-- Evelyn is a ghost? Interesting.
SELECT * FROM bank_accounts
JOIN people ON people.id = bank_accounts.person_id
WHERE people.id = 560886;

account_number | person_id | creation_year | id | name | phone_number | passport_number | license_plate
76054385 | 449774 | 2015 | 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
49610011 | 686048 | 2010 | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- And somehow both of these people also happened to withdraw money on fifer street. Really?
-- Time to start chasing down the accomplice I suppose
-- I have two phone numbers to track down
254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45


SELECT * FROM people
WHERE phone_number IN ("(676) 555-6554", "(375) 555-8161");

-- Okay, it looks like one of these two is the accomplice. I know that the accomplice bought the ticket
-- but it doesn't look like there is any way to match that up in the database
-- This is the part where we'd just go interview these people.


id | name | phone_number | passport_number | license_plate
250277 | James | (676) 555-6554 | 2438825627 | Q13SVG6
864400 | Berthold | (375) 555-8161 |  | 4V16VO0

-- Bank records?
SELECT * FROM bank_accounts
JOIN people ON people.id = bank_accounts.person_id
WHERE people.id IN (250277,864400 );

account_number | person_id | creation_year | id | name | phone_number | passport_number | license_plate
94751264 | 864400 | 2019 | 864400 | Berthold | (375) 555-8161 |  | 4V16VO0

SELECT * FROM bank_accounts
JOIN people ON people.id = bank_accounts.person_id
WHERE people.id = 250277;

-- Well, it seems James doesn't have a bank account. Presumably that means he couldn't buy the ticket
-- and Berthold would be the accomplice, making Ernest the thief.
-- Let's see where Ernest was bound to - flight 36 going somewhere

-- I want to start small, let's just look at the flight
SELECT * FROM flights
WHERE id = 36;

id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
36 |                8  |                     4  | 2020 | 7     | 29  | 8    | 20

-- This the airport he is fleeing to?
SELECT * FROM airports
WHERE id = 4;

id | abbreviation | full_name | city
4 | LHR | Heathrow Airport | London


-- I hope we get the duck back soon.
