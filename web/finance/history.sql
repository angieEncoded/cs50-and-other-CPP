CREATE TABLE 'history' (
'id' integer PRIMARY KEY AUTOINCREMENT NOT NULL,
'stock_name' varchar(255) NOT NULL,
'stock_symbol' varchar(255) NOT NULL,
'number_of_shares' integer NOT NULL,
'user_id' integer NOT NULL,
'price' double precision NOT NULL,
'purchase_date' datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
'purchase_type' varchar(4),
FOREIGN KEY (user_id) REFERENCES users(id)
);