#include "Transaction.h"
#include <string> 
using namespace std;

Transaction::Transaction() {
	dateTime = "";
	transactionId = 0;
	userId = 0;
	subtotal = 0;
}

void Transaction::insert(double subtotal1) {

	DBConnection db;
	db.prepareStatement("INSERT INTO sale(user_id, subtotal) VALUES (?,?)");
	db.stmt->setInt(1, userId);
	db.stmt->setDouble(2, subtotal1);
	db.QueryStatement();
	transactionId = db.getGeneratedId();
	// get back the generated id to be used during insertion of transaction items

	string query = "INSERT INTO sale_item(sale_id, item_id, quantity) VALUES "; // (),()
	for (int i = 0; i < items.size(); i++) {
		query += "(?,?,?),";
		// 3 place holder per item/row/record
		//P  1,             2,        3
		// transactionId,productId,quantity 
	}
	query.erase(query.size() - 1); // remove the extra comma at the end
	db.prepareStatement(query);

	for (int i = 0; i < items.size(); i++) {
		// formula for inserting the value into the right index 
		// i * N + P
		// i is the index of item being loop through
		// N is number of place holder you have per row/item in your prepared statement; N = 3
		// P is the position of the value in each row
		// 
		// Example:
		// i=0, 0 * 3 + 1 = 1 || 0 * 3 + 2 = 2 || 0 * 3 + 3 = 3
		// i=1, 1 * 3 + 1 = 4 || 1 * 3 + 2 = 5 || 1 * 3 + 3 = 6
		// i=2, 2 * 3 + 1 = 7 || 2 * 3 + 2 = 8 || 2 * 3 + 3 = 9 

			db.stmt->setInt(i * 3 + 1, transactionId);
			db.stmt->setInt(i * 3 + 2, items[i].first.itemId);
			db.stmt->setInt(i * 3 + 3, items[i].second);
		

	}
	db.QueryStatement();
	db.~DBConnection();



}




void Transaction::addItem(Item item, int quantity) {
	items.push_back({ item,quantity });
}

double Transaction::total() {
	double total = 0;
	for (int i = 0; i < items.size(); i++) {
		total += items[i].first.itemPrice * items[i].second;
	}
	return total;
}

int Transaction::count() {
	double count = 0;
	for (int i = 0; i < items.size(); i++) {
		count += items[i].second;
	}
	return count;
}

//int Transaction::clear() {
//	
//	Transaction sales;
//
//	sales.clear();
//
//}