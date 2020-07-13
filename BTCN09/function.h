#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

struct sUser {
	string id;
	string fullname;
	string username;
	string password;
};

struct sProduct {
	string id;
	string name;
	string type;
	int price;
};

struct sProductList {
	sProduct product;
	int cost;
	int number;
};

struct sDate {
	int day;
	int month;
	int year;
};

struct sOrder {
	sDate date;
	int total;
	sProductList* productList;
	int size;
};

struct sOrderInfo {
	sDate date;
	int total;
	int size;
};

bool login(string username, string password);
bool inputStaff(sUser*& user);
bool addStaff(sUser* user);
bool removeStaff(string id);
bool alterStaff(sUser* user);
bool getUserArr(sUser*& userArr, int& num);
bool outputUserArr();

bool addProduct(sProduct* product);
bool alterProduct(sProduct* product);
bool getProduct(string id, sProduct*& product);
bool getProductArr(sProduct*& productArr, int &num);
bool inputProduct(sProduct*& product);
bool outputProductArr();

bool inputProductList(sProductList*& productList, int& n);
bool inputOrder(sOrder*& order);
bool addOrder(sOrder* order);
bool outputOrder();
bool inputDate(sDate*& date);
bool getOrderByDate(sDate* date);