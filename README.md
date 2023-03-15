# Lem-in

The goal of this project is to find the quickest way to get n ants across the farm.

Obviously, there are some basic constraints. To be the first to arrive, ants will need to take the shortest path (and that isn’t necessarily the simplest).
They will also need to avoid traffic jams as well as walking all over their fellow ants.

The farm or maps are display in the following way :

number_of_ants
the_rooms
the_links

<img width="255" alt="Screenshot 2023-03-15 at 11 47 40" src="https://user-images.githubusercontent.com/32699739/225271789-adf9b5ca-be80-4027-adf2-ba2f57c6dcce.png">

(example available in the repo >> cat map)

<img width="429" alt="Screenshot 2023-03-15 at 11 13 08" src="https://user-images.githubusercontent.com/32699739/225271536-450030bd-0304-49e0-a8e1-d3dc1c15616e.png">

At the start of the game all the ants are in the start room, at each turn you can move each ant only once and through a tube (the room at the receiving end must be empty).

## Usage

```
https://github.com/wdclem/Lem-in.git
```

make in the root of the repository

To test the program
```
 ./lem-in < map
 ```

## Solving

The project is divide in two parts, first you need to take the instruction map/farm and save the info from it.
The room are save with their link as linked list.

The second part is the search algortithm, we use mostly a Ford Fulkerson with some freedom in the implementation to fit the requirement of the exercice.
The idea is to keep track of the different path, taking that our algorithm always find the fastest path first, we go back from the end and update the map.
At the end of the process we are left with path groups.
We then define which path groups is the best.
Then move the ants according to the rule choosing which road of the path to take by using path->len + path->ants_in to define which one to use.

Result should print as follow

<img width="217" alt="Screenshot 2023-03-15 at 11 35 33" src="https://user-images.githubusercontent.com/32699739/225271164-634cff08-318f-47f4-8c07-d449eed85582.png">


The program was made with the focus on keeping the speed as a priority, the algorithm use a bitmask system to make that possible.
It was a fun program to make with many way to solve it.
