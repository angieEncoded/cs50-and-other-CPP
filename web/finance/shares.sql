CREATE TABLE 'shares' (
'id' integer PRIMARY KEY AUTOINCREMENT NOT NULL,
'stock_name' varchar(255) NOT NULL,
'stock_symbol' varchar(255) NOT NULL,
'number_of_shares' integer NOT NULL,
'user_id' integer NOT NULL,
FOREIGN KEY (user_id) REFERENCES users(id)
);