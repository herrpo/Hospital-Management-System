# 🏥 Hospital Patient Record & Management System

A comprehensive **C++ Hospital Management System** implementing multiple data structures and algorithms for efficient patient record management, including undo operations, request queuing, tree-based filtering, hash-based analysis, compression algorithms, and performance tracking.

---

# 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Data Structures & Modules](#data-structures--modules)
- [Project Structure](#project-structure)
- [Installation & Setup](#installation--setup)
- [Usage Guide](#usage-guide)
- [Module Details](#module-details)
- [Performance Analysis](#performance-analysis)
- [Future Improvements](#future-improvements)
- [Contributing](#contributing)
- [License](#license)
- [Author](#author)

---

# 🔍 Overview

This hospital management system is a **console-based C++ application** designed to demonstrate the practical implementation of various data structures and algorithms.

The system manages patient records, tracks operations, supports undo functionality, handles priority-based requests, performs efficient searching, applies compression algorithms, and analyzes performance metrics.

The main goal of this project is to combine theoretical computer science concepts with a realistic software system.

---

# ✨ Features

## 🏥 Core Functionality

- ✅ Add patient records
- ✅ Delete patient records
- ✅ Update patient information
- ✅ Search patients by ID or name
- ✅ Display all patient records
- ✅ Sort records by file size
- ✅ View oldest records
- ✅ Add critical notes
- ✅ Rate patient records

---

# 🚀 Advanced Features

## 🔄 Undo System

Revert previous operations:

- Add operations
- Delete operations
- Update operations

Implemented using:

- Stack (LIFO)

---

## 📝 Operation Logging

Tracks all system activities:

- Patient additions
- Patient deletions
- Updates
- Critical notes
- Queue processing

Implemented using:

- Circular Doubly Linked List

---

## 🎯 Priority Request Queue

Manages patient requests based on urgency.

Priority levels:

- 1 → Low
- 2 → Medium
- 3 → High / Emergency

Implemented using:

- Circular Priority Queue

---

## 🌳 Binary Search Tree Filtering

Provides efficient searching and filtering.

Features:

- Search by date/year
- Priority filtering
- Rating range filtering
- Tree height analysis

Implemented using:

- Binary Search Tree (BST)

---

## 🔑 Hash Table Analysis

Provides fast patient lookup and analytics.

Features:

- Patient lookup
- Category counting
- Priority distribution
- Collision analysis
- Load factor calculation

Implemented using:

- Hash Table with Chaining

---

## 🗜️ Compression Algorithms

Implemented compression techniques:

- Huffman Coding
- LZW Compression
- Shannon-Fano Compression

Features:

- Character frequency analysis
- Compression ratio calculation
- Storage comparison

---

## ⚡ Performance Analysis

Tracks system performance:

- Module execution time
- Operation speed comparison
- Data structure efficiency analysis

---

# 📊 Data Structures & Modules

| Module | Data Structure | Purpose |
|---|---|---|
| M1: Patient Registry | Singly Linked List | Store and manage patient records |
| M2: Operation Log | Circular Doubly Linked List | Track system operations |
| M3: Undo System | Stack (LIFO) | Reverse previous operations |
| M4: Request Management | Circular Priority Queue | Process emergency requests |
| M5: Filter System | Binary Search Tree | Fast searching and filtering |
| M6: Hash Analysis | Hash Table with Chaining | Fast lookup and analytics |
| M7: Compression | Huffman Tree, LZW, Shannon-Fano | Data compression |
| M8: Performance | Circular Array | Track execution performance |

---

# 📂 Project Structure

```text
Hospital-Management-System/

│
├── Hospital.cpp        # Main program
├── Hospital.h          # Header file containing declarations
├── Source.cpp          # Function implementations
├── Makefile            # MinGW build configuration
├── README.md           # Project documentation
└── LICENSE             # MIT License
```

---

# 🚀 Installation & Setup

## Requirements

- C++ Compiler (C++11 or later)
- MinGW (for Makefile compilation)
- Visual Studio 2022 (Recommended)
- Standard C++ Library Support

---

# 🔨 Build Using Makefile (MinGW)

If MinGW is installed:

```bash
mingw32-make
```

After successful compilation:

```bash
./hospital.exe
```

---

# 🖥️ Build Using Visual Studio

1. Open the project in Visual Studio 2022
2. Add the `.cpp` and `.h` files
3. Build the solution
4. Run the application

---

# 📖 Usage Guide

The application uses a numbered menu system.

Users can select operations by entering the corresponding number.

---

# 📋 Menu Modules

## Module 1: Patient Registry

| Option | Description |
|---|---|
| 1 | Add new patient |
| 2 | Delete patient |
| 3 | Update patient |
| 4 | Display all patients |
| 5 | Search patient |
| 6 | Show total records |
| 7 | Sort records |
| 8 | Show oldest records |
| 9 | Add critical note |
| 10 | Display critical patients |

---

## Module 2: Operation Log

| Option | Description |
|---|---|
| 11 | Search logs by patient ID |
| 12 | Search logs by operation type |
| 13 | Search logs by date |
| 14 | Search logs by date range |
| 15 | Generate log report |

---

## Module 3: Undo Stack

| Option | Description |
|---|---|
| 16 | Undo last operation |
| 17 | Show stack depth |
| 18 | Show recent operations |
| 19 | Operation frequency analysis |
| 20 | Clear undo history |

---

## Module 4: Request Queue

| Option | Description |
|---|---|
| 21 | Add request |
| 22 | Add emergency request |
| 23 | Display queue |
| 24 | Process request |
| 25 | Calculate waiting time |

---

## Module 5: Tree Module

| Option | Description |
|---|---|
| 26 | Filter by date |
| 27 | List by priority |
| 28 | Filter by rating |
| 29 | Show tree height |
| 30 | Analyze trends |

---

## Module 6: Hash Module

| Option | Description |
|---|---|
| 31 | Build hash table |
| 32 | Search patient rating |
| 33 | Count categories |
| 34 | Priority analysis |
| 35 | Show collisions |

---

## Module 7: Compression Module

| Option | Description |
|---|---|
| 36 | Character frequency |
| 37 | Huffman compression |
| 38 | LZW compression |
| 39 | Shannon-Fano compression |
| 40 | Compression report |

---

## Module 8: Performance Module

| Option | Description |
|---|---|
| 41 | Recent records |
| 42 | Compare searches |
| 43 | Execution times |
| 44 | Average operation time |
| 45 | Recommend fastest structure |

---

# 🏗️ Module Details

## M1: Patient Registry

**Data Structure:** Singly Linked List

Features:

- Insert
- Delete
- Update
- Search
- Sort
- Patient ratings
- Critical notes

---

## M2: Operation Log

**Data Structure:** Circular Doubly Linked List

Features:

- Operation tracking
- Date filtering
- Patient-specific history

---

## M3: Undo System

**Data Structure:** Stack using Linked List

Features:

- Save previous states
- Restore previous actions
- Track operation history

---

## M4: Request Queue

**Data Structure:** Circular Priority Queue

Features:

- Emergency handling
- Priority ordering
- Waiting time calculation

---

## M5: Filter Tree

**Data Structure:** Binary Search Tree

Features:

- Searching
- Filtering
- Traversal
- Performance measurement

---

## M6: Hash Analysis

**Data Structure:** Hash Table with Chaining

Features:

- Fast searching
- Collision tracking
- Load factor analysis

---

## M7: Compression

Algorithms:

- Huffman Coding
- LZW
- Shannon-Fano

Features:

- Compression comparison
- Size reduction analysis

---

## M8: Performance

**Data Structure:** Circular Array

Features:

- Execution tracking
- Module comparison
- Efficiency analysis

---

# 📈 Performance Analysis

| Operation | Data Structure | Complexity |
|---|---|---|
| Search ID | Linked List | O(n) |
| Search ID | BST | O(log n) average |
| Search ID | Hash Table | O(1) average |
| Insert | Linked List | O(1) |
| Insert | BST | O(log n) |
| Sorting | Linked List | O(n²) |

---

# 🔮 Future Improvements

Possible improvements:

- Graphical User Interface (GUI)
- Database integration
- User authentication
- Doctor and receptionist accounts
- Web version
- Network communication
- Improved storage system

---

# 🤝 Contributing

Contributions are welcome.

Steps:

1. Fork the repository
2. Create a feature branch
3. Commit changes
4. Push your branch
5. Open a Pull Request

---

# 📄 License

This project is licensed under the MIT License.

---

# 👤 Author

**Arian Nabil**

Information Systems Engineering Student

GitHub:

https://github.com/yourusername

---

# ⭐ Project Status

🚧 Currently under development.

Future versions may include additional features, optimizations, and improvements.

---

**Happy Coding! 🚀**

