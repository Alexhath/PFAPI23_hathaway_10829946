# 🚗 Highway Route Planning 

## 📌 Project Description
This project implements a system for managing service stations on a highway and planning the optimal route with the fewest stops. The problem is solved using a binary search tree structure representing service stations and a linked list for calculating the route.

### ✨ Key Features:
- Adding and removing service stations.
- Managing available vehicles at each station.
- Planning the route with the fewest stops between two stations.
- Prioritizing routes with stations closer to the highway start in case of multiple equivalent solutions.

## 📂 File Structure
- **main.c**: Contains the program implementation, including functions for managing stations, vehicles, and route calculation.
- **Testo Prova Finale 2023.pdf**: Detailed problem specifications.

## 🛠️ Problem-Solving Approach
The problem is solved using:
- **Binary Search Tree (BST)**: Used to efficiently organize and search for service stations.
- **Linked Lists**: Used to maintain the optimal route and manage available cars at each station.
- **Route Planning Algorithm**:
  1. Given a starting point and a destination, the program finds the route with the fewest stops.
  2. The route that minimizes the distance of intermediate stops from the start is chosen.
  3. If no valid route exists, the program returns "no route".

## 📄 Input/Output Format
The program reads textual commands from input and returns textual responses:

### 📥 Input Commands
- `add-station : [distance , number-of-cars , car-autonomy-1 ... car-autonomy-n]
- `remove-station: [distance]`
- `add-car: [station-distance , car-autonomy]`
- `scrap-car: [station-distance car-autonomy]`
- `plan-route: [start-distance end-distance]`

### 📤 Expected Output
- `added` / `not added`
- `removed` / `not removed`
- `added` / `not added`
- `scrapped` / `not scrapped`
- Sequence of station distances in the optimal route or `no route`

---
📌 **Author:** [Alex Hathaway]  
📧 **Contact:** [alex.hathaway@mail.polimi.it]  
📜 **License:** MIT

