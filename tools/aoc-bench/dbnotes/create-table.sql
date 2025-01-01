CREATE TABLE entries (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    year INTEGER NOT NULL,
    day INTEGER NOT NULL,
    part INTEGER NOT NULL,
    microsecond INTEGER NOT NULL,
    UNIQUE(year, day, part)  -- Ensures unique combinations of year, day, and part
);
