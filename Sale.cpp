/*


	NAME			:	MUHAMMAD ZUHAIRY BIN RAZALY
	MATRIX NUMBER	:	B032310282
	COURSE			:	BITS
	TOPIC			:	GROCERIES SALE TRACKER
	CURRENT FILE	:	sale.cpp file


*/


#include "Sale.h"
#include <ctime>
#include <iomanip>
#include "DBConnection.h"
#include "Item.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace sql;

Sale::Sale() {
	//initialize
	saleId = 0;
	userId = 0;
	subtotal= 0;
	//categoryId = 0;
}

Sale::Sale(int saleId, int userId, double subtotal) {
	this->saleId = saleId;
	this->userId = userId;
	this->subtotal = subtotal;
	//this->categoryId = category_id;

}

Sale::Sale(sql::ResultSet* data) {
	saleId = data->getInt("sale_id");
	userId = data->getInt("user_id");
	subtotal = data->getDouble("subtotal");

}






//list all sale by user
vector<Sale> Sale::findSaleDate() {

	string query = "SELECT * FROM sale";

	DBConnection db;
	db.prepareStatement(query);

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {


		cout << "\n\n---------------------------------------------------------------------------------";
		cout << "\nSALE ID\t\t|USER ID\t|TOTAL\t\t\t|DATE\t\t\t|" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {
			Sale tmpSale(db.res);
			sales.push_back(tmpSale);
			sql::SQLString timestampValue = db.res->getString("date_time");

			cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("user_id") << "      \t|" << db.res->getDouble("subtotal") << "      \t\t|" << timestampValue << "\t|" << endl;
			cout << fixed << showpoint;
			cout << setprecision(2);

		}

		cout << "---------------------------------------------------------------------------------" << endl;
	}

	db.~DBConnection();
	return sales;
}





//list all sale by user
vector<Sale> Sale::findSale() {

	string query = "SELECT * FROM sale";

	DBConnection db;
	db.prepareStatement(query);

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\n\n---------------------------------------------------------";
		cout << "\nSALE ID\t\t|USER ID\t|TOTAL\t\t\t|" << endl;
		cout << "---------------------------------------------------------" << endl;
		while (db.res->next()) {
			Sale tmpSale(db.res);
			sales.push_back(tmpSale);

				cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("user_id") << "      \t|" << db.res->getDouble("subtotal") << "      \t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);

		}
		cout << "---------------------------------------------------------" << endl;
	}

	db.~DBConnection();
	return sales;
}








//list all sale by user
vector<Sale> Sale::findSaleRange(double minValue, double maxValue) {

	DBConnection db;
	db.prepareStatement("SELECT * FROM sale WHERE subtotal>=? AND subtotal<=? ORDER BY subtotal");
	db.stmt->setInt(1,minValue);
	db.stmt->setInt(2, maxValue);
	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nAll Sale Recorded";
		cout << "\n\n---------------------------------------------------------";
		cout << "\nSALE ID\t\t|USER ID\t|TOTAL\t\t\t|" << endl;
		cout << "---------------------------------------------------------" << endl;
		while (db.res->next()) {
			Sale tmpSale(db.res);
			sales.push_back(tmpSale);

			cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("user_id") << "      \t|" << db.res->getDouble("subtotal") << "      \t\t|" << endl;
			cout << fixed << showpoint;
			cout << setprecision(2);

		}
		cout << "---------------------------------------------------------" << endl;
	}
	else {
		cout << "\nNo sale data found!";
	}

	db.~DBConnection();
	return sales;
}








