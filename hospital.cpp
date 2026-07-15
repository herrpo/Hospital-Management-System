#include "Header.h"

int main() {



	// =====================================================
	// MODULLER ARASI BAGLANTI VE SISTEM BASLATMA
	// =====================================================

	// M2: Tum sistem islemlerini kaydeden log sistemi olusturulur.
	Operationlog hospitalLogger;

	// M3: Yapilan islemleri geri almak (undo) icin stack sistemi olusturulur.
	undostack undo;

	// M1: Ana hasta kayit sistemi baslatilir.
	// M1, log sistemi (M2) ve undo sistemi (M3) ile baglantili calisir.
	registration statehospital(&hospitalLogger, &undo);

	// M4: Talep/kuyruk sistemi baslatilir.
	// Kuyruktan cikan hastalar otomatik olarak M1'e aktarilir
	requestQueue queue(&statehospital);

	// M5: Tree (BST) modulu olusturulur.
	// M1 verilerini kullanarak hizli filtreleme ve arama yapar.
	Treemodule filterTree(&statehospital);

	// M6: Hash analiz modulu baslatilir.
	// M1 verilerini hash tablosuna aktararak O(1) arama saglar.
	Hashmodule fastHash(&statehospital);

	// M8: Performans analiz sistemi baslatilir.
	// Tum modullerin calisma surelerini takip eder.
	PerfomansAnaliz performanceTracker;

	// M7: Veri sikistirma modulu baslatilir.
	// M1 verilerini kullanarak Huffman, LZW ve Shannon-Fano analizleri yapar
	Compressionmodule compSystem(&statehospital);




	int choise;

	do {
		menu();
		std::cout << "Lutfen Secim Yapiniz: ";
		std::cin >> choise;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "\nHata: Lutfen sadece rakam giriniz!\n";
			choise = -1;
			continue;
		}

		std::cin.ignore();

		switch (choise) {

		case 1: {
			int id;
			std::string name, category, priority, status;
			double size;

			std::cout << "ID: ";
			std::cin >> id;
			std::cin.ignore();

			std::cout << "Isim: ";
			std::getline(std::cin, name);

			std::cout << "Kategori: ";
			std::getline(std::cin, category);

			std::cout << "Boyut: ";
			std::cin >> size;
			std::cin.ignore();

			std::cout << "Oncelik (Dusuk/Orta/Yuksek): ";
			std::getline(std::cin, priority);

			std::cout << "Durum: (Aktif/Islemde/Arsiv): ";
			std::getline(std::cin, status);

			auto start = std::chrono::high_resolution_clock::now();

			statehospital.addPatient(id, name, category, size, priority, status, 0.0);

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = end - start;
			performanceTracker.recordOperationTime(1, elapsed.count());
			break;

		}

		case 2: {
			int id; std::cout << "ID: ";
			std::cin >> id; statehospital.deleteById(id);
			break;
		}

		case 3: {
			std::string name;
			std::cout << "isim: "; std::getline(std::cin, name);
			statehospital.updateByName(name);
			break;
		}

		case 4: {
			statehospital.listByTimestamp();
			break;
		}

		case 5: {
			int id;
			std::cout << "ID: ";
			std::cin >> id;

			auto start = std::chrono::high_resolution_clock::now();

			statehospital.searchById(id);
			performanceTracker.addRecordAccess(id);

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = end - start;

			performanceTracker.recordOperationTime(1, elapsed.count());
			break;
		}

		case 6: {
			statehospital.totalrecord();
			break;
		}

		case 7: {
			statehospital.sortBysize_SmallToLarge();
			break;
		}

		case 8: {
			statehospital.oldeset10records();
			break;
		}

		case 9: {
			std::string note;
			int id;
			std::cout << "ID: ";
			std::cin >> id; std::cin.ignore();
			std::cout << "NOT: ";
			std::getline(std::cin, note);
			statehospital.AddCriticalNote(id, note);
			break;
		}

		case 10: {
			statehospital.showCritacalRecords();
			break;
		}

		case 11: {
			int id;
			std::cout << "ID: ";
			std::cin >> id;
			std::cin.ignore();
			hospitalLogger.listLogsByPatient(id);
			break;
		}

		case 12: {
			std::string type;
			std::cout << "Tur (Ekle/Sil/Guncelle/Dequeue): ";
			std::getline(std::cin, type);
			hospitalLogger.listLogsByType(type);
			break;
		}

		case 13: {
			std::string targetdate;
			std::cout << "Tarih: ";
			std::getline(std::cin, targetdate);

			auto start = std::chrono::high_resolution_clock::now();
			hospitalLogger.listLogsByDate(targetdate);
			auto end = std::chrono::high_resolution_clock::now();
			performanceTracker.recordOperationTime(4, std::chrono::duration<double, std::milli>(end - start).count());
			break;
		}

		case 14: {
			int startday, startmonth, startyear;
			int endday, endmonth, endyear;

			std::cout << "Baslangic Gun: ";
			std::cin >> startday;
			std::cin.ignore();
			std::cout << "Baslangic ay: ";
			std::cin >> startmonth;
			std::cin.ignore();
			std::cout << "Baslangic yil: ";
			std::cin >> startyear;

			std::cout << "Bitis Gun: ";
			std::cin >> endday;
			std::cin.ignore();
			std::cout << "Bitis ay: ";
			std::cin >> endmonth;
			std::cin.ignore();
			std::cout << "Bitis yil: ";
			std::cin >> endyear;

			auto start = std::chrono::high_resolution_clock::now();
			hospitalLogger.listLogsByDateRange(startday, startmonth, startyear, endday, endmonth, endyear);
			auto end = std::chrono::high_resolution_clock::now();
			performanceTracker.recordOperationTime(4, std::chrono::duration<double, std::milli>(end - start).count());
			break;
		}

		case 15: {
			hospitalLogger.generalreport();
			break;
		}

		case 16: {
			auto start = std::chrono::high_resolution_clock::now();
			statehospital.undolastaction();
			auto end = std::chrono::high_resolution_clock::now();
			performanceTracker.recordOperationTime(4, std::chrono::duration<double, std::milli>(end - start).count());

			break;
		}

		case 17: {
			std::cout << "\n--- GERI ALINABILIR ISLEM SAYISI ---\n";
			std::cout << undo.getdepth();
			break;
		}

		case 18: {
			undo.showlast10();
			break;
		}

		case 19: {
			undo.frequency();
			break;
		}

		case 20: {
			undo.clear();
			break;
		}

		case 21: {
			int id;
			int priority;
			std::string name, category;
			double size;
			std::cout << "ID: ";
			std::cin >> id;
			std::cin.ignore();
			std::cout << "Isim: ";
			std::getline(std::cin, name);
			std::cout << "Kategori: ";
			std::getline(std::cin, category);
			std::cout << "Boyut: ";
			std::cin >> size;
			std::cout << "Oncelik (1:Dusuk, 2:Orta, 3:Yuksek): ";
			std::cin >> priority;
			if (std::cin.fail()) {
				std::cin.clear(); std::cin.ignore(10000, '\n');
				std::cout << "Hata: Oncelik icin sadece 1, 2 veya 3 rakamlarindan birini giriniz!\n";
				break;
			}
			queue.enqueueRequest(id, name, category, size, priority);
			break;
		}

		case 22: {
			int id;
			std::string name, category;
			double size;
			std::cout << "--- ACIL TALEP GIRISI ---\nID: ";
			std::cin >> id;
			std::cin.ignore();
			std::cout << "Isim: ";
			std::getline(std::cin, name);
			std::cout << "Kategori: ";
			std::getline(std::cin, category);
			std::cout << "Boyut: ";
			std::cin >> size;
			queue.enqueueRequest(id, name, category, size, 3);

			break;
		}

		case 23: {
			queue.listQueue();
			break;
		}

		case 24: {
			std::string status;
			std::cout << "Yeni durum: ";
			std::getline(std::cin, status);

			auto start = std::chrono::high_resolution_clock::now();
			queue.dequeueToRegisgtry(status);
			auto end = std::chrono::high_resolution_clock::now();

			performanceTracker.recordOperationTime(4, std::chrono::duration<double, std::milli>(end - start).count());

			break;
		}

		case 25: {
			queue.CalculateAverageTime();
			break;
		}

		case 26: {
			std::string year;
			std::cout << "Yil: ";
			std::getline(std::cin, year);
			filterTree.buildTree();
			filterTree.filterByDate(year);
			break;
		}

		case 27: {
			filterTree.buildTree();
			filterTree.printByPriority();
			break;
		}

		case 28: {
			double minPuan;
			double maxPuan;
			std::cout << "Minimum Puan: ";
			std::cin >> minPuan;
			std::cout << "Maximum Puan: ";
			std::cin >> maxPuan;
			std::cin.ignore();
			filterTree.buildTree();

			auto start = std::chrono::high_resolution_clock::now();
			filterTree.filterByRating(minPuan, maxPuan);
			auto end = std::chrono::high_resolution_clock::now();
			performanceTracker.recordOperationTime(5, std::chrono::duration<double, std::milli>(end - start).count());
			break;
		}

		case 29: {
			filterTree.buildTree();
			filterTree.showHeight();
			break;
		}

		case 30: {
			filterTree.buildTree();
			filterTree.analyzeYear2000();
			break;
		}

		case 31: {
			fastHash.bulidTable();
			break;
		}

		case 32: {
			int targetId;
			std::cout << "Puanini gormek istediginiz hasta ID'si: ";
			std::cin >> targetId;

			auto start = std::chrono::high_resolution_clock::now();
			fastHash.findRatingById(targetId);
			auto end = std::chrono::high_resolution_clock::now();
			performanceTracker.recordOperationTime(4, std::chrono::duration<double, std::milli>(end - start).count());
			break;
		}

		case 33: {
			std::string category;
			std::cin.ignore();
			std::cout << "Sayisini ogrenmek istediginiz kategori: ";
			std::getline(std::cin, category);
			fastHash.countByCategory(category);
			break;
		}

		case 34: {
			fastHash.priorityAnalysis();
			break;
		}

		case 35: {
			fastHash.showCollisions();
			fastHash.showLoadFactor();
			break;
		}

		case 36: {
			compSystem.frequencyAnalysis();
			break;
		}

		case 37: {
			compSystem.huffmanCompression(&performanceTracker);
			break;
		}

		case 38: {
			compSystem.lzwCompression(&performanceTracker);
			break;
		}

		case 39: {
			compSystem.shannonFanoCompression(&performanceTracker);
			break;
		}

		case 40: {
			compSystem.compressionReport();
			break;
		}

		case 41: {
			performanceTracker.listLastAccessed();
			break;

		}

		case 42: {
			int searchID;
			std::cout << "Karsilastirmali arama icin ID girin: ";
			std::cin >> searchID;

			if (std::cin.fail()) {
				std::cin.clear(); std::cin.ignore(10000, '\n');
				std::cout << "Hata: Gecerli bir ID girin.\n";
				break;
			}
			std::cin.ignore();

			auto startL = std::chrono::high_resolution_clock::now();
			statehospital.searchById(searchID);
			auto endL = std::chrono::high_resolution_clock::now();
			double timeL = std::chrono::duration<double, std::milli>(endL - startL).count();
			performanceTracker.recordOperationTime(1, timeL);
			performanceTracker.addRecordAccess(searchID);

			filterTree.buildTree();
			auto startB = std::chrono::high_resolution_clock::now();
			filterTree.searchByIdInTree(searchID);
			auto endB = std::chrono::high_resolution_clock::now();
			double timeB = std::chrono::duration<double, std::milli>(endB - startB).count();
			performanceTracker.recordOperationTime(5, timeB);


			performanceTracker.recommendFastestStructure();
			break;
		}

		case 43: {
			performanceTracker.showExecutionTimes();
			break;
		}

		case 44: {
			performanceTracker.calculateAverageTimes();
			break;
		}

		case 45: {
			std::cout << "\n--- SISTEM KARAR DESTEK VE OPTIMIZASYON RAPORU ---\n";
			performanceTracker.recommendFastestStructure();
			break;
		}

		case 0: {
			std::cout << "IYI GUNLER\n";
			return 0;
		}

		default:
			std::cout << "gecirsiz secim\n";
			break;
		}



	} while (choise != 0);
	return 0;
}
