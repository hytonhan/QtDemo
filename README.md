# QtDemo

A small c++/Qt project

## Overview

This project is a **C++ / Qt desktop application** built to demonstrate my skills as an aspiring C++ developer.  
The focus of the project is **clean architecture, separation of concerns, and modern C++/Qt practices**, rather than UI complexity.

The application manages domain entities such as students, teachers, and study programs, using a layered architecture backed by an SQL database.


## Goals of the Project

This project was created to demonstrate:

- Practical use of **C++ with Qt (Widgets)**
- Clean **layered architecture** in a non-trivial application
- Separation of **domain logic**, **infrastructure**, and **UI**
- Use of **Qt Model/View architecture**
- Database interaction via **repositories**

## Technologies Used

- **C++ (C++17)**
- **Qt 6**
  - Qt Widgets
  - Qt SQL
- **SQLite**
- **CMake**

## Architecture Overview

The application follows a **layered architecture** inspired by clean architecture principles.

- domain/ → Core business entities and rules
- services/ → Application logic and orchestration
- infra/ → Database access and repositories
- model/ → Qt models (QAbstractListModel)
- ui/ → Qt Widgets UI layer

### Domain Layer (`domain/`)

- Contains **pure business entities**
- No dependency on Qt UI or database code
- Responsible for validation and domain rules

**Example responsibilities:**
- Student validity rules
- Domain-specific behavior

### Service Layer (`services/`)

- Orchestrates use cases
- Coordinates domain objects and repositories
- Contains application-level logic

**Why this exists:**  
To keep UI logic thin and domain logic reusable and testable.

### Infrastructure Layer (`infra/`)

- Handles **database access**
- Implements repository interfaces
- Uses Qt SQL for persistence

**Responsibilities:**
- SQL queries
- Mapping database rows to domain entities
- Database initialization


### Model Layer (`model/`)

- Qt `QAbstractListModel` implementations
- Acts as a bridge between services and UI
- Keeps UI logic independent of storage details


### UI Layer (`ui/`)

- Qt Widgets-based UI
- `.ui` files created with Qt Designer
- UI interacts only with models and services

**Note:**  
The UI layer intentionally contains minimal logic to keep the application maintainable and testable.

## Testing

Unit tests are implemented using **Qt Test**.

### What is tested
- Domain logic
- Service layer behavior
- Repository logic (using an in-memory SQLite database)

### What is intentionally not tested
- UI widgets
- Layout and visual behavior

### Running Tests

```bash
ctest
```

or directly:
```
./domain_tests
```

## Build Instructions
Requirements

- Qt 6 (with Widgets, SQL, Test)
- CMake 3.16+
- C++17 compatible compiler
  
```
mkdir build
cd build
cmake ..
cmake --build .
```
Run the application:
```
./KouluHarkkaTyoQt
```
