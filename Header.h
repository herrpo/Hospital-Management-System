#pragma once

// =====================================================
// GEREKLI KUTUPHANELER
// Sistem genelinde kullanilan standart kutuphaneler
// =====================================================

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm> 
#include <chrono>

// =====================================================
// MODUL 2: LOG DUGUMU
// Cift yonlu dairesel bagli listede kullanilan log kaydi
// =====================================================

struct lognode {
	int logID = 0;
	std::string type = "";
	int patientID = 0;
	std::string date = "";
	std::string oldValue;
	std::string newValue;
	time_t timestamp = 0;

	lognode* next = nullptr;
	lognode* prev = nullptr;
};

// =====================================================
// MODUL 2: OPERASYON GUNLUK SISTEMI
// Tum ekleme/silme/guncelleme islemlerini kaydeder
// =====================================================

class Operationlog {
private:
	lognode* head;
	int nextlogID;

public:
	Operationlog();
	~Operationlog();
	void addLog(std::string type, int PatientID, std::string OldValue, std::string NewValue);
	void listLogsByPatient(int TargetID);
	void listLogsByType(std::string type);
	void generalreport();
	void listLogsByDate(std::string targetdate);
	void listLogsByDateRange(int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear);
};

// =====================================================
// MODUL 1: ANA HASTA KAYIT VERISI
// Sistemdeki her hasta icin temel veri yapisi
// =====================================================


class patient {
public:
	int id = 0;
	std::string name = "";
	std::string catagory = "";
	double size = 0.0;
	std::string date = "";
	time_t timestamp = 0;
	std::string priority = "";
	std::string status = "";

	double rating = 0.0;
	int ratingCount = 0;
	std::string criticalNote = "";

	patient* next = nullptr;


};


// =====================================================
// MODUL 3: STACK DUGUMU
// Undo sistemi icin kullanilan stack elemani
// =====================================================

struct stacknode {
	std::string operationtype;
	patient oldata;
	stacknode* next = nullptr;
};

// =====================================================
// MODUL 3: UNDO STACK SISTEMI
// Yapilan islemleri geri almak icin kullanilir
// =====================================================


class undostack {
private:
	stacknode* top = nullptr;
	int depth = 0;
public:
	~undostack();
	void push(std::string type, patient data);
	patient pop(std::string& outoperationtype);
	void showlast10();
	void frequency();
	int getdepth() {
		return depth;
	}
	void clear();

};

// =====================================================
// MODUL 1: ANA KAYIT YONETIM SISTEMI
// Tum hasta kayitlarini bagli listede tutar
// =====================================================

class registration {
private:
	patient* head;
	Operationlog* logger;
	undostack* undoSystem;

public:
	registration(Operationlog* _logger, undostack* _undo);
	~registration();
	void addPatient(int id, std::string name, std::string catagory, double size, std::string priority, std::string status, double rating, bool fromQueue = false);
	void deleteById(int Targetid);
	void updateByName(std::string Targetname);
	void listByTimestamp();
	void searchById(int Targetid);
	void totalrecord();
	void sortBysize_SmallToLarge();
	void oldeset10records();
	void AddCriticalNote(int Targetid, std::string note);
	void showCritacalRecords();
	void undolastaction();
	void logQueueProcessing(int id);

	patient* getHead() {
		return head;
	}
};

// =====================================================
// MODUL 4: KUYRUK DUGUMU
// Bekleyen hasta taleplerini temsil eder
// =====================================================

struct requestNode {
	int requestID = 0;
	std::string name = "";
	std::string catagory = "";
	double size = 0.0;
	int priortiylevel = 0;
	time_t requesttime = 0;
	std::string date = "";

	requestNode* next = nullptr;
};

// =====================================================
// MODUL 4: TALEP KUYRUK SISTEMI
// Oncelikli dairesel kuyruk yapisi kullanir
// =====================================================

class requestQueue {
private:
	requestNode* front;
	requestNode* rear;
	registration* regestrationSystem;

public:
	requestQueue(registration* _reg);
	~requestQueue();

	void enqueueRequest(int id, std::string name, std::string Catagory, double Size, int PriortyLevel);
	void listQueue();
	void dequeueToRegisgtry(std::string defaultStatus);
	void CalculateAverageTime();
};

// =====================================================
// MODUL 5: TREE DUGUMU
// BST yapisinda kullanilan agac dugumu
// =====================================================

