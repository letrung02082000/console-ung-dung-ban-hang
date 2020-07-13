#include"function.h"

bool login(string username, string password) {
	fstream f;
	sUser* user = new sUser;
	f.open("user.bin", ios::in | ios::binary);
	while (!f.eof()) {
		f.read(reinterpret_cast<char*>(user), sizeof(sUser));
		if (user->username == username && user->password == password) {
			cout << "Dang nhap thanh cong!" << endl;
			return true;
		}
	}
	cout << "Sai ten dang nhap hoac mat khau" << endl;
	return false;
	f.close();
}

bool getUserArr(sUser*& userArr, int& num) {
	fstream f;
	sUser* user = new sUser;
	num = 0;
	f.open("user.bin", ios::in | ios::binary);
	while (!f.eof()) {
		f.read(reinterpret_cast<char*>(user), sizeof(sUser));
		++num;
	}
	f.close();
	userArr = new sUser[num];
	int i = 0;
	
	f.open("user.bin", ios::in | ios::binary);
	while (!f.eof()) {
		f.read(reinterpret_cast<char*>(user), sizeof(sUser));
		userArr[i].id = user->id;
		userArr[i].fullname = user->fullname;
		userArr[i].username = user->username;
		userArr[i].password = user->password;
		++i;
	}
	return true;
}

bool inputStaff(sUser*& user) {
	user = new sUser;
	cout << "Nhap id: ";
	getline(cin, user->id);
	cout << "Nhap ho ten: ";
	getline(cin, user->fullname);
	cout << "Nhap username: ";
	getline(cin, user->username);
	cout << "Nhap password: ";
	getline(cin, user->password);
	return true;
}

bool addStaff(sUser* user) {
	fstream f;
	f.open("user.bin", ios::app | ios::binary);
	sUser* userArr = new sUser;
	int num = 0;
	getUserArr(userArr, num);
	if (user->username == "admin101") {
		cout << "Ten dang nhap da ton tai." << endl;
		return false;
	}
	for (int i = 0; i < num - 1; ++i) {
		if (userArr[i].id == user->id) {
			cout << "Nhan vien da co tai khoan." << endl;
			return false;
		}
		if (userArr[i].username == user->username) {
			cout << "Ten dang nhap da ton tai." << endl;
			return false;
		}
	}
	f.write(reinterpret_cast<const char*>(user), sizeof(sUser));
	cout << "Them nhan vien thanh cong!" << endl;
	f.close();
	delete user;
	return true;
}

bool removeStaff(string id) {
	sUser* user = new sUser;
	sUser* userArr;
	sUser* newUserArr;
	int num;
	int pos = -1;
	getUserArr(userArr, num);
	for (int i = 0; i < num - 1; ++i) {
		if (userArr[i].id == id) {
			pos = i;
			break;
		}
	}
	if (pos == -1) {
		cout << "Khong ton tai nguoi dung." << endl;
		return false;
	}
	else {
		newUserArr = new sUser[num - 2];
		for (int i = 0; i < pos; ++i) {
			newUserArr[i] = userArr[i];
		}
		for (int i = pos; i < num - 2; ++i) {
			newUserArr[i] = userArr[i + 1];
		}
		fstream f;
		f.open("user.bin", ios::out | ios::binary);

		for (int i = 0; i < num - 2; ++i) {
			user->id = newUserArr[i].id;
			user->fullname = newUserArr[i].fullname;
			user->username = newUserArr[i].username;
			user->password = newUserArr[i].password;
			f.write(reinterpret_cast<const char*>(user), sizeof(sUser));
		}
		cout << "Da xoa " << userArr[pos].id << endl;
		return true;
	}
}

