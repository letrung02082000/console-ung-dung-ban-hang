#include"function.h"

int main() {
	int loginStatus = 0;
	int adminStatus = 0;
	while (true)
	{
		if (loginStatus == 0) {
			string username, password;
			cout << "Vui long dang nhap de tiep tuc!" << endl;
			cout << "Username: ";
			getline(cin, username);
			cout << "Password: ";
			getline(cin, password);
			if (username == "admin101" && password == "admin123") {
				cout << "Da dang nhap bang quyen addmin." << endl;
				loginStatus = 1;
				adminStatus = 1;
			}
			else if (login(username, password)) {
				loginStatus = 1;
			}
		}
		while (true)
		{
			if (loginStatus == 1) {
				int opt = 0;
				cout << "1. Them san pham" << endl << "2. Xoa san pham" << endl << "3.Sua san pham" << endl << "4. Tao don hang" << endl << "5. Thong ke don hang va doanh thu theo ngay" << endl << ">Admin" << endl << "6.Them nhan vien" << endl << "7.Xoa nhan vien" << endl << "8.Sua nhan vien" << endl << endl << "9. Dang xuat" << endl << "Chon: ";
				cin >> opt;
				cin.ignore();
				switch (opt)
				{
				case 1:
					cout << "Nhap thong tin san pham:" << endl;
					sProduct* product1;
					inputProduct(product1);
					addProduct(product1);
					break;
				case 2:
					cout << "Nhap ma san pham can xoa: ";
					
					break;
				case 3:
					cout << "Sua san pham:" << endl;
					sProduct* product3;
					inputProduct(product3);
					alterProduct(product3);
					break;
				case 4:
					cout << "Tao don hang:" << endl;
					sOrder* order;
					inputOrder(order);
					addOrder(order);
					break;
				case 5:
					cout << "Thong ke don hang va doanh thu theo ngay:" << endl;
					sDate* date;
					inputDate(date);
					getOrderByDate(date);
					break;
				case 6:
					if (adminStatus == 1) {
						sUser* user6;
						inputStaff(user6);
						addStaff(user6);
					}
					else cout << "Vui long dang nhap bang quyen admin de su dung chuc nang nay!" << endl;
					break;
				case 7:
					if (adminStatus == 1) {
						string id;
						cout << "Nhap id nhan vien: " << endl;
						getline(cin, id);
						removeStaff(id);
					}
					else cout << "Vui long dang nhap bang quyen admin de su dung chuc nang nay!" << endl;
					break;
				case 8:
					if (adminStatus == 1) {
						sUser* user8;
						inputStaff(user8);
						alterStaff(user8);
					}
					else cout << "Vui long dang nhap bang quyen admin de su dung chuc nang nay!" << endl;
					break;
				case 9:
					loginStatus = 0;
					break;
				case 10:
					outputUserArr();
					break;
				case 11:
					outputProductArr();
					break;
				case 12:
					outputOrder();
					break;
				case 13:
					cout << "Khong lam gi ca.";
					break;
				default:
					cout << "Khong hop le. Vui long nhap lai!" << endl;
					break;
				}
			}
			else break;
		}
		
	}
	system("pause");
	return 0;
}