//list all sale by user
vector<Sale> Sale::findSaleRangeMax(double maxValue) {

	DBConnection db;
	db.prepareStatement("SELECT * FROM sale WHERE subtotal<=? ORDER BY subtotal");
	db.stmt->setInt(1, maxValue);
	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nAll Sale Recorded";
		cout << "\n\n---------------------------------------------------------";
		cout << "\nSALE ID\t\t|USER ID\t|TOTAL\t\t\t|" << endl;
		cout << "---------------------------------------------------------" << endl;
		while (db.res->next()) {
			Sale tmpSale(db.res);
			sales.push_back(tmpSale);

			cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("user_id") << "      \t|" << db.res->getDouble("subtotal") << "      \t\t|" << endl;
			cout << fixed << showpoint;
			cout << setprecision(2);

		}
		cout << "---------------------------------------------------------" << endl;
	}
	else {
		cout << "\nNo sale data found!";
	}

	db.~DBConnection();
	return sales;
}






//list all sale by user
vector<Sale> Sale::findSaleRangeMin(double minValue) {

	DBConnection db;
	db.prepareStatement("SELECT * FROM sale WHERE subtotal>=? ORDER BY subtotal");
	db.stmt->setInt(1, minValue);
	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nAll Sale Recorded";
		cout << "\n\n---------------------------------------------------------";
		cout << "\nSALE ID\t\t|USER ID\t|TOTAL\t\t\t|" << endl;
		cout << "---------------------------------------------------------" << endl;
		while (db.res->next()) {
			Sale tmpSale(db.res);
			sales.push_back(tmpSale);

			cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("user_id") << "      \t|" << db.res->getDouble("subtotal") << "      \t\t|" << endl;
			cout << fixed << showpoint;
			cout << setprecision(2);

		}
		cout << "---------------------------------------------------------" << endl;
	}
	else {
		cout << "\nNo sale data found!";
	}

	db.~DBConnection();
	return sales;
}




//list all sale by user
vector<Sale> Sale::findSaleMaxMin(double subtotal) {

	string query = "SELECT * FROM sale WHERE subtotal=?";

	DBConnection db, db1, db2;
	db.prepareStatement(query);
	db.stmt->setDouble(1, subtotal);

	int itemId;
	double itemPrice, totalPrice;

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\n\n---------------------------------------------------------------------------------";
		cout << "\nSALE ID\t\t|USER ID\t|TOTAL\t\t\t|DATE\t\t\t|" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {
			Sale tmpSale(db.res);
			sales.push_back(tmpSale);
			sql::SQLString timestampValue = db.res->getString("date_time");

			cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("user_id") << "      \t|" << db.res->getDouble("subtotal") << "      \t\t|" << timestampValue << "\t|" << endl;
			cout << fixed << showpoint;
			cout << setprecision(2);

			cout << "---------------------------------------------------------------------------------" << endl;


			cout << "\nSale Breakdown";

			db1.prepareStatement("SELECT * FROM sale_item WHERE sale_id=?");
			db1.stmt->setInt(1, db.res->getInt("sale_id"));
			db1.QueryResult();

			if (db1.res->rowsCount() > 0) {
				cout << "\n\n-------------------------------------------------------------------------------------------------";
				cout << "\nSALE ID\t\t|ITEM ID\t|ITEM PRICE\t\t|QUANTITY\t|TOTAL PRICE\t\t|" << endl;
				cout << "-------------------------------------------------------------------------------------------------" << endl;

				while (db1.res->next()) {
					itemId = db1.res->getInt("item_id");
					db2.prepareStatement("SELECT * FROM item WHERE item_id=?");
					db2.stmt->setInt(1, itemId);
					db2.QueryResult();

					if (db2.res->rowsCount() > 0) {
						while (db2.res->next()) {

							itemPrice = db2.res->getDouble("item_price");
							totalPrice = itemPrice * (db1.res->getInt("quantity"));

							cout << "" << db1.res->getInt("sale_id") << "\t\t|" << db1.res->getInt("item_id") << "      \t|" << fixed << setprecision(2) << itemPrice << "      \t\t|" << db1.res->getInt("quantity") << "      \t|" << fixed << setprecision(2) << totalPrice << "      \t\t|" << endl;
							cout << fixed << showpoint;
							cout << setprecision(2);

						}

					}



					
				}
				cout << "-------------------------------------------------------------------------------------------------" << endl;
			}





		}
		//cout << "---------------------------------------------------------" << endl;
	}

	db.~DBConnection();
	return sales;
}







