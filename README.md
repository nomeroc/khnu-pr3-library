# 📚 Library Database Management System

A C++ console-based application to manage a book library database with support for:

- Admin & User access modes
- Full CRUD for books, authors, genres, publishers, releases
- JSON data persistence
- Search, filter, and statistical queries

---

## 🗂️ Features

### 🔐 Authentication
- Role-based access: **Admin** (`admin123`) and **User**
- Admins can create, edit, delete data
- Users can search, view, and filter data only
- Password input is masked with `*` characters

### 👨‍💼 Admin Mode
- Manage:
  - Books
  - Authors
  - Genres
  - Publishers
  - Countries
  - Releases
- 15 query tasks implemented (see below)
- Auto-saving to JSON after any change

### 👤 User Mode
- View all books or authors
- Search books by author ID
- Filter books by price range

---

## 📈 Query List (All Implemented ✅)

| #  | Query Description |
|----|-------------------|
| 1  | Show all publishers |
| 2  | Show publishers without email |
| 3  | List authors alphabetically |
| 4  | Show books within a price range |
| 5  | Count number of publishers |
| 6  | Show books by author |
| 7  | Count authors per country |
| 8  | Count copies released by each publisher in a selected year |
| 9  | Show genres of books by selected author |
| 10 | Add new publisher |
| 11 | Update editor phone for a publisher |
| 12 | Adjust all book prices by % (user-defined) |
| 13 | Delete genre by name |
| 14 | Show book with max copies released in a year |
| 15 | Show how many unique books each publisher has released |

---

## 🧱 Project Structure

```
Library/
├── entities/
│   ├── Book.h / .cpp
│   ├── Author.h / .cpp
│   ├── Genre.h / .cpp
│   ├── Publisher.h / .cpp
│   ├── Country.h / .cpp
│   ├── Release.h / .cpp
│
├── managers/
│   ├── BookManager.h / .cpp
│   ├── AuthorManager.h / .cpp
│   ├── GenreManager.h / .cpp
│   ├── PublisherManager.h / .cpp
│   ├── CountryManager.h / .cpp
│   ├── ReleaseManager.h / .cpp
│
├── interfaces/
│   ├── AdminInterface.h / .cpp
│   ├── UserInterface.h / .cpp
│
├── utils/
│   ├── ConsoleUtils.h / .cpp
│   ├── json.hpp  // nlohmann/json single-header library
│
├── AuthManager.h / .cpp
├── main.cpp
├── books.json
├── authors.json
├── genres.json
├── publishers.json
├── countries.json
├── releases.json
```

---

## ⚙️ Requirements

- **C++17** or later
- Windows or Linux
- Visual Studio / g++ / CLion supported

---

## 🚀 How to Build

### ▶ Visual Studio
1. Open solution file
2. Go to Project Properties → C++ Language Standard → **ISO C++17**
3. Build and Run

### ▶ Command Line
```sh
g++ -std=c++17 -o LibraryApp main.cpp *.cpp -I./
./LibraryApp
```

---

## 🔑 Login Credentials

| Role  | Password  |
|-------|-----------|
| Admin | admin123  |

Passwords are masked during typing for security.

---

## 📦 Data Storage

- JSON file-based persistence (e.g., `books.json`, `authors.json`)
- Automatically saved after every change
- Easily portable and editable

---

## 👨‍💻 Author

Developed as a C++ practical assignment using OOP principles, real-world data structures, and modular design.