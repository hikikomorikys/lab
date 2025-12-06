-- Таблица authors
CREATE TABLE IF NOT EXISTS authors (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    birth_year INTEGER
);

-- Таблица books
CREATE TABLE IF NOT EXISTS books (
    id SERIAL PRIMARY KEY,
    title TEXT NOT NULL,
    author_id INTEGER NOT NULL REFERENCES authors(id) ON DELETE CASCADE,
    publication_year INTEGER,
    genre TEXT
);

-- Таблица users
CREATE TABLE IF NOT EXISTS users (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    registration_date DATE NOT NULL
);


-- Таблица borrowed_books
CREATE TABLE IF NOT EXISTS borrowed_books (
    user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    book_id INTEGER NOT NULL REFERENCES books(id) ON DELETE CASCADE,
    borrow_date DATE NOT NULL,
    return_date DATE,
    PRIMARY KEY (user_id, book_id, borrow_date)
);

-- Индекс на authors.name
CREATE INDEX IF NOT EXISTS idx_authors_name
ON authors(name);

-- Индекс на books.title
CREATE INDEX IF NOT EXISTS idx_books_title
ON books(title);

-- Индекс на borrowed_books.borrow_date
CREATE INDEX IF NOT EXISTS idx_borrowed_borrow_date
ON borrowed_books(borrow_date);