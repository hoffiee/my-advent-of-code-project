CREATE TABLE entries (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    year INTEGER NOT NULL,
    day INTEGER NOT NULL,
    part INTEGER NOT NULL,
    mean_ms INTEGER NOT NULL,
    variance_ms INTEGER NOT NULL,
    min_ms INTEGER NOT NULL,
    max_ms INTEGER NOT NULL,
    UNIQUE(year, day, part)  -- Ensures unique combinations of year, day, and part
);