bool alterStaff(sUser* user) {
	sUser* userArr;
	int num;
	getUserArr(userArr, num);
	for (int i = 0; i < num - 1; ++i) {
		if (userArr[i].id == user->id) {
			userArr[i].fullname = user->fullname;
			userArr[i].username = user->username;
			userArr[i].password = user->password;
			fstream f;
			sUser* user = new sUser;
			f.open("user.bin", ios::out | ios::binary);
			for (int i = 0; i < num - 1; ++i) {
				user->id = userArr[i].id;
				user->fullname = userArr[i].fullname;
				user->username = userArr[i].username;
				user->password = userArr[i].password;
				f.write(reinterpret_cast<const char*>(user), sizeof(sUser));
			}
			return true;
		}
		else continue;
	}
	cout << "Khong ton tai nhan vien." << endl;
	return false;
}

bool outputUserArr() {
	sUser* userArr = new sUser;
	int num = 0;
	getUserArr(userArr, num);
	for (int i = 0; i < num - 1; ++i) {
		cout << userArr[i].id << "\t" << userArr[i].fullname << "\t" << userArr[i].username << "\t" << userArr[i].password << endl;
	}
	return true;
}

bool addProduct(sProduct* product) {
	fstream f;
	f.open("product.bin", ios::app | ios::binary);
	sProduct* tmpProduct = new sProduct;
	if (getProduct(product->id, tmpProduct)) {
		cout << "San pham da ton tai." << endl;
		return false;
	}
	f.write(reinterpret_cast<const char*>(product), 88);
	f.close();
	delete product;
	return true;
}

bool getProduct(string id, sProduct*& product) {
	fstream f;
	int num = 0;
	f.open("product.bin", ios::in | ios::binary);
	while (!f.eof()) {
		f.read(reinterpret_cast<char*>(product), 88);
		++num;
	}
	sProduct* productArr = new sProduct[num];
	int i = 0;
	f.close();
	f.open("product.bin", ios::in | ios::binary);
	while(!f.eof()) {
		f.read(reinterpret_cast<char*>(product), sizeof(sProduct));
		productArr[i].id = product->id;
		productArr[i].name = product->name;
 		productArr[i].type = product->type;
		productArr[i].price = product->price;
		++i;
	}
	for (int i = 0; i < num; ++i) {
		if (productArr[i].id == id) {
			product->id = productArr[i].id;
			product->name = productArr[i].name;
			product->type = productArr[i].type;
			product->price = productArr[i].price;
			return true;
		}
	}
	return false;
}

bool getProductArr(sProduct*& productArr, int &num) {
	fstream f;
	sProduct* product = new sProduct;
	num = 0;
	f.open("product.bin", ios::in | ios::binary);
	while (!f.eof()) {
		f.read(reinterpret_cast<char*>(product), 88);
		++num;
	}
	productArr = new sProduct[num];
	int i = 0;
	f.close();
	f.open("product.bin", ios::in | ios::binary);
	while (!f.eof()) {
		f.read(reinterpret_cast<char*>(product), sizeof(sProduct));
		productArr[i].id = product->id;
		productArr[i].name = product->name;
		productArr[i].type = product->type;
		productArr[i].price = product->price;
		++i;
	}
	return true;
}

bool alterProduct(sProduct* product) {
	sProduct* productArr;
	int num;
	getProductArr(productArr, num);
	for (int i = 0; i < num - 1; ++i) {
		if (productArr[i].id == product->id) {
			productArr[i].name = product->name;
			productArr[i].type = product->type;
			productArr[i].price = product->price;
			fstream f;
			f.open("product.bin", ios::out | ios::binary);
			f.seekg(0, ios::beg);
			for (int i = 0; i < num - 1; ++i) {
				product->id = productArr[i].id;
				product->name = productArr[i].name;
				product->type = productArr[i].type;
				product->price = productArr[i].price;
				f.write(reinterpret_cast<const char*>(product), 88);
			}
			f.close();
			return true;
		}
		else continue;
	}
	cout << "Khong ton tai san pham." << endl;
	return false;
}

