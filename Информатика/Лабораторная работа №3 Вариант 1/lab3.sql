/*
CREATE TABLE authors (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    birth_year INT
);

CREATE TABLE books (
    id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    author_id INT,
    publication_year INT,
    genre VARCHAR(50)
);

CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    registration_date DATE
);

CREATE TABLE borrowed_books (
    user_id INT,
    book_id INT,
    borrow_date DATE NOT NULL,
    return_date DATE
);

ALTER TABLE books ADD CONSTRAINT fk_books_authors FOREIGN KEY (author_id) REFERENCES authors(id);
ALTER TABLE borrowed_books ADD CONSTRAINT fk_borrowed_books_users FOREIGN KEY (user_id) REFERENCES users(id);
ALTER TABLE borrowed_books ADD CONSTRAINT fk_borrowed_books_books FOREIGN KEY (book_id) REFERENCES books(id);

INSERT INTO authors (name, birth_year) VALUES
('Александр Пушкин', 1799),
('Михаил Булгаков', 1891),
('Владимир Набоков', 1899);

INSERT INTO books (title, author_id, publication_year, genre) VALUES
('Капитанская дочка', 1, 1836, 'Роман'),
('Мастер и Маргарита', 2, 1967, 'Роман'),
('Бледный огонь', 3, 1962, 'Роман');

INSERT INTO users (name, registration_date) VALUES
('Тимур Леонов', '2021-03-15'),
('Иван Шурпатов', '2021-06-22'),
('Артём Максимов', '2021-11-30');

INSERT INTO borrowed_books (user_id, book_id, borrow_date, return_date) VALUES
(1, 1, '2024-01-10', '2024-01-25'),
(2, 2, '2024-02-15', NULL),
(3, 3, '2024-03-01', '2024-03-20');
*/
SELECT b.title, b.publication_year, b.genre
FROM books b
JOIN authors a ON b.author_id = a.id
WHERE a.name = 'Михаил Булгаков';

SELECT b.title, a.name as author, b.publication_year
FROM books b
JOIN authors a ON b.author_id = a.id
WHERE b.genre = 'Роман';

SELECT name, registration_date
FROM users
WHERE registration_date BETWEEN '2021-01-01' AND '2021-06-30'
ORDER BY registration_date;

SELECT 
    u.name as user_name,
    b.title as book_title,
    a.name as author,
    bb.borrow_date
FROM borrowed_books bb
JOIN users u ON bb.user_id = u.id
JOIN books b ON bb.book_id = b.id
JOIN authors a ON b.author_id = a.id
WHERE bb.return_date IS NULL;
