#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Clearing the preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i != j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
            else
            {
                preferences[ranks[i]][ranks[j]] = 0;    
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int c = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[c].winner = i;
                    pairs[c].loser = j;
                    c++;
                    pair_count++;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[c].winner = j;
                    pairs[c].loser = i;
                    c++;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int x = 0, y = 0, z = 0;
    int temp_winner, temp_loser;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > x)
            {
                x = preferences[pairs[j].winner][pairs[j].loser];
            }
        }
        for (int k = 0; k < pair_count; k++)
        {
            if (z != 1)
            {
                if (x == preferences[pairs[k].winner][pairs[k].loser])
                {
                    z++;
                    temp_winner = pairs[i].winner;
                    temp_loser = pairs[i].loser;
                    pairs[i].winner = pairs[k].winner;
                    pairs[i].loser = pairs[k].loser;
                    pairs[k].winner = temp_winner;
                    pairs[k].loser = temp_loser;
                }
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int locked_count = 0;
    for (int i = 0; i < pair_count; i++)
    {
        int temp_winner = pairs[i].winner, temp_loser = pairs[i].loser;
        for (int j = 0; j < locked_count; j++)
        {
            if (pairs[j].winner == temp_loser)
            {
                temp_loser = pairs[j].loser;
            }
        }
        if (temp_winner != temp_loser)
        {
            for (int k = locked_count - 1; k >= 0; k--)
            {
                if (pairs[k].winner == temp_loser)
                {
                    temp_loser = pairs[k].loser;
                }   
            } 
            if (temp_winner != temp_loser)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
                locked_count++;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int f = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                f++;
            }
        }
        if (f == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }    
    return;
}