bool inputProduct(sProduct*& product) {
	product = new sProduct;
	string id;
	string name;
	string type;
	int price;
	cout << "Nhap ma san pham: ";
	getline(cin, id);
	cout << "Nhap ten san pham: ";
	getline(cin, name);
	cout << "Nhap loai san pham: ";
	getline(cin, type);
	cout << "Nhap gia san pham: ";
	cin >> price;
	cin.ignore();
	product->id = id;
	product->name = name;
	product->type = type;
	product->price = price;
	return true;
}

bool inputProductList(sProductList*& productList, int&n ) {
	n = 0;
	cout << "Nhap so luong san pham: ";
	cin >> n;
	cout << endl;
	productList = new sProductList[n];
	cin.ignore();
	for (int i = 0; i < n; ++i) {
		string id;
		int cost = 0;
		int number = 0;
		sProduct* product = new sProduct;
		cout << "Nhap san pham thu " << i + 1 << " :" << endl;
		while (true) {
			cout << "Nhap ma san pham: ";
			getline(cin, id);
			if (getProduct(id, product)) break;
			else cout << "San pham khong ton tai." << endl;
		}
		cout << "Nhap so luong: ";
		cin >> number;
		cin.ignore();
		cost = product->price * number;
		
		productList[i].cost = cost;
		productList[i].number = number;
		productList[i].product.id = product->id;
		productList[i].product.name = product->name;
		productList[i].product.type = product->type;
		productList[i].product.price = product->price;
	}
	return true;
}

bool outputProductArr() {
	sProduct* productArr;
	int num;
	getProductArr(productArr, num);
	for (int i = 0; i < num - 1; ++i) {
		cout << productArr[i].id << "\t" << productArr[i].name << "\t" << productArr[i].type << "\t" << productArr[i].price << endl;
	}
	return true;
}

bool inputDate(sDate*& date) {
	date = new sDate;
	while (true) {
		cout << "Nam: ";
		cin >> date->year;
		if (date->year > 0) break;
		else cout << "Khong hop le. Nhap lai." << endl;
	}
	while (true) {
		cout << "Thang: ";
		cin >> date->month;
		if (date->month > 0 && date->month <= 12) break;
		else cout << "Khong hop le. Nhap lai." << endl;
	}
	while (true) {
		cout << "Ngay: ";
		cin >> date->day;
		if (date->month == 1 || date->month == 3 || date->month == 5 || date->month == 7 || date->month == 8 || date->month == 10 || date->month == 12) {
			if (date->day > 0 && date->day <= 31) break;
			else cout << "Khong hop le. Nhap lai." << endl;
		}
		else if (date->month == 2) {
			if (date->day > 0 && date->day <= 29) break;
			else cout << "Khong hop le. Nhap lai." << endl;
		}
		else {
			if (date->day > 0 && date->day <= 30) break;
			else cout << "Khong hop le. Nhap lai." << endl;
		}
	}
	return true;
}

bool inputOrder(sOrder*& order) {
	sDate* date;
	sProductList* productList;
	int n = 0;
	int total = 0;
	cout << "Nhap ngay tao: " << endl;
	inputDate(date);
	cout << endl;
	cout << "Nhap danh sach san pham: " << endl;
	inputProductList(productList, n);
	for (int i = 0; i < n; ++i) {
		total += (productList[i].cost);
	}
	//cout << total << endl;
	order->date.day = date->day;
	order->date.month = date->month;
	order->date.year = date->year;
	order->total = total;
	order->size = n;
	order->productList = new sProductList[n];
	for (int i = 0; i < n; ++i) {
		order->productList[i].product = productList[i].product;
		order->productList[i].number = productList[i].number;
		order->productList[i].cost = productList[i].cost;
	}
	return true;
}

bool addOrder(sOrder* order) {
	fstream f;
	sOrderInfo* orderInfo = new sOrderInfo;
	sProductList* productList = new sProductList;
	orderInfo->date = order->date;
	orderInfo->total = order->total;
	orderInfo->size = order->size;
	f.open("order.bin", ios::app | ios::binary);
	if (!f.is_open()) return false;
	f.write(reinterpret_cast<const char*>(orderInfo), sizeof(sOrderInfo));
	for (int i = 0; i < order->size; ++i) {
		*productList = order->productList[i];
		f.write(reinterpret_cast<const char*>(productList), sizeof(sProductList));
	}
	f.close();
	return true;
}

