# Simulate a sports tournament
import csv
import sys
import random

# Number of simluations to run
# N = 1000
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []

    # TODO: Read teams into memory from file
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:  # every row do something
            # Don't overthink. This is just like building a json object.
            teams.append({"team": row['team'], "rating": int(row['rating'])})
    file.close()  # done with the file
    # for item in teams:
    #     print(item)
    counts = {}
    counter = 0
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):  # not inclusive
        # Get a winning team
        winningTeam = simulate_tournament(teams)
        counter += 1
        # This is just like json objects. It came in on an array, the first item is the object, the second item is the key
        # print(winningTeam[0]['team'])
        # teamName = winningTeam[0]['team']
        # print(teamName)
        # if teamName in counts:
        #     counts[teamName] += 1
        # else:
        #     counts[teamName] = 1
        # Above is my original implementation in which I dealt with the processing outside of the recursive function
        # However this did not pass check50's check and I came across this post https://www.reddit.com/r/cs50/comments/lm01bk/help_with_world_cup_lab_6/
        # after doing a search for simulate_tournament fails to return the name of 1 winning team
        # The first response was exactly what I was running into. So I adjusted it to return just the team name from the recursive function
        # instead of processing it all here.

        if winningTeam in counts:
            counts[winningTeam] += 1
        else:
            counts[winningTeam] = 1

    print(counter)
    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # Base Case
    if (len(teams) == 1):
        winner = teams
        # print(winner)
        # return winner
        return winner[0]["team"]  # check50 is looking for this???

        # Note from angieEncoded 10/04/2021
        # This program was working exactly as expected but wasn't passing Check50, so I turned to the internet
        # and came across this post: https://www.reddit.com/r/cs50/comments/lm01bk/help_with_world_cup_lab_6/
        # which was exactly the same problem I ran into. I returned the entire value from the recursive function
        # and dealt with the processing on the other side, but check50 was expecting it to be dealt with here
        # Which is better? Who knows. My code worked before the change. See lines 37-42 for my original implementation
        # which worked, but didn't pass check50's expectation of a string coming out of this recursive function

    # Recursive case, send in the teams until we have one team left
    winners = simulate_round(teams)
    # dummy dummy dummy remember to RETURN the recursive call or you will get nothing!
    # or in this case "None" since that's what python will print
    return simulate_tournament(winners)


if __name__ == "__main__":
    main()