struct Treenode {
	patient data;
	Treenode* left = nullptr;
	Treenode* right = nullptr;
};

// =====================================================
// MODUL 5: TREE (BST) SISTEMI
// Hizli filtreleme ve binary search islemleri yapar
// =====================================================

class Treemodule {
private:
	Treenode* root;
	registration* regSystem;

	Treenode* insert(Treenode* node, patient data);
	void filterByDateHelper(Treenode* node, std::string targetyear);
	void printPriorityHelper(Treenode* node, std::string targetPriority);
	void filterByRatingHelper(Treenode* node, double minPuan, double maxPuan);
	void analyzeYear2000Helper(Treenode* node, int& before, int& after);
	Treenode* searchByIdHelper(Treenode* node, int targetId);
	int getHeightHelper(Treenode* node);
	void destroyTree(Treenode* node);



public:
	Treemodule(registration* _reg);
	~Treemodule();

	void buildTree();
	void filterByDate(std::string targetYear);
	void filterByRating(double minPuan, double maxPuan);
	void printByPriority();
	void showHeight();
	void analyzeYear2000();
	void searchByIdInTree(int targetId);


};

// =====================================================
// MODUL 6: HASH DUGUMU
// Zincirleme (chaining) icin kullanilan dugum
// =====================================================


struct Hashnode {
	patient data;
	Hashnode* next = nullptr;
};

// =====================================================
// MODUL 6: HASH ANALIZ SISTEMI
// O(1) hizinda arama ve analiz saglar
// =====================================================

class Hashmodule {
private:
	static const int Table_size = 100;
	Hashnode* table[Table_size];
	registration* regSystem;

	int collesionCounter;
	int filledCells;

	int hashFunction(int id);

public:
	Hashmodule(registration* _reg);
	~Hashmodule();

	void bulidTable();
	void findRatingById(int id);
	void countByCategory(std::string targetCategory);
	void priorityAnalysis();
	void showCollisions();
	void showLoadFactor();
};


// =====================================================
// MODUL 8: PERFORMANS ANALIZ SISTEMI
// Tum modullerin surelerini ve performansini takip eder
// =====================================================

class PerfomansAnaliz {
private:
	int* lastAccessed;
	int accesIndex;
	int accesCount;

	double moduleTimes[8];

public:
	PerfomansAnaliz();
	~PerfomansAnaliz();


	void addRecordAccess(int id);
	void listLastAccessed();
	void recordOperationTime(int moduleNo, double timeMs);
	void showPerformanceReport();
	void recommendFastestStructure();
	void showExecutionTimes();
	void calculateAverageTimes();

};

// =====================================================
// MODUL 7: HUFFMAN AGAC DUGUMU
// Huffman sikistirma algoritmasi icin kullanilir
// =====================================================


struct HuffmanNode {
	char ch;
	int freq;
	HuffmanNode* left = nullptr;
	HuffmanNode* right = nullptr;

	HuffmanNode(char c, int f) {
		ch = c;
		freq = f;
	}
};

// =====================================================
// MODUL 7: SHANNON-FANO KARAKTER FREKANSI
// Karakter ve frekans bilgisini tutar
// =====================================================


struct CharFreq {
	char ch;
	int freq;
};

// =====================================================
// MODUL 7: VERI SIKISTIRMA SISTEMI
// Huffman, LZW ve Shannon-Fano algoritmalarini uygular
// =====================================================

class Compressionmodule {
private:
	registration* regSystem;
	double originalSizeKB = 0.0;
	double huffmanSizeKB = 0.0;
	double lzwSizeKB = 0.0;
	double shannonSizeKB = 0.0;

	std::string getFullDataString();
	void getFrequencies(std::string data, int* freqArray);
	void getHuffmanCodes(HuffmanNode* root, std::string code, std::string* codesArray);
	void shannonFanoRecursive(CharFreq* freqList, int start, int end, std::string* codesArray, std::string currentCode);

public:
	Compressionmodule(registration* _reg);
	void frequencyAnalysis();
	void huffmanCompression(PerfomansAnaliz* perf);
	void lzwCompression(PerfomansAnaliz* perf);
	void shannonFanoCompression(PerfomansAnaliz* perf);
	void compressionReport();
};

// =====================================================
// ANA MENU FONKSIYONU
// Tum modullerin seceneklerini ekrana yazdirir
// =====================================================

void menu();