//list all sale by user
vector<Sale> Sale::findHighLowSale() {

	DBConnection db, db1, dbSize;
	int itemId, itemCount;
	double itemPrice, totalPrice, subTotalItem, minimum_value;

	dbSize.prepareStatement("SELECT COUNT(item_id) FROM sale_item");
	dbSize.QueryResult();

	while (dbSize.res->next()) {
		itemCount = dbSize.res->getInt(1);

		cout << "Total item = " << itemCount << endl;
	}
	std::vector<double> myTotal(itemCount);
	int y = 0;
	std::vector<double> myTotal1(y);

	subTotalItem = 0;
	int i = 0;

	db.prepareStatement("SELECT * FROM item");

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\n\n-------------------------------------------------------------------------------------------------";
		cout << "\nITEM ID\t\t|ITEM NAME \t\t\t\t|TOTAL SALE\t\t\t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {

			itemId = db.res->getInt("item_id");
			itemPrice = db.res->getDouble("item_price");

			db1.prepareStatement("SELECT * FROM sale_item WHERE item_id=?");
			db1.stmt->setInt(1, itemId);
			db1.QueryResult();


			if (db1.res->rowsCount() > 0) {

				while (db1.res->next()) {
					totalPrice = itemPrice * (db1.res->getInt("quantity"));

					subTotalItem = subTotalItem + totalPrice;



				}



				if ((db.res->getString("item_name")).length() > 8 && (db.res->getString("item_name")).length() <= 12) {
					cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << subTotalItem << "      \t\t\t\t|" << endl;
					cout << fixed << showpoint;
					cout << setprecision(2);

				}
				else if ((db.res->getString("item_name")).length() > 12 && (db.res->getString("item_name")).length() <= 16) {
					cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << subTotalItem << "      \t\t\t\t|" << endl;
					cout << fixed << showpoint;
					cout << setprecision(2);
				}
				else if ((db.res->getString("item_name")).length() > 16) {
					cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t|" << subTotalItem << "      \t\t\t\t|" << endl;
					cout << fixed << showpoint;
					cout << setprecision(2);
				}
				else {
					cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t\t|" << subTotalItem << "      \t\t\t\t|" << endl;
					cout << fixed << showpoint;
					cout << setprecision(2);
				}

				myTotal[i] = subTotalItem;
				i++;

				/*cout << "\nItem Name = " << db.res->getString("item_name") << endl;
				cout << "Total Sale for this item = " << subTotalItem << endl;*/
				subTotalItem = 0;

			}


		}
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		//std::cout << "Highest Sale Recorded = " << *std::max_element(std::begin(myTotal), std::end(myTotal));
		minimum_value = *min_element(begin(myTotal), end(myTotal));
		cout << "\nHighest Item Sale Recorded = " << *max_element(begin(myTotal), end(myTotal)) << endl;



		auto min_non_zero_it = std::min_element(begin(myTotal), end(myTotal), [](double a, double b) {
			return a != 0 && (b == 0 || a < b);  // Prioritize non-zeros and compare values
			});

		double min_non_zero_value = *min_non_zero_it;  // Dereference iterator to get the value

		cout << "\nLowest Item Sale Recorded = " << min_non_zero_value << endl;




		db.~DBConnection();
		return sales;
	}
}









