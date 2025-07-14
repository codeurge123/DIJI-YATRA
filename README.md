# 🚆 Digi-Yatra: Smart City Travel Simulator

**Digi-Yatra** is a C++ based command-line application simulating a travel management system between multiple cities. It incorporates **Dijkstra's algorithm** to determine the shortest path between cities, dynamic traffic condition simulation, and real-time fare estimation based on selected travel modes. Admins can configure city distances, set fares, and simulate roadblocks, while customers can explore travel options interactively.

---

## 🛠️ Features

### 👤 Role-based System
- **Admin** (`password: admin123`)
  - Set/update bus, train, and metro fares.
  - Input distance (graph) between cities.
  - Apply traffic conditions (simulate real-world congestion).
  - Visualize the graph and connectivity matrix.
  - Introduce roadblocks (remove edges).
  - Rank cities by connectivity.

- **Customer** (`password: cust123`)
  - Find the **shortest path** between cities.
  - Get **fare estimates** based on mode of travel.
  - View all possible routes between cities.
  - Apply traffic conditions for real-time simulations.

---

## 🔢 Algorithms and Concepts Used

- **Dijkstra’s Algorithm** – for shortest path computation.
- **Graph Representation** – using adjacency matrix.
- **Randomized Traffic Simulation** – edges are altered by ±20%.
- **Graph Traversal** – DFS to find all routes.
- **Priority Queue** – implemented using STL for Dijkstra’s optimization.
- **Connectivity Matrix** – shows the binary connectivity of cities.
- **City Ranking** – based on the number of direct connections.

---

## 🖥️ User Interface Flow

1. **Captcha Verification**
   - Validates human interaction by identifying ASCII shapes (`triangle`, `diamond`, `hexagon`).

2. **Role Selection**
   - Choose between `admin`, `customer`, or `exit`.

3. **Admin Panel**
   - Configure fares and the city map.
   - Simulate traffic and manage roadblocks.

4. **Customer Panel**
   - Find shortest routes.
   - Estimate fares and generate random ticket numbers.
   - Explore all possible paths between two cities.

5. **Rating System**
   - Users can rate the service (1–5 stars) with ASCII visualization.

---

## 🔐 Default Credentials

| Role     | Username | Password   |
|----------|----------|------------|
| Admin    | admin    | `admin123` |
| Customer | customer | `cust123`  |

---

## 📊 Technologies Used

- **C++ Standard Template Library (STL)**
- **Graph Theory Algorithms**
- **Random Number Generators (`<random>`)**
- **Terminal Text Coloring (ANSI Escape Codes)**

---

## 🎮 How to Run

1. **Compile the Code**
   ```bash
   g++ -o digiyatra main.cpp
