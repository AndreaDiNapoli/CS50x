-- QUERY LOG

-- 1) Search for any kind of information in the reports matchin place and time the duck theft
SELECT * FROM crime_scene_reports
WHERE year = 2020
AND  month = 7
AND day = 28
AND street LIKE "Chamberlin Street";
-- INSIGHTS:
-- Time of crime: 10:15am
-- Crimescene: courthouse
-- Three witnesses interviewd (conducted on the same day)

-- 2) Search for the transcript of the three witnesess interviews on police database, since we know the day they have been registred
SELECT name, transcript FROM interviews
WHERE year = 2020
AND month = 7
AND day = 28;
-- INSIGHTS:
-- None. Too much interviews found.

-- 3) Implement better search for transcripts including filter for "courthouse" word, mentioned in the crimescene report
SELECT name, transcript FROM interviews
WHERE year = 2020
AND month = 7
AND day = 28
AND transcript LIKE "%courthouse%";
-- INSIGHTS:
-- The thief left the crimescene with a car within ten minutes
-- The thief was recognized by a witness near the ATM on Fifer Street in the morning of the same day
-- The thief asked an accomplice to buy the earliest flight leaving Fiftyville the next day

-- 4) Recover any information from the security footage of the courthouse for a relevant timespan near the crimetime
SELECT activity, license_plate FROM courthouse_security_logs
WHERE year = 2020
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute < 25;
-- INSIGHTS:
-- 8 cars left the parking lot within that timespan
-- Lincense plates are: 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

-- 5) Find the first flight leaving the city the day after the crime
SELECT id, hour, minute FROM flights
WHERE origin_airport_id IN(
SELECT id FROM airports
WHERE city = "Fiftyville")
AND year = 2020
AND month = 7
AND day = 29
ORDER BY hour;
-- INSIGHTS:
-- The first flight is registred as id 36 and left at 8:20 on that day

-- 6) Find the destionation of that flight
SELECT abbreviation, full_name, city FROM airports
WHERE id IN (
SELECT destination_airport_id FROM flights
WHERE id = 36);
-- INSIGHTS:
-- The thief probably left for London city, Heathrow Airport

-- 7) Find the list of passengers in that flight
SELECT passport_number, seat FROM passengers
WHERE flight_id = 36;
-- INSIGHTS:
-- The list of passport numbers and seats
-- 7214083635 | 2A
-- 1695452385 | 3B
-- 5773159633 | 4A
-- 1540955065 | 5C
-- 8294398571 | 6C
-- 1988161715 | 6D
-- 9878712108 | 7A
-- 8496433585 | 7B

-- 8) Find information about who used the ATM machine on the morning of the crimeday
SELECT account_number FROM atm_transactions
WHERE year = 2020
AND month = 7
AND day = 28
AND atm_location LIKE "Fifer Street"
AND transaction_type LIKE "%withdraw%";
-- INSIGHTS:
-- Found some account_numbers
-- 28500762
-- 28296815
-- 76054385
-- 49610011
-- 16153065
-- 25506511
-- 81061156
-- 26013199

-- 9) Find information about phone number callers for the day of the theft
SELECT caller, duration FROM phone_calls
WHERE year = 2020
AND month = 7
AND day = 28;
-- INSIGHT:
-- Found 65 unique numbers who made calls that day

-- 10) Combine information retrieved as far to see if we can find a match for the thief
SELECT id, name FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN(
        SELECT account_number FROM atm_transactions
        WHERE year = 2020
        AND month = 7
        AND day = 28
        AND atm_location LIKE "Fifer Street"
        AND transaction_type LIKE "%withdraw%")
    )
INTERSECT
SELECT id, name FROM people
WHERE passport_number IN(
    SELECT passport_number FROM passengers
    WHERE flight_id = 36)
INTERSECT
SELECT id, name FROM people
WHERE license_plate IN(
    SELECT license_plate FROM courthouse_security_logs
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute > 15
    AND minute < 25)
INTERSECT
SELECT id, name FROM people
WHERE phone_number IN(
    SELECT caller FROM phone_calls
    WHERE year = 2020
    AND month = 7
    AND day = 28);
-- INSIGHTS:
-- One possible match (thief identified): Ernest (ID: 686048)

-- 11) Try to identify the thief accomplish by looking phonecalls tablates and searching for calls made by Ernest during crimeday and shorter tha 1 minute
SELECT name FROM people
WHERE phone_number IN(
    SELECT receiver FROM phone_calls
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND duration < 61
    AND caller IN (
        SELECT phone_number FROM people
        WHERE id = 686048));
-- INSIGHT:
-- One single match (accomplish identified): Berthold

-- Mistery Solved!