vector<Sale> Sale::findSaleItem() {

	DBConnection db;
	int itemId, saleId;
	double itemPrice, totalPrice;
	string itemName;

	string query = "SELECT si.sale_id, si.item_id, i.item_price, i.item_name, si.quantity, s.date_time "
		"FROM sale_item si "
		"INNER JOIN item i ON si.item_id = i.item_id "
		"INNER JOIN sale s ON si.sale_id = s.sale_id";

	db.prepareStatement(query);

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\n\n----------------------------------------------------------------------------------------------------------------------";
		cout << "\nSALE ID\t|ITEM ID|ITEM PRICE\t|QUANTITY\t|TOTAL PRICE\t|ITEM NAME \t\t\t|SALE TIME           |" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {
			saleId = db.res->getInt("sale_id");
			itemId = db.res->getInt("item_id");
			itemPrice = db.res->getDouble("item_price");
			totalPrice = itemPrice * db.res->getInt("quantity");
			sql::SQLString timestampValue = db.res->getString("date_time");
			itemName = db.res->getString("item_name");



			if (itemName.length() > 8 && (itemName.length() <= 12)) {
				cout << "" << saleId << "\t|" << itemId << "   \t|" << fixed << setprecision(2) << itemPrice << "   \t|" << db.res->getInt("quantity") << "   \t\t|" << fixed << setprecision(2) << totalPrice << "   \t|" << itemName << "      \t\t|" << timestampValue << " |" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if (itemName.length() > 12 && (itemName.length() <= 16)) {
				cout << "" << saleId << "\t|" << itemId << "   \t|" << fixed << setprecision(2) << itemPrice << "   \t|" << db.res->getInt("quantity") << "   \t\t|" << fixed << setprecision(2) << totalPrice << "   \t|" << itemName << "      \t\t|" << timestampValue << " |" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if (itemName.length() > 16) {
				cout << "" << saleId << "\t|" << itemId << "   \t|" << fixed << setprecision(2) << itemPrice << "   \t|" << db.res->getInt("quantity") << "   \t\t|" << fixed << setprecision(2) << totalPrice << "   \t|" << itemName << "      \t|" << timestampValue << " |" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else {
				cout << "" << saleId << "\t|" << itemId << "   \t|" << fixed << setprecision(2) << itemPrice << "   \t|" << db.res->getInt("quantity") << "   \t\t|" << fixed << setprecision(2) << totalPrice << "   \t|" << itemName << "      \t\t\t|" << timestampValue << " |" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}


		}
		cout << "----------------------------------------------------------------------------------------------------------------------\n";
	}

	db.~DBConnection();
	return sales;
}











//list all sale by item
vector<Sale> Sale::findSaleCategory(int category_id) {

	DBConnection db, db1;
	int itemId, categoryId;
	double itemPrice, totalPrice, subtotal;

	subtotal = 0;

	string query = "SELECT * FROM sale_item";

	db.prepareStatement(query);

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nSALES IN THIS CATEGORY";
		cout << "\n\n-------------------------------------------------------------------------------------------------";
		cout << "\nSALE ID\t\t|ITEM ID\t|ITEM PRICE\t\t|QUANTITY\t|TOTAL PRICE\t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {

			itemId = db.res->getInt("item_id");
			db1.prepareStatement("SELECT * FROM item WHERE item_id=?");
			db1.stmt->setInt(1, itemId);
			db1.QueryResult();

			if (db1.res->rowsCount() > 0) {
				while (db1.res->next()) {

					categoryId = db1.res->getInt("category_id");

					if (categoryId == category_id) {
						itemPrice = db1.res->getDouble("item_price");
						totalPrice = itemPrice * (db.res->getInt("quantity"));
						subtotal = subtotal + totalPrice;

						cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("item_id") << "      \t|" << fixed << setprecision(2) << itemPrice << "      \t\t|" << db.res->getInt("quantity") << "      \t|" << fixed << setprecision(2) << totalPrice << "      \t\t|" << endl;
						cout << fixed << showpoint;
						cout << setprecision(2);
					}


				}
			}





		}
		cout << "-------------------------------------------------------------------------------------------------\n";
		cout << "       \t\t|       \t|          \t\t|SUM     \t|" << subtotal <<"      \t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}

	db.~DBConnection();
	return sales;
}






//list all sale by item
vector<Sale> Sale::findSaleItemID(int item_id) {

	DBConnection db, db1;
	int itemId, categoryId, item_ID;
	double itemPrice, totalPrice, subtotal;

	subtotal = 0;

	string query = "SELECT * FROM sale_item";

	db.prepareStatement("SELECT * FROM sale_item WHERE item_id=?");
	db.stmt->setInt(1, item_id);

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nSALES FOR THIS ITEM";
		cout << "\n\n-------------------------------------------------------------------------------------------------";
		cout << "\nSALE ID\t\t|ITEM ID\t|ITEM PRICE\t\t|QUANTITY\t|TOTAL PRICE\t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {

			db1.prepareStatement("SELECT * FROM item WHERE item_id=?");
			db1.stmt->setInt(1, item_id);
			db1.QueryResult();

			if (db1.res->rowsCount() > 0) {
				while (db1.res->next()) {

						itemPrice = db1.res->getDouble("item_price");
						totalPrice = itemPrice * (db.res->getInt("quantity"));
						subtotal = subtotal + totalPrice;

						cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("item_id") << "      \t|" << fixed << setprecision(2) << itemPrice << "      \t\t|" << db.res->getInt("quantity") << "      \t|" << fixed << setprecision(2) << totalPrice << "      \t\t|" << endl;
						cout << fixed << showpoint;
						cout << setprecision(2);



				}
			}





		}
		cout << "-------------------------------------------------------------------------------------------------\n";
		cout << "       \t\t|       \t|          \t\t|SUM     \t|" << subtotal << "      \t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}
	else {
		cout << "\nItem ID not found!";
	}

	db.~DBConnection();
	return sales;
}