bool outputOrder() {
	fstream f;
	f.open("order.bin", ios::in | ios::binary);
	if (!f.is_open()) {
		cout << "Khong co du lieu." << endl;
		return false;
	}
	int num = 0;
	while(!f.eof()) {
		sOrderInfo* orderInfo = new sOrderInfo;
		f.read(reinterpret_cast<char*>(orderInfo), sizeof(sOrderInfo));
		int n = orderInfo->size;
		for (int i = 0; i < n; ++i) {
			sProductList* productList = new sProductList;
			f.read(reinterpret_cast<char*>(productList), sizeof(sProductList));
		}
		++num;
	}
	f.close();
	f.open("order.bin", ios::in | ios::binary);
	for(int i=0; i<num-1;++i) {
		sOrderInfo* orderInfo = new sOrderInfo;
		f.read(reinterpret_cast<char*>(orderInfo), sizeof(sOrderInfo));
		int n = orderInfo->size;
		cout << orderInfo->date.day << "-" << orderInfo->date.month << "-" << orderInfo->date.year << ":" << endl;
		for (int j = 0; j < n; ++j) {
			sProductList* productList = new sProductList;
			f.read(reinterpret_cast<char*>(productList), sizeof(sProductList));
			cout << "MaSP\tTenSP\tSL\tDonGia\tThanhTien" << endl;
			cout << productList->product.id << "\t" << productList->product.name << "\t" << productList->number << "\t" << productList->product.price << "\t" << productList->cost << endl;
		}
		cout << "Tong tien: " << orderInfo->total << endl;
	}
	return true;
}

bool getOrderByDate(sDate* date) {
	fstream f;
	f.open("order.bin", ios::in | ios::binary);
	if (!f.is_open()) {
		cout << "Khong co du lieu." << endl;
		return false;
	}
	int num = 0;
	while (!f.eof()) {
		sOrderInfo* orderInfo = new sOrderInfo;
		f.read(reinterpret_cast<char*>(orderInfo), sizeof(sOrderInfo));
		int n = orderInfo->size;
		for (int i = 0; i < n; ++i) {
			sProductList* productList = new sProductList;
			f.read(reinterpret_cast<char*>(productList), sizeof(sProductList));
		}
		++num;
	}
	f.close();
	f.open("order.bin", ios::in | ios::binary);
	int dateNum = 0;
	int dateTotal = 0;
	cout << "Thong ke don hang ngay " << date->day << " thang " << date->month << " nam " << date->year << ":" << endl << endl;
	cout << "===" << endl << endl;
	for (int i = 0; i < num - 1; ++i) {
		sOrderInfo* orderInfo = new sOrderInfo;
		f.read(reinterpret_cast<char*>(orderInfo), sizeof(sOrderInfo));
		int n = orderInfo->size;
		if (orderInfo->date.year == date->year && orderInfo->date.month == date->month && orderInfo->date.day == date->day) {
			++dateNum;
			dateTotal += orderInfo->total;
		}
		for (int j = 0; j < n; ++j) {
			sProductList* productList = new sProductList;
			f.read(reinterpret_cast<char*>(productList), sizeof(sProductList));
			if (orderInfo->date.year == date->year && orderInfo->date.month == date->month && orderInfo->date.day == date->day) {
				
				cout << "MaSP\tTenSP\tSL\tDonGia\tThanhTien" << endl;
				cout << productList->product.id << "\t" << productList->product.name << "\t" << productList->number << "\t" << productList->product.price << "\t" << productList->cost << endl;
			}
		}
	}
	cout << "===" << endl << endl;
	cout << "So luong don hang:" << dateNum << endl << "Tong doanh thu ngay: " << dateTotal << endl;
	f.close();
}