//list all sale by item name
//vector<Sale> Sale::findSaleItemName(string item_name) {
//
//	DBConnection db, db1, dbItem;
//	int itemId, categoryId, item_ID;
//	double itemPrice, totalPrice, subtotal;
//
//	subtotal = 0;
//
//
//	dbItem.prepareStatement("");
//
//	db.prepareStatement("SELECT * FROM sale_item WHERE item_id=?");
//	db.stmt->setInt(1, item_id);
//
//	vector<Sale> sales;
//
//	db.QueryResult();
//
//	if (db.res->rowsCount() > 0) {
//		cout << "\nSALES FOR THIS ITEM";
//		cout << "\n\n-------------------------------------------------------------------------------------------------";
//		cout << "\nSALE ID\t\t|ITEM ID\t|ITEM PRICE\t\t|QUANTITY\t|TOTAL PRICE\t\t|" << endl;
//		cout << "-------------------------------------------------------------------------------------------------" << endl;
//		while (db.res->next()) {
//
//			db1.prepareStatement("SELECT * FROM item WHERE item_id=?");
//			db1.stmt->setInt(1, item_id);
//			db1.QueryResult();
//
//			if (db1.res->rowsCount() > 0) {
//				while (db1.res->next()) {
//
//					itemPrice = db1.res->getDouble("item_price");
//					totalPrice = itemPrice * (db.res->getInt("quantity"));
//					subtotal = subtotal + totalPrice;
//
//					cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("item_id") << "      \t|" << fixed << setprecision(2) << itemPrice << "      \t\t|" << db.res->getInt("quantity") << "      \t|" << fixed << setprecision(2) << totalPrice << "      \t\t|" << endl;
//					cout << fixed << showpoint;
//					cout << setprecision(2);
//
//
//
//				}
//			}
//
//
//
//
//
//		}
//		cout << "-------------------------------------------------------------------------------------------------\n";
//		cout << "       \t\t|       \t|          \t\t|SUM     \t|" << subtotal << "      \t\t|" << endl;
//		cout << "-------------------------------------------------------------------------------------------------" << endl;
//	}
//	else {
//		cout << "\nItem ID not found!";
//	}
//
//	db.~DBConnection();
//	return sales;
//}
