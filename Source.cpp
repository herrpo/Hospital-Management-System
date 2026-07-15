#include "Header.h"


// =====================================================
// ANA MENU - Tum modullerin seceneklerini listeler
// =====================================================
void menu() {

	std::cout << std::setw(75) << "*********************************************" << std::endl;
	std::cout << std::setw(75) << " * === HASTANE KAYIT VE YONETIM SISTEMI ==== *" << std::endl;
	std::cout << std::setw(75) << "*********************************************" << std::endl;

	std::cout << "--- MODUL 1: ANA KAYIT ---    --- MODUL 2: LOG SISTEMI ---\n";
	std::cout << "[1] Hasta Ekle                [11] Hastaya Gore Log Listele\n";
	std::cout << "[2] ID'ye Gore Sil            [12] Islem Turune Gore Listele\n";
	std::cout << "[3] Isme Gore Guncelle        [13] Belirli Tarihli Loglar\n";
	std::cout << "[4] Zaman Damgasi Listele     [14] Tarih Araligi Sorgula\n";
	std::cout << "[5] ID ile Ara                [15] Genel Log ve Kritik Rapor\n";
	std::cout << "[6] Toplam Kayit Sayisi       --- MODUL 3: STACK (UNDO) ---\n";
	std::cout << "[7] Boyuta Gore Sirala        [16] Son Islemi Geri Al (Undo)\n";
	std::cout << "[8] En Eski 10 Kayit          [17] Stack Derinligi Goster\n";
	std::cout << "[9] Kritik Not Ekle           [18] Son 10 Islem Gecmisi\n";
	std::cout << "[10] Kritik Kayitlari Listele [19] Islem Yogunluk Analizi\n";
	std::cout << "                              [20] Stack Gecmisini Temizle\n";

	std::cout << "\n--- MODUL 4: KUYRUK ---       --- MODUL 5: AGAC (TREE) ---\n";
	std::cout << "[21] Yeni Talep Ekle          [26] Agacta Tarih Filtrele\n";
	std::cout << "[22] ONCELIKLI Talep Ekle     [27] Agaci Oncelige Gore Listele\n";
	std::cout << "[23] Kuyrugu Listele          [28] Puan Araligi Filtrele\n";
	std::cout << "[24] Talebi Isleme Al (Deq)   [29] Agac Derinligi (Performans)\n";
	std::cout << "[25] Ortalama Bekleme Suresi  [30] 2000 Yili Trend Analizi\n";

	std::cout << "\n--- MODUL 6: HASH ---         --- MODUL 7: SIKISTIRMA ---\n";
	std::cout << "[31] Hash Tablosunu Olustur   [36] Frekans Analizi\n";
	std::cout << "[32] ID -> Ortalama Puan Bul  [37] Huffman\n";
	std::cout << "[33] Kategori Kayit Sayisi    [38] LZW\n";
	std::cout << "[34] Oncelik Yogunluk (Hash)  [39] Shannon-Fano\n";
	std::cout << "[35] Carpisma & Load Factor   [40] Tasarruf/Oran Raporu\n";

	std::cout << "\n--- MODUL 8: PERFORMANS ---\n";
	std::cout << "[41] Son 10 Erisilen Kayit\n";
	std::cout << "[42] Linear vs Binary Search Karsilastirmasi\n";
	std::cout << "[43] Modul Calisma Sureleri (ms)\n";
	std::cout << "[44] Ortalama Islem Suresi Hesapla\n";
	std::cout << "[45] En Hizli Yapi Onerisi\n";
	std::cout << "[0] CIKIS\n";

	std::cout << std::endl;
}

// =====================================================
// MODUL 2: OPERASYON GUNLUGU
// Cift Yonlu Dairesel Bagli Liste ile implementedir.
// Yapilan tum islemleri (ekle/sil/guncelle) kaydeder.
// =====================================================




// Operationlog nesnesini baslatir; log listesini bos ayarlar, log ID sayacini 1'den baslatir
Operationlog::Operationlog() {
	head = nullptr;
	nextlogID = 1;
}

// [M2-1] Gunluk kaydi ekle: Yeni islem logu olusturup dairesel cift bagli listeye ekler
// type: islem turu | PatientID: hasta ID | OldValue: eski deger | NewValue: yeni deger
void Operationlog::addLog(std::string type, int PatientID, std::string OldValue, std::string NewValue) {
	lognode* newNode = new lognode;
	newNode->logID = nextlogID++;
	newNode->type = type;
	newNode->patientID = PatientID;
	newNode->oldValue = OldValue;
	newNode->newValue = NewValue;

	time_t now = time(0);
	newNode->timestamp = now;
	newNode->date = std::string(ctime(&now));
	newNode->date.pop_back();

	if (head == nullptr) {
		head = newNode;
		head->next = head;
		head->prev = head;
	}
	else {
		lognode* last = head->prev;

		last->next = newNode;
		newNode->prev = last;
		newNode->next = head;
		head->prev = newNode;
	}
	std::cout << "Islem: " << type << " | Hasta ID: " << PatientID << " icin Guncellendi.\n";

}



// [M2-2] Belirli kayit ID'ye ait tum islemleri listele: Verilen hasta ID'sine ait tum loglari ekrana yazdirir
void Operationlog::listLogsByPatient(int TargetID) {
	if (head == nullptr) {
		std::cout << "Hata: sistemde gosterilecek log bulunmamaktadir.\n";
		return;
	}
	lognode* temp = head;
	bool found = false;
	std::cout << "\n========== ID:" << TargetID << " icin islem Gecmisi ==========\n";
	do {
		if (temp->patientID == TargetID) {
			std::cout << "[" << temp->date << "] Islem: " << temp->type << " | Eski: " << temp->oldValue << " | Yeni: " << temp->newValue << '\n';
			found = true;
		}
		temp = temp->next;
	} while (temp != head);

	if (!found)
		std::cout << "Hata: Belirtilmis oldugunuz hasta icin islem bulunmadi.\n";
}


// [M2-5] Islem turune gore listeleme: Verilen islem turune (orn. "[Ekle]") gore loglari filtreler
void Operationlog::listLogsByType(std::string actionType) {
	if (head == nullptr) {
		std::cout << "Hata: Sistemde gosterilecek log bulunmamaktadir.\n";
		return;
	}
	lognode* temp = head;
	bool found = false;
	std::cout << "\n========== Islem Turu: " << actionType << " Gecmisi ==========\n";
	do {
		if (temp->type.find(actionType) != std::string::npos) {
			std::cout << "[" << temp->date << "] ID: " << temp->patientID
				<< " | Eski: " << temp->oldValue << "| Yeni: " << temp->newValue << '\n';
			found = true;
		}
		temp = temp->next;
	} while (temp != head);

	if (!found)
		std::cout << "Hata: " << actionType << " islem bulunmadi.\n";
}


// [M2-4] Gunluk raporu olustur: Ekleme, silme, guncelleme ve kritik not islem sayilarini ekrana yazdirir
void Operationlog::generalreport() {
	if (head == nullptr) {
		std::cout << "Hata: Raporlanacak log bulunmamaktadir.\n";
		return;
	}
	int ekle = 0;
	int sil = 0;
	int guncelle = 0;
	int kritik = 0;
	int talep = 0;

	lognode* temp = head;
	do {
		if (temp->type == "[Ekle]" || temp->type == "[Undo-Sil]") {
			ekle++;
		}
		else if (temp->type == "[Sil]" || temp->type == "[Undo-Ekle]") {
			sil++;
		}
		else if (temp->type == "[Guncelle]" || temp->type == "[Undo-Guncelle]") {
			guncelle++;
		}
		else if (temp->type == "[Kritik Not]") {
			kritik++;
		}
		else if (temp->type == "[Talep Islendi]") {
			talep++;
		}
		temp = temp->next;

	} while (temp != head);

	std::cout << std::setw(75) << "* ======== GUNLUK ISLEM RAPORU =========   *" << std::endl;
	
	std::cout << "Toplam Ekleme Islemi: " << ekle << "\n";
	std::cout << "Toplam Silme Islemi: " << sil << "\n";
	std::cout << "Toplam Guncelleme Islemi: " << guncelle << "\n";
	std::cout << "Toplam Kritik Not Islemi: " << kritik << "\n";
	std::cout << "Sistemdeki Toplam Log Sayisi: " << (ekle + sil + guncelle + kritik + talep) << "\n";


}

// [M2-3] Belirli tarihli loglari listele: Verilen tarih dizgisiyle eslesen log kayitlarini bulur
void Operationlog::listLogsByDate(std::string targetdate) {
	if (head == nullptr) {
		std::cout << "Hata: Sistemde aranacak log bulunamamaktadi.\n";
		return;
	}

	lognode* temp = head;
	bool found = false;

	std::cout << "\n ========== TARIH ==========\n";

	do {
		if (temp->date.find(targetdate) != std::string::npos) {
			std::cout << "[" << temp->date << "] Islem: " << temp->type << "| ID: " << temp->patientID << '\n';
			found = true;
		}
		temp = temp->next;
	} while (temp != head);

	if (!found) {
		std::cout << "Hata: " << targetdate << " tarihine ait islem bulunamadi.\n";
	}
}


// [M2-3] Tarih araligi sorgula: Baslangic ve bitis tarihleri arasindaki loglari timestamp ile filtreler
void Operationlog::listLogsByDateRange(int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear) {
	if (head == nullptr) {
		std::cout << "Hata: Sistemde listelenecek log bulunmamaktadir.\n";
		return;
	}

	struct tm start_tm = { 0 };
	start_tm.tm_mday = startDay;
	start_tm.tm_mon = startMonth - 1;
	start_tm.tm_year = startYear - 1900;
	time_t startTime = mktime(&start_tm);

	struct tm end_tm = { 0 };
	end_tm.tm_mday = endDay;
	end_tm.tm_mon = endMonth - 1;
	end_tm.tm_year = endYear - 1900;
	end_tm.tm_hour = 23;
	end_tm.tm_min = 59;
	end_tm.tm_sec = 59;
	time_t endTime = mktime(&end_tm);

	lognode* temp = head;
	bool found = false;

	std::cout << "\n========== " << startDay << "/" << startMonth << "/" << startYear
		<< " - " << endDay << "/" << endMonth << "/" << endYear << " ARASI LOGLAR ==========\n";

	do {
		if (temp->timestamp >= startTime && temp->timestamp <= endTime) {
			std::cout << "[" << temp->date << "] Islem: " << temp->type
				<< " | ID: " << temp->patientID
				<< " | Detay: " << temp->oldValue << " -> " << temp->newValue << '\n';
			found = true;
		}
		temp = temp->next;
	} while (temp != head);

	if (!found) {
		std::cout << "Bilgi: Bu tarih araliginda hicbir islem bulunamadi.\n";
	}
	std::cout << "========================================================\n";
}


// =====================================================
// MODUL 1: ANA KAYIT YONETIMI
// Tek Yonlu Bagli Liste ile implemente edilmistir.
// Tum hasta verilerinin merkezi deposudur.
// =====================================================


// registration nesnesini baslatir; hasta listesini bos ayarlar, log ve undo referanslarini atar
registration::registration(Operationlog* _logger, undostack* _undo) {
	head = nullptr;
	logger = _logger;
	undoSystem = _undo;
}

// [M1-1] Kayit ekle: Yeni hasta olusturup listenin sonuna ekler; ID tekrarini kontrol eder
// Islem M2 log sistemine ve M3 undo stack'ine kaydedilir
void registration::addPatient(int id, std::string name, std::string catagory, double size, std::string priority, std::string status, double rating, bool fromQueue) {

	patient* check = head;
	while (check != nullptr) {
		if (check->id == id) {
			std::cout << "Hata: ID " << id << " sistemde kayitli!" << std::endl;
			return;
		}
		check = check->next;
	}


	patient* newPatient = new patient();
	newPatient->id = id;
	newPatient->name = name;
	newPatient->catagory = catagory;
	newPatient->size = size;
	newPatient->priority = priority;
	newPatient->status = status;

	if (rating > 0.0) {
		newPatient->rating = rating;
		newPatient->ratingCount = 1;
	}
	else {
		newPatient->rating = 0.0;
		newPatient->ratingCount = 0;
	}





	newPatient->next = nullptr;

	time_t now = time(0);
	newPatient->timestamp = now;
	newPatient->date = std::string(ctime(&now));
	newPatient->date.pop_back();



	if (head == nullptr) {
		head = newPatient;
	}

	else {
		patient* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newPatient;
	}
	std::cout << "Hasta: " << name << " | ID: " << id << " sisteme basarli bir sekilde kaydedildi." << std::endl;


	std::string newData = name + " " + catagory;
	logger->addLog("[Ekle]", id, "-", newData);
	undoSystem->push("[Ekle]", *newPatient);
}


// [M1-2] ID'ye gore sil: Verilen ID'li hastayi bulur ve listeden cikarir
// Silme oncesi hasta verisi M3 undo stack'ine, islem M2 log'a kaydedilir
void registration::deleteById(int Targetid) {
	if (head == nullptr) {
		std::cout << "Hata: Sistemde silinecek kayit bulunmamaktadir.\n";
		return;
	}


	if (head->id == Targetid) {
		patient* temp = head;
		std::string oldData = temp->name + " " + temp->catagory;

		undoSystem->push("[Sil]", *temp);

		head = head->next;
		logger->addLog("[Sil]", Targetid, oldData, "Silindi");

		delete temp;
		std::cout << "ID: " << Targetid << " silindi.\n";
		return;
	}

	patient* current = head;

	while (current->next != nullptr && current->next->id != Targetid) {
		current = current->next;
	}

	if (current->next == nullptr) {
		std::cout << "Hata: " << Targetid << " sistemde bulunamadi.\n";
		return;
	}

	patient* temp = current->next;

	std::string oldData = temp->name + " " + temp->catagory;
	undoSystem->push("[Sil]", *temp);

	current->next = temp->next;

	logger->addLog("[Sil]", Targetid, oldData, "Silindi");

	delete temp;
	std::cout << "ID: " << Targetid << " silindi.\n";
}

// [M1-3] Basliga gore guncelle: Isme gore hastayi bulur, yeni bilgileri kullanicidan alir
// Eski deger M3 undo stack'ine push edilir, degisiklik M2 log'a kaydedilir
void registration::updateByName(std::string Targetname) {
	if (head == nullptr) {
		std::cout << "Hata: Sistemde guncellenecek kayit bulunmamaktadir.\n";
		return;
	}

	patient* current = head;


	while (current != nullptr) {
		if (current->name == Targetname) {

			std::cout << "Hasta: " << Targetname << " bulundu. Yeni bilgileri giriniz:\n";
			undoSystem->push("[Guncelle]", *current);

			std::string oldData = current->catagory + " | Oncelik: " + current->priority + " | Ortalama Puan: " + std::to_string(current->rating);

			std::cout << "Yeni Kategori: ";
			std::getline(std::cin, current->catagory);

			std::cout << "Yeni Oncelik (Yuksek/Orta/Dusuk): ";
			std::getline(std::cin, current->priority);

			std::cout << "Yeni Durum(Aktif/Islemde/Arsiv): ";
			std::getline(std::cin, current->status);

			double newRating;
			std::cout << "Yeni Puan Ekle (Rating): ";
			std::cin >> newRating;
			std::cin.ignore();

			current->rating = ((current->rating * current->ratingCount) + newRating) / (current->ratingCount + 1);
			current->ratingCount++;

			std::string newData = current->catagory + " | Oncelik: " + current->priority + " | Ortalama Puan: " + std::to_string(current->rating);

			logger->addLog("[Guncelle]", current->id, oldData, newData);

			std::cout << "Kayit basari ile guncellendi.\n";

			return;
		}

		current = current->next;
	}

	std::cout << "Hata:" << Targetname << " isimli hasta bulunamadi.\n";
}

// [M1-4] Zaman damgasi ile listele: Listedeki tum hastalari ekle sirasina gore ekrana yazdirir
void registration::listByTimestamp() {
	if (head == nullptr) {
		std::cout << "Hata: Gosterilecek kayit bulunamamaktadir.\n";
		return;
	}

	patient* current = head;
	
	std::cout << std::setw(75) << "*  ======== HASTA KAYIT LISTESI ==========  *" << std::endl;
	
	while (current != nullptr) {
		std::cout << "ID: " << current->id
			<< " | Isim: " << current->name
			<< " | Kategori: " << current->catagory
			<< " | Durum: " << current->status
			<< " | Kayit Tarihi: " << current->date;
		current = current->next;
		std::cout << "\n--------------------------------------------------------------------------------------------------------\n";
	}

}

// [M1-5] ID'ye gore ara: Verilen ID'li hastanin tum detaylarini ekrana yazdirir
void registration::searchById(int Targetid) {
	if (head == nullptr) {
		std::cout << "Hata: Sistemde kayit bulunmamaktadir.\n";
		return;
	}
	patient* current = head;

	while (current != nullptr) {
		if (current->id == Targetid) {
			
			std::cout << std::setw(75) << "*   ======== HASTA BILGILERI ==========     *" << std::endl;
			
			std::cout << "ID: " << current->id << "\n";
			std::cout << "Isim: " << current->name << "\n";
			std::cout << "Kategori: " << current->catagory << "\n";
			std::cout << "Boyut: " << current->size << " MB\n";
			std::cout << "Oncelik (Yuksek/Orta/Dusuk): " << current->priority << "\n";
			std::cout << "Durum (Aktif/Islemde/Arsiv): " << current->status << "\n";
			std::cout << "Puan (Rating): " << current->rating << "\n";
			std::cout << "Kayit Tarihi: " << current->date << "\n";

			if (current->criticalNote != "") {
				std::cout << "KRITIK NOT: " << current->criticalNote << "\n";
			}

			return;
		}
		current = current->next;
	}
	std::cout << "Hata:" << Targetid << " ID numarali hasta bulunamadi.\n";

}


// [M1-6] Toplam kayit sayisi: Bagli listedeki toplam hasta sayisini sayar ve ekrana yazdirir
void registration::totalrecord() {
	int counter = 0;
	patient* temp = head;
	while (temp != nullptr) {
		temp = temp->next;
		counter++;
	}
	std::cout << "Toplam Kayit Sayisi:" << counter << std::endl;

}

// [M1-7] Boyuta gore kucukten buyuge sirala: Bubble sort ile hastalari dosya boyutuna gore siralar
// Siralama sonrasi bagli listenin head pointeri guncellenir
void registration::sortBysize_SmallToLarge() {
	if (head == nullptr) {
		std::cout << "Hata: Siralanacak kayit bulunmamaktadir.\n";
		return;
	}


	int count = 0;
	patient* temp = head;
	while (temp != nullptr) {
		count++;
		temp = temp->next;
	}

	patient** ptrArray = new patient * [count];
	temp = head;
	for (int i = 0; i < count; i++) {
		ptrArray[i] = temp;
		temp = temp->next;
	}


	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (ptrArray[j]->size > ptrArray[j + 1]->size) {
				patient* swapTemp = ptrArray[j];
				ptrArray[j] = ptrArray[j + 1];
				ptrArray[j + 1] = swapTemp;
			}
		}
	}

	head = ptrArray[0];
	for (int i = 0; i < count - 1; i++) {
		ptrArray[i]->next = ptrArray[i + 1];
	}
	ptrArray[count - 1]->next = nullptr;

	std::cout << "\n========== KAYITLAR BOYUTA GORE SIRALANDI (KUCUKTEN BUYUGE) ==========\n";
	for (int i = 0; i < count; i++) {
		std::cout << "Boyut: " << ptrArray[i]->size << " MB | ID: " << ptrArray[i]->id << " | Isim: " << ptrArray[i]->name << "\n";
	}

	delete[] ptrArray;
}

// [M1-8] En eski 10 kayit: Listenin basindaki en fazla 10 hastayi ekrana listeler
void registration::oldeset10records() {
	if (head == nullptr) {
		std::cout << "Hata: Sistemde kayit bulunmamaktadir.\n";
		return;
	}


	std::cout << std::setw(75) << " ========== EN ESKI 10 KAYIT ==========   " << std::endl;
	

	patient* temp = head;
	int counter = 0;

	while (temp != nullptr && counter < 10) {
		std::cout << "Tarih: " << temp->date << " | Hasta: " << temp->name << " | ID: " << temp->id << "\n";
		std::cout << "\n----------------------------------------------------------\n";
		temp = temp->next;
		counter++;
	}

}


// [M1-9] Kritik not ekle: Verilen ID'li hastaya kritik not ekler
// Eski durum M3 undo stack'ine kaydedilir, islem M2 log'a dusurulur
void registration::AddCriticalNote(int Targetid, std::string note) {
	if (head == nullptr) {
		std::cout << "Hata: Sistemde kayit bulunamamaktadir.\n";
		return;
	}

	patient* current = head;
	while (current != nullptr) {
		if (current->id == Targetid) {
			undoSystem->push("[Kritik Not]", *current);
			current->criticalNote = note;
			std::cout << "ID:" << Targetid << " olan hastaya kritik not eklendi.\n";
			std::string oldData = "";
			std::string newData = note;
			logger->addLog("[Kritik Not]", Targetid, oldData, newData);
			return;
		}
		current = current->next;
	}
	std::cout << "Hata: " << Targetid << " ID'li hasta bulunamadi.\n";
}


// [M1-10] Kritik kayitlari listele: criticalNote alani dolu olan tum hastalari ekrana yazdirir
void registration::showCritacalRecords() {
	if (head == nullptr) {
		std::cout << "Hata: Sistemde kritik notu olan hasta bulunamamaktadir.\n";
		return;
	}
	patient* current = head;
	bool found = false;
	
	std::cout << std::setw(75) << " ======== KRITIK DURUMDAKI HASTALAR ======= " << std::endl;
	


	while (current != nullptr) {
		if (current->criticalNote != "") {
			std::cout << "ID: " << current->id
				<< " | Isim: " << current->name
				<< " | NOT: " << current->criticalNote << "\n";
			std::cout << "\n-----------------------------------------\n";
			found = true;

		}
		current = current->next;
	}
	if (!found) {
		std::cout << "Kritik notu olan herhangi bir hasta bulunamadi.\n";
	}

}


// [M1 - M3 baglantisi] Son undo islemi: M3 stack'ten son islemi alarak M1 uzerinde geri uygular
// [Ekle] -> hasta silinir | [Sil] -> hasta geri eklenir | [Guncelle/Kritik Not] -> eski degerler yuklenir
void registration::undolastaction() {
	std::string lastOperation;
	patient oldState = undoSystem->pop(lastOperation);

	if (lastOperation == "YOK") {
		return;
	}

	if (lastOperation == "[Ekle]") {
		std::cout << "Geri Alma: [Ekle] islemi iptal ediliyor...\n";


		if (head != nullptr) {
			if (head->id == oldState.id) {
				patient* temp = head;
				head = head->next;
				delete temp;
			}
			else {
				patient* current = head;
				while (current->next != nullptr && current->next->id != oldState.id) {
					current = current->next;
				}
				if (current->next != nullptr) {
					patient* temp = current->next;
					current->next = temp->next;
					delete temp;
				}
			}

			logger->addLog("[Undo-Ekle]", oldState.id, "Eklendi", "Geri Alindi (Silindi)");
		}
	}

	else if (lastOperation == "[Sil]") {
		std::cout << "Geri Alma: [Sil] islemi iptal ediliyor...\n";


		patient* recoveredPatient = new patient();
		*recoveredPatient = oldState;
		recoveredPatient->next = nullptr;

		if (head == nullptr) {
			head = recoveredPatient;
		}
		else {
			patient* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = recoveredPatient;
		}

		logger->addLog("[Undo-Sil]", oldState.id, "Silindi", "Geri Alindi (Eklendi)");
	}

	else if (lastOperation == "[Guncelle]" || lastOperation == "[Kritik Not]") {
		patient* curr = head;
		while (curr != nullptr && curr->id != oldState.id) {
			curr = curr->next;
		}
		if (curr != nullptr) {
			curr->catagory = oldState.catagory;
			curr->priority = oldState.priority;
			curr->status = oldState.status;
			curr->criticalNote = oldState.criticalNote;
			curr->rating = oldState.rating;

			std::cout << "Geri Alma: Guncelleme islemi geri alindi, eski degerlere donuldu.\n";
			logger->addLog("[Undo-Guncelle]", oldState.id, "Guncel", "Eski Haline Dondu");
		}
	}
}


// [M1 - M4 baglantisi] Kuyruktan isleme alinan hasta icin M2 log sistemine kayit olusturur
void registration::logQueueProcessing(int id) {
	std::string oldData = "Kuyrukta Bekliyordu";
	std::string newData = "Ana Listeye Alindi";

	logger->addLog("[Talep Islendi]", id, oldData, newData);
}



// =====================================================
// MODUL 3: STACK MODULU (UNDO)
// LIFO yapisiyla yapilan degisiklikleri geri almak icin
// kullanilir. M1'deki her islem sonrasi push yapilir.
// =====================================================


// [M3-1] Islem push: Yapilan islemi (turu ve hasta verisini) stack tepesine ekler; derinligi arttirir
void undostack::push(std::string type, patient data) {
	stacknode* newNode = new stacknode;
	newNode->operationtype = type;
	newNode->oldata = data;
	newNode->next = top;
	top = newNode;
	depth++;
	std::cout << "Geri alma listesine eklendi: " << type << " | ID:" << data.id << '\n';

}

// [M3-2] Undo (pop): Stack tepesindeki islemi cikarir; islem turunu ve eski hasta verisini geri dondurur
// Stack bos ise outoperationtype = "YOK" olarak ayarlanir
patient undostack::pop(std::string& outoperationtype) {
	if (top == nullptr) {
		std::cout << "Hata: Geri alinacak islem bulunmamaktadir.\n";
		outoperationtype = "YOK";
		return patient();
	}

	stacknode* temp = top;
	patient recoverdData = temp->oldata;
	outoperationtype = temp->operationtype;
	top = top->next;
	delete temp;
	depth--;

	std::cout << "Son islem geri alindi.\n";

	return recoverdData;
}


// [M3-5] Islem yogunluk analizi: Stack'teki ekleme, silme ve guncelleme sayilarini hesaplar;
// en cok yapilan islemi ekrana yazdirir
void undostack::frequency() {
	if (top == nullptr) {
		std::cout << "Hata: Analiz icin veri bulunmamaktadir.\n";
		return;
	}

	int eklecounter = 0, silcounter = 0, guncelecounter = 0;
	stacknode* temp = top;

	while (temp != nullptr) {
		if (temp->operationtype == "[Ekle]") {
			eklecounter++;
		}
		else if (temp->operationtype == "[Sil]") {
			silcounter++;
		}
		else if (temp->operationtype == "[Guncelle]") {
			guncelecounter++;
		}
		temp = temp->next;
	}
	
	std::cout << std::setw(75) << "===== Islem Yogunlugu Analizi =====" << std::endl;
	
	std::cout << "Ekleme Sayisi: " << eklecounter << "\n";
	std::cout << "Silme Sayisi: " << silcounter << "\n";
	std::cout << "Guncelleme Sayisi: " << guncelecounter << "\n";

	if (eklecounter >= silcounter && eklecounter >= guncelecounter) {
		std::cout << "En cok yapilan islem: Ekleme\n";
	}
	else if (silcounter >= eklecounter && silcounter >= guncelecounter) {
		std::cout << "En cok yapilan islem: Silme\n";
	}
	else {
		std::cout << "En cok yapilan islem: Guncelleme\n";
	}
}

// [M3-4] Son 10 islemi goster: Stack tepesinden baslayarak en fazla 10 islem gecmisini listeler
void undostack::showlast10() {
	if (top == nullptr) {
		std::cout << "Hata: Geri alma gecmisi henuz bos.\n";
		return;
	}
	stacknode* temp = top;
	int counter = 0;

	
	std::cout << std::setw(75) << "    =====   SON 10 ISLEM GECMISI  ======   " << std::endl;
	

	while (temp != nullptr && counter < 10) {
		std::cout << "ISLEM: " << temp->operationtype << "| Hasta: " << temp->oldata.name << "ID:" << temp->oldata.id << std::endl;
		temp = temp->next;
		counter++;
	}
	std::cout << "Aktif Geri Alinabilir Islem Sayisi: " << depth << "\n";

}


// [M3 temizle] Stack gecmisini temizle: Tum stack elemanlarini siler ve bellegini serbest birakir
void undostack::clear() {
	while (top != nullptr) {
		stacknode* temp = top;
		top = top->next;
		delete temp;
	}
	depth = 0;
	std::cout << "Stack gecmisi temizlendi.\n";
}


// =====================================================
// MODUL 4: TALEP YONETIM MODULU (QUEUE)
// Dairesel oncelikli kuyruk yapisiyla implemente edilmistir.
// M4'ten eklenen kayitlar oncelik sirasina gore M1'e aktarilir.
// =====================================================


// requestQueue nesnesini baslatir; front/rear pointerleri bos ayarlar, kayit sistemine referans atar
requestQueue::requestQueue(registration* _reg) {
	front = nullptr;
	rear = nullptr;
	regestrationSystem = _reg;
}

// [M4-1/2] Yeni talep ekle / Oncelikli talep olustur: Talebi oncelik seviyesine gore dairesel kuyruga ekler
// Yuksek oncelik (3) -> one, dusuk oncelik (1) -> arkaya yerlestirilir
void requestQueue::enqueueRequest(int id, std::string Name, std::string Catagory, double Size, int PriortyLevel) {
	requestNode* newNode = new requestNode;
	newNode->requestID = id;
	newNode->name = Name;
	newNode->catagory = Catagory;
	newNode->size = Size;
	newNode->priortiylevel = PriortyLevel;
	time_t now = time(0);
	newNode->requesttime = now;
	newNode->date = std::string(ctime(&now));
	newNode->date.pop_back();


	if (front == nullptr) {
		front = newNode;
		rear = newNode;
		newNode->next = front;
	}
	// oncelik > front ise:
	else if (PriortyLevel > front->priortiylevel) {
		newNode->next = front;
		front = newNode;
		rear->next = front;
	}
	// herhangi bir yerde: 
	else {
		requestNode* temp = front;
		while (temp->next != front && temp->next->priortiylevel >= PriortyLevel) {
			temp = temp->next;
		}

		newNode->next = temp->next;
		temp->next = newNode;

		//en sona ekleniyorsa: 
		if (temp == rear) {
			rear = newNode;
			rear->next = front;
		}

	}

	std::string prioText;
	if (PriortyLevel == 3) {
		prioText = "Yuksek";
	}
	else if (PriortyLevel == 2) {
		prioText = "Orta";
	}
	else {
		prioText = "Dusuk";
	}


	std::cout << "Talep Eklendi: " << newNode->name << " | Oncelik: " << prioText << "\n";

}

// [M4-3] Kuyrugu listele: Bekleyen tum talepleri oncelik sirasina gore ekrana yazdirir
void requestQueue::listQueue() {
	if (front == nullptr) {
		std::cout << "Hata: Bekleyen herhangi bir hasta talebi bulunmamaktadir\n";
		return;
	}

	
	std::cout << std::setw(75) << " ======== BEKLEYEN HASTA TALEPLERI ======= " << std::endl;
	

	requestNode* temp = front;
	int position = 1;

	do {
		std::string prioritytext;
		if (temp->priortiylevel == 3) {
			prioritytext = "Yuksek";
		}
		else if (temp->priortiylevel == 2) {
			prioritytext = "Orta";
		}
		else {
			prioritytext = "Dusuk";
		}

		std::cout << position << ". Sira | ID:" << temp->requestID << " | Isim: " << temp->name << " | Oncelik: " << prioritytext << " | Katagori: " << temp->catagory << "\n";
		std::cout << "------------------------------------------------------------\n";

		temp = temp->next;
		position++;
	} while (temp != front);

	std::cout << "Toplam bekleyen Talep sayisi: " << position - 1 << std::endl;

}

// [M4-4] Ilk talebi isleme al (dequeue): Kuyrugun onundeki en oncelikli talebi alir ve M1'e kayit ekler
// Islem sonrasi M2 log kaydedilir; kuyruk tek elemanli ise front/rear sifirlaniir
void requestQueue::dequeueToRegisgtry(std::string defaultStatus) {

	if (front == nullptr) {
		std::cout << "Hata: Isleme alinacak bekleyen talep yok.\n";
		return;
	}

	requestNode* temp = front;

	std::string prioText;
	if (temp->priortiylevel == 3) {
		prioText = "Yuksek";
	}
	else if (temp->priortiylevel == 2) {
		prioText = "Orta";
	}
	else {
		prioText = "Dusuk";
	}

	std::cout << "\n--- siradaki Ilk Hasta Isleme Aliniyor ---\n";


	regestrationSystem->addPatient(temp->requestID, temp->name, temp->catagory, temp->size, prioText, defaultStatus, 0.0, true);
	regestrationSystem->logQueueProcessing(temp->requestID);

	if (front == rear) {

		front = nullptr;
		rear = nullptr;
	}
	else {

		front = front->next;
		rear->next = front;
	}

	delete temp;
}


// [M4-5] Ortalama bekleme suresi: Kuyrukdaki her talebin bekleme suresini hesaplar ve ortalamasini verir
// Sonuc M8 performans modulu icin kullanilabilir
void requestQueue::CalculateAverageTime() {
	if (front == nullptr) {
		std::cout << "HATA: Sirada bekleyen hasta olmadigi icin ortalama sure hesaplanamiyor.\n";
		return;
	}

	double totalseconds = 0.0;
	int count = 0;
	time_t currentTime = time(0);
	requestNode* temp = front;

	do {
		double waittime = difftime(currentTime, temp->requesttime);
		totalseconds += waittime;
		count++;
		temp = temp->next;
	} while (temp != front);

	double averageTime = totalseconds / count;

	
	std::cout << std::setw(75) << " ====== ORTALAMA BEKLEME SURESI ====== " << std::endl;
	
	std::cout << "Ortalama Bekleme Suresi: " << averageTime << " saniye.\n";
	std::cout << "------------------------------------------------------------\n";
}


// =====================================================
// MODUL 5: TREE (AKILLI FILTRELEME)
// Binary Search Tree (BST) yapisiyla implemente edilmistir.
// M1 verisini ID'ye gore agaca aktararak filtreleme saglar.
// =====================================================

// Treemodule nesnesini baslatir; agac kokunu bos ayarlar ve M1 kayit sistemine referans atar
Treemodule::Treemodule(registration* _reg) {
	root = nullptr;
	regSystem = _reg;
}

// BST'yi ozyinelemeli olarak tamamen siler; destructor ve buildTree tarafindan kullanilir
void Treemodule::destroyTree(Treenode* node) {
	if (node != nullptr) {
		destroyTree(node->left);
		destroyTree(node->right);
		delete node;
	}
}

// Hasta verisini ID'ye gore BST kurallarina uygun sekilde agaca ekler (yardimci fonksiyon)
Treenode* Treemodule::insert(Treenode* node, patient data) {
	if (node == nullptr) {
		Treenode* newNode = new Treenode;
		newNode->data = data;
		return newNode;
	}
	if (data.id < node->data.id) {
		node->left = insert(node->left, data);
	}
	else if (data.id > node->data.id) {
		node->right = insert(node->right, data);
	}

	return node;

}

// [M5 hazirlik] Agaci olustur: Mevcut agaci yikar, M1'deki tum hastalari BST'ye ekler
void Treemodule::buildTree() {
	destroyTree(root);
	root = nullptr;

	patient* temp = regSystem->getHead();

	if (temp == nullptr) {
		std::cout << "Hata: Sistemde agaca eklenecek kayit bulunamamaktadir.\n";
		return;
	}

	while (temp != nullptr) {
		root = insert(root, *temp);
		temp = temp->next;
	}
	std::cout << "Guncel hasta verileri basriyla agac yapisina aktarildi\n";
}

// Agaci inorder gezerek tarihinde hedef yil ifadesi gecen hastalari yazdirir (yardimci)
void Treemodule::filterByDateHelper(Treenode* node, std::string Targetyear) {
	if (node != nullptr) {
		filterByDateHelper(node->left, Targetyear);
		if (node->data.date.find(Targetyear) != std::string::npos) {
			std::cout << "ID:" << node->data.id << "| Isim: " << node->data.name << " | Tarih: " << node->data.date << std::endl;
		}
		filterByDateHelper(node->right, Targetyear);

	}
}

// [M5-1] Tarihe gore agac filtrele: Verilen yil ifadesine gore eslesen kayitlari listeler
void Treemodule::filterByDate(std::string Targetyear) {
	std::cout << "\n--- " << Targetyear << " --- Icin Kayitlar\n";
	filterByDateHelper(root, Targetyear);
}

// Agaci inorder gezerek belirtilen oncelik degerindeki hastalari yazdirir (yardimci)
void Treemodule::printPriorityHelper(Treenode* node, std::string targetPriority) {
	if (node != nullptr) {
		printPriorityHelper(node->left, targetPriority);
		if (node->data.priority == targetPriority) {
			std::cout << "Oncelik: " << node->data.priority << " | ID: " << node->data.id << " | Isim: " << node->data.name << std::endl;
		}
		printPriorityHelper(node->right, targetPriority);

	}
}

// [M5-2] Oncelige gore agac listele: Yuksek -> Orta -> Dusuk siralamasiyla kayitlari yazdirir
void Treemodule::printByPriority() {
	std::cout << "\n--- ONCELIGE GORE AGAC LISTESI ---\n";
	printPriorityHelper(root, "Yuksek");
	printPriorityHelper(root, "Orta");
	printPriorityHelper(root, "Dusuk");
}


// Agaci inorder gezerek puani verilen aralikta olan hastalari yazdirir (yardimci)
void Treemodule::filterByRatingHelper(Treenode* node, double minP, double maxP) {
	if (node != nullptr) {
		filterByRatingHelper(node->left, minP, maxP);
		if (node->data.rating >= minP && node->data.rating <= maxP) {
			std::cout << "Puan: " << node->data.rating << " | ID: " << node->data.id << " | Isim: " << node->data.name << "\n";
		}
		filterByRatingHelper(node->right, minP, maxP);
	}
}

// [M5-3] Puan araligi filtrele: Verilen min-max puan araligindaki hastalari agactan bulur ve listeler
void Treemodule::filterByRating(double minPuan, double maxPuan) {
	std::cout << "\n--- Puan Araligi: " << minPuan << " - " << maxPuan << std::endl;
	filterByRatingHelper(root, minPuan, maxPuan);

}

// Agacin yuksekligini ozyinelemeli hesaplar (yardimci); M8 performans karsilastirmasi icin kullanilir
int Treemodule::getHeightHelper(Treenode* node) {
	if (node == nullptr) {
		return 0;

	}
	int leftHeight = getHeightHelper(node->left);
	int rightHeight = getHeightHelper(node->right);
	return std::max(leftHeight, rightHeight) + 1;
}

// [M5-4] Agac derinligi (performans): Agacin toplam yuksekligini hesaplar ve ekrana yazdirir
void Treemodule::showHeight() {
	int height = getHeightHelper(root);
	std::cout << "\nAgacin Derinligi: " << height << "\n";

}

// Agaci inorder gezerek her kaydın yilini belirler; 2000 oncesi/sonrasi sayar (yardimci)
void Treemodule::analyzeYear2000Helper(Treenode* node, int& before, int& after) {
	if (node != nullptr) {
		analyzeYear2000Helper(node->left, before, after);

		time_t ts = node->data.timestamp;
		struct tm* t = localtime(&ts);
		int year = t->tm_year + 1900;

		if (year < 2000) {
			before++;
		}
		else {
			after++;
		}

		analyzeYear2000Helper(node->right, before, after);
	}
}

// [M5-5] 2000 yili trend analizi: 2000 oncesi ve sonrasi kayit sayilarini karsilastirarak raporlar
void Treemodule::analyzeYear2000() {
	int oncesi = 0, sonrasi = 0;
	analyzeYear2000Helper(root, oncesi, sonrasi);
	std::cout << "\n--- 2000 YILI TREND ANALIZI ---\n";
	std::cout << "2000 Yilindan Onceki Kayit Sayisi: " << oncesi << "\n";
	std::cout << "2000 Yili ve Sonrasi Kayit Sayisi: " << sonrasi << "\n";
}

// BST'de ID'yi ozyinelemeli binary search ile arar; bulunan dugumu dondurur (yardimci)
Treenode* Treemodule::searchByIdHelper(Treenode* node, int targetId) {
	if (node == nullptr) {
		return nullptr;
	}


	if (node->data.id == targetId) {
		return node;
	}

	if (targetId < node->data.id) {
		return searchByIdHelper(node->left, targetId);
	}
	else {
		return searchByIdHelper(node->right, targetId);
	}
}

// [M5 - M8 baglantisi] Agacta ID ara: Binary search ile ID'yi agacta bulur ve sonucu yazdirir
void Treemodule::searchByIdInTree(int targetId) {
	Treenode* result = searchByIdHelper(root, targetId);
	if (result != nullptr) {
		std::cout << "Agacta Bulundu -> ID: " << result->data.id
			<< " | Isim: " << result->data.name << "\n";
	}
	else {
		std::cout << "Agacta bulunamadi: " << targetId << "\n";
	}
}

// =====================================================
// MODUL 6: HASH ANALIZ MOTORU
// Chaining (zincirleme) yontemiyle implemente edilmistir.
// ID, kategori ve oncelik bazli O(1) hizinda sorgulama saglar.
// =====================================================

// Hashmodule nesnesini baslatir; tum tablo hucrelerini nullptr yapar, sayaclari sifirlar
Hashmodule::Hashmodule(registration* _reg) {
	regSystem = _reg;
	collesionCounter = 0;
	filledCells = 0;

	for (int i = 0; i < Table_size; i++) {
		table[i] = nullptr;
	}
}

// Hash fonksiyonu: Hasta ID'sini tablo boyutuna bolumunden kalanla indekse donusturur
int Hashmodule::hashFunction(int id) {
	return id % Table_size;
}

// [M6-1 hazirlik] Hash tablosunu olustur: Mevcut tabloyu temizler ve M1 verilerini yeniden ekler
// Carpisme (collision) sayisini ve dolu hucre sayisini gunceller
void Hashmodule::bulidTable() {
	for (int i = 0; i < Table_size; i++) {
		Hashnode* current = table[i];
		while (current != nullptr) {
			Hashnode* temp = current;
			current = current->next;
			delete temp;
		}
		table[i] = nullptr;
	}
	collesionCounter = 0;
	filledCells = 0;

	patient* temp = regSystem->getHead();

	if (temp == nullptr) {
		std::cout << "Hata: Sistemde Hash tablosuna aktarilacak kayit bulunamadi.\n";
		return;
	}

	while (temp != nullptr) {
		int index = hashFunction(temp->id);

		Hashnode* newNode = new Hashnode;
		newNode->data = *temp;
		newNode->next = nullptr;


		if (table[index] == nullptr) {
			table[index] = newNode;
			filledCells++;
		}
		else {
			collesionCounter++;

			Hashnode* current = table[index];
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newNode;
		}
		temp = temp->next;
	}
	std::cout << "Guncel Veriler Hash tablosona islendi.\n";
}

// [M6-1] ID -> Ortalama puan bul: Hash fonksiyonuyla indekse gider, o ID'nin puanini O(1) hizinda dondurur
void Hashmodule::findRatingById(int targetId) {
	int index = hashFunction(targetId);
	Hashnode* current = table[index];

	while (current != nullptr) {
		if (current->data.id == targetId) {
			std::cout << "ID: " << targetId << " olan hastanin ortalama puan: " << current->data.rating << std::endl;
			return;
		}
		current = current->next;
	}
	std::cout << "Hata: " << targetId << " ID numarali hasta bulunamadi!\n";
}

// [M6-2] Kategori -> kayit sayisi: Tum tabloyu gezerek belirtilen kategoriye ait kayit sayisini bulur
void Hashmodule::countByCategory(std::string targetCategory) {
	int count = 0;

	for (int i = 0; i < Table_size; i++) {
		Hashnode* current = table[i];
		while (current != nullptr) {
			if (current->data.catagory == targetCategory) {
				count++;
			}
			current = current->next;
		}
	}
	std::cout << targetCategory << " katagorisine ait toplam kayit sayis: " << count << "\n";
}

// [M6-3] Oncelik yogunluk analizi: Yuksek, Orta ve Dusuk oncelikli hasta sayilarini hesaplar
void Hashmodule::priorityAnalysis() {
	int heigh = 0;
	int medium = 0;
	int low = 0;

	for (int i = 0; i < Table_size; i++) {
		Hashnode* current = table[i];
		while (current != nullptr) {
			if (current->data.priority == "Yuksek" || current->data.priority == "yuksek" || current->data.priority == "3") {
				heigh++;
			}

			else if (current->data.priority == "Orta" || current->data.priority == "orta" || current->data.priority == "2") {
				medium++;
			}

			else {
				low++;
			}

			current = current->next;

		}
	}
	std::cout << "\n--- ONCELIK YOGUNLUK ANALIZI ---\n";
	std::cout << "Yuksek Oncelikli Kayit Sayisi : " << heigh << "\n";
	std::cout << "Orta Oncelikli Kayit Sayisi   : " << medium << "\n";
	std::cout << "Dusuk Oncelikli Kayit Sayisi  : " << low << "\n";

}

// [M6-4] Carpisme sayisi: Hash tablosunda yasanan toplam collision sayisini ekrana yazdirir
void Hashmodule::showCollisions() {
	std::cout << "Tabloda yasanan toplam carpisma (Collision) sayisi: " << collesionCounter << "\n";
}


// [M6-5] Load factor (doluluk orani): (dolu hucre / toplam hucre) oranini hesaplar
// Oran > %75 ise performans uyarisi verir
void Hashmodule::showLoadFactor() {
	double loadfactor = (double)filledCells / Table_size;

	std::cout << "\n--- HASH TABLOSU YOGUNLUK OLCUMU (LOAD FACTOR) ---\n";
	std::cout << "Toplam Hucre Sayisi : " << Table_size << "\n";
	std::cout << "Dolu Hucre Sayisi   : " << filledCells << "\n";
	std::cout << "Doluluk Orani (Load Factor) : " << loadfactor << " (Yuzde " << loadfactor * 100 << ")\n";


	if (loadfactor > 0.75) {
		std::cout << "Uyari: Tablo cok dolu ( > %75), Perfotmans kaybi yasanabilir\n";
	}

	else {
		std::cout << "Tablo doluluk orani ideal seviyede.\n";
	}
}

// =====================================================
// MODUL 7: VERI SIKISTIRMA
// Huffman, LZW ve Shannon-Fano algoritmalarini uygular.
// M1 verisini ham metin olarak alir ve sikistirilmis boyutlari karsilastirir.
// =====================================================


// Compressionmodule nesnesini baslatir; tum boyut degerlerini sifirlar, M1'e referans atar
Compressionmodule::Compressionmodule(registration* _reg) {
	regSystem = _reg;
	originalSizeKB = 0;
	huffmanSizeKB = 0;
	lzwSizeKB = 0;
	shannonSizeKB = 0;
}

// M1'deki tum hastalarin metin alanlarini birlestirerek tek bir ham veri dizgisi olusturur
// Kayit yoksa "ornek veri yok" dondurur
std::string Compressionmodule::getFullDataString() {
	std::string fulldata = "";
	patient* temp = regSystem->getHead();
	while (temp != nullptr) {
		fulldata += temp->name + temp->catagory + temp->status + temp->criticalNote;
		temp = temp->next;
	}

	if (fulldata.empty()) {
		return "ornek veri yok";
	}
	else {
		return fulldata;
	}
}


// Her karakterin kac kez gectigi frekansini hesaplar ve 256 elemanli diziye kaydeder
void Compressionmodule::getFrequencies(std::string data, int* frequencyArray) {
	for (int i = 0; i < 256; i++) {
		frequencyArray[i] = 0;
	}

	for (int i = 0; i < data.length(); i++) {
		frequencyArray[(unsigned char)data[i]]++;
	}
}

// Huffman agacini ozyinelemeli gezerek her karakter icin binary kod dizgisi olusturur (yardimci)
void Compressionmodule::getHuffmanCodes(HuffmanNode* root, std::string code, std::string* codesArray) {
	if (root == nullptr) {
		return;
	}
	if (root->ch != '\0') {
		codesArray[(unsigned char)root->ch] = code;
	}
	getHuffmanCodes(root->left, code + "0", codesArray);
	getHuffmanCodes(root->right, code + "1", codesArray);
}

// Shannon-Fano algoritmasini ozyinelemeli uygular; frekans listesini ikiye bolarak kod olusturur (yardimci)
void Compressionmodule::shannonFanoRecursive(CharFreq* freqList, int start, int end, std::string* codesArray, std::string currentCode) {
	if (start == end) {
		codesArray[(unsigned char)freqList[start].ch] = currentCode;
		return;
	}

	int totalFreq = 0;
	for (int i = start; i <= end; i++) {
		totalFreq += freqList[i].freq;
	}

	int sum = 0, splitIndex = start;
	int minDiffrence = totalFreq;

	for (int i = start; i < end; i++) {
		sum += freqList[i].freq;


		int diffrence = totalFreq - 2 * sum;
		if (diffrence < 0) diffrence = -diffrence;

		if (diffrence < minDiffrence) {
			minDiffrence = diffrence;
			splitIndex = i;
		}
	}
	shannonFanoRecursive(freqList, start, splitIndex, codesArray, currentCode + "0");
	shannonFanoRecursive(freqList, splitIndex + 1, end, codesArray, currentCode + "1");
}

// [M7-1] Frekans analizi: Veri tekrarlarini hesaplar; hangi karakterler daha cok gectigi ekrana yazdirilir
void Compressionmodule::frequencyAnalysis() {
	std::string data = getFullDataString();
	if (data == "ornek veri yok") {
		std::cout << "Analiz edilecek veri bulunamadi.\n";
		return;
	}

	int freqs[256];
	getFrequencies(data, freqs);

	std::cout << "\n--- FREKANS ANALIZI (M7) ---\n";
	for (int i = 0; i < 256; i++) {
		if (freqs[i] > 0) {
			std::cout << "'" << (char)i << "': " << freqs[i] << " kez\n";
		}
	}
	originalSizeKB = data.length() / 1024.0;
	std::cout << "Orijinal Boyut: " << (originalSizeKB * 1024.0) << " Byte\n";
}

// Huffman agacini ozyinelemeli siler; bellek sizintisini onler
void deleteHuffmanTree(HuffmanNode* node) {
	if (!node) return;
	deleteHuffmanTree(node->left);
	deleteHuffmanTree(node->right);
	delete node;
}

// [M7-2] Huffman sikistirma: Karakterlere frekanslarina gore degisken uzunluklu kodlar atar
// Tahmini sikistirilmis boyutu huffmanSizeKB'ya kaydeder; islem suresini M8'e raporlar
void Compressionmodule::huffmanCompression(PerfomansAnaliz* perf) {
	auto start = std::chrono::high_resolution_clock::now();
	std::string data = getFullDataString();
	if (data == "ornek veri yok") {
		return;
	}
	int freqs[256];
	getFrequencies(data, freqs);

	HuffmanNode* nodes[256] = { nullptr };
	int nodeCount = 0;

	for (int i = 0; i < 256; i++) {
		if (freqs[i] > 0) {
			nodes[nodeCount++] = new HuffmanNode((char)i, freqs[i]);
		}
	}

	if (nodeCount == 0) {
		std::cout << "Sikistirilacak yeterli veri yok.\n";
		return;
	}


	while (nodeCount > 1) {

		for (int i = 0; i < nodeCount - 1; i++) {
			for (int j = 0; j < nodeCount - i - 1; j++) {
				if (nodes[j]->freq < nodes[j + 1]->freq) {
					HuffmanNode* temp = nodes[j];
					nodes[j] = nodes[j + 1];
					nodes[j + 1] = temp;
				}
			}
		}
		HuffmanNode* right = nodes[nodeCount - 1];
		HuffmanNode* left = nodes[nodeCount - 2];

		HuffmanNode* top = new HuffmanNode('\0', left->freq + right->freq);
		top->left = left;
		top->right = right;

		nodes[nodeCount - 2] = top;
		nodeCount--;
	}

	std::string huffmanCodes[256];
	getHuffmanCodes(nodes[0], "", huffmanCodes);

	double bits = 0;
	for (int i = 0; i < data.length(); i++) {
		bits += huffmanCodes[(unsigned char)data[i]].length();
	}
	huffmanSizeKB = (bits / 8.0) / 1024.0;

	auto end = std::chrono::high_resolution_clock::now();
	perf->recordOperationTime(7, std::chrono::duration<double, std::milli>(end - start).count());
	deleteHuffmanTree(nodes[0]);
	std::cout << "Huffman Sikistirmasi Tamamlandi.\n";
}

// [M7-4] Shannon-Fano sikistirma: Frekanslara gore ozyinelemeli bolme ile kodlar olusturur
// Tahmini boyutu shannonSizeKB'ya kaydeder; islem suresini M8'e raporlar
void Compressionmodule::shannonFanoCompression(PerfomansAnaliz* perf) {
	auto start = std::chrono::high_resolution_clock::now();
	std::string data = getFullDataString();
	if (data == "ornek veri yok") {
		return;
	}

	int freqs[256];
	getFrequencies(data, freqs);

	int uniqueCount = 0;
	for (int i = 0; i < 256; i++) if (freqs[i] > 0) uniqueCount++;

	CharFreq* freqList = new CharFreq[uniqueCount];
	int idx = 0;
	for (int i = 0; i < 256; i++) {
		if (freqs[i] > 0) {
			freqList[idx].ch = (char)i;
			freqList[idx].freq = freqs[i];
			idx++;
		}
	}


	for (int i = 0; i < uniqueCount - 1; i++) {
		for (int j = 0; j < uniqueCount - i - 1; j++) {
			if (freqList[j].freq < freqList[j + 1].freq) {
				CharFreq temp = freqList[j];
				freqList[j] = freqList[j + 1];
				freqList[j + 1] = temp;
			}
		}
	}

	std::string codes[256];
	shannonFanoRecursive(freqList, 0, uniqueCount - 1, codes, "");
	delete[] freqList;

	double totalBits = 0;
	for (int i = 0; i < data.length(); i++) {
		totalBits += codes[(unsigned char)data[i]].length();
	}
	shannonSizeKB = (totalBits / 8.0) / 1024.0;

	auto end = std::chrono::high_resolution_clock::now();
	perf->recordOperationTime(7, std::chrono::duration<double, std::milli>(end - start).count());
	std::cout << "Shannon-Fano Tamamlandi.\n";
}

// [M7-3] LZW sikistirma: Dinamik sozluk olusturarak tekrar eden dizileri index'e donusturur
// Tahmini boyutu lzwSizeKB'ya kaydeder; islem suresini M8'e raporlar
void Compressionmodule::lzwCompression(PerfomansAnaliz* perf) {
	auto start = std::chrono::high_resolution_clock::now();
	std::string data = getFullDataString();
	if (data == "ornek veri yok") {
		return;
	}


	std::string* dictionary = new std::string[4096];
	int dictSize = 256;


	for (int i = 0; i < 256; i++) {
		dictionary[i] = std::string(1, (char)i);
	}

	std::string p = "";
	p += data[0];
	int outputIdx = 0;
	int* output = new int[10000];

	for (int i = 1; i < (int)data.length(); i++) {
		char c = data[i];
		std::string pc = p + c;


		int foundIndex = -1;
		for (int j = 0; j < dictSize; j++) {
			if (dictionary[j] == pc) {
				foundIndex = j;
				break;
			}
		}

		if (foundIndex != -1) {
			p = pc;
		}
		else {

			for (int j = 0; j < dictSize; j++) {
				if (dictionary[j] == p) {
					output[outputIdx++] = j;
					break;
				}
			}

			if (dictSize < 4096) {
				dictionary[dictSize++] = pc;
			}
			p = std::string(1, c);
		}
	}


	for (int j = 0; j < dictSize; j++) {
		if (dictionary[j] == p) {
			output[outputIdx++] = j;
			break;
		}
	}


	lzwSizeKB = (outputIdx * 12.0 / 8.0) / 1024.0;

	auto end = std::chrono::high_resolution_clock::now();
	perf->recordOperationTime(7, std::chrono::duration<double, std::milli>(end - start).count());


    delete[] dictionary; 
    delete[] output; 


	std::cout << "LZW Sikistirmasi Tamamlandi.\n";
}


// [M7-5] Sikistirma oran raporu: Orijinal veri boyutunu ve 3 algoritmanin kazanc yuzdesini karsilastirir
void Compressionmodule::compressionReport() {
	std::cout << "\n--- MODUL 7: SIKISTIRMA ANALIZ RAPORU ---\n";
	std::cout << "------------------------------------------\n";
	std::string data = getFullDataString();
	if (data != "ornek veri yok") {
		originalSizeKB = data.length() / 1024.0;
	}
	std::cout << "Orijinal Veri Boyutu : " << (originalSizeKB * 1024.0) << " Byte\n";

	if (originalSizeKB > 0) {
		std::cout << "Huffman Boyutu       : " << (huffmanSizeKB * 1024.0) << " Byte (Kazanc: %" << (1.0 - huffmanSizeKB / originalSizeKB) * 100 << ")\n";
		std::cout << "LZW Boyutu           : " << (lzwSizeKB * 1024.0) << " Byte (Kazanc: %" << (1.0 - lzwSizeKB / originalSizeKB) * 100 << ")\n";
		std::cout << "Shannon-Fano Boyutu  : " << (shannonSizeKB * 1024.0) << " Byte (Kazanc: %" << (1.0 - shannonSizeKB / originalSizeKB) * 100 << ")\n";
	}
	else {
		std::cout << "Veri olmadigi icin oran hesaplanamadi.\n";
	}
	std::cout << "------------------------------------------\n";
}


// =====================================================
// MODUL 8: PERFORMANS & DIZI ANALIZI
// Tum modullerin calisma surelerini olcer ve karsilastirir.
// Dizi yapisiyla son erisim kayitlarini tutar.
// =====================================================


// PerfomansAnaliz nesnesini baslatir; 10'luk erisim dizisini ve modul surelerini sifirlar
PerfomansAnaliz::PerfomansAnaliz() {
	lastAccessed = new int[10];
	accesIndex = 0;
	accesCount = 0;

	for (int i = 0; i < 8; i++) {
		moduleTimes[i] = 0.0;
	}

}

// [M8-1] Son erisilen kayit kaydet: ID'yi dairesel 10'luk tampona ekler; tampon doluysa eskiyi yazar
void PerfomansAnaliz::addRecordAccess(int id) {
	lastAccessed[accesIndex] = id;
	accesIndex = (accesIndex + 1) % 10;
	if (accesCount < 10) {
		accesCount++;

	}
}


// [M8-1] Son 10 erisilen kayit listele: Dairesel tampondaki ID'leri kayit sirasina gore yazdirir
void PerfomansAnaliz::listLastAccessed() {
	std::cout << "\n --- SON ERISILEN 10 KAYIT ---\n";
	if (accesCount == 0) {
		std::cout << "Hata: Hic bir kayda erisilmedi.\n";
		return;
	}

	for (int i = 0; i < accesCount; i++) {
		int realIndex = (accesIndex - accesCount + i + 10) % 10;
		std::cout << i + 1 << ". Erisim -> Hasta ID: " << lastAccessed[realIndex] << std::endl;
	}
}


// [M8-3] Modul islem suresi kaydet: Belirtilen modul numarasinin toplam suresine timeMs ekler
void PerfomansAnaliz::recordOperationTime(int moduleNo, double timeMs) {
	if (moduleNo >= 1 && moduleNo <= 8) {
		moduleTimes[moduleNo - 1] += timeMs;
	}
}

void PerfomansAnaliz::showPerformanceReport() {
	std::cout << "\n === SISTEM PERFORMANS RAPORU ===\n";
	for (int i = 1; i <= 7; i++) {
		std::cout << "Modul " << i << " Toplam islem Suresi: " << moduleTimes[i - 1] << "ms\n";
	}
	std::cout << "--------------------------\n";
	recommendFastestStructure();
}

// [M8-5] En hizli yapi onerisi: Linear Search vs Binary Search ve Hash vs Agac karsilastirir
// M8 modul sureleri kullanilarak hangi veri yapisinin daha verimli oldugu raporlanir
void PerfomansAnaliz::recommendFastestStructure() {
	std::cout << "\n--- Sistem Optimizasyon Onerisi ---\n";


	std::cout << "[Linear Search vs Binary Search Analizi]\n";


	if (moduleTimes[0] > 0 && moduleTimes[4] > 0) {
		std::cout << "Bagli Liste (Linear Search - O(N)) Arama Suresi : " << moduleTimes[0] << " ms\n";
		std::cout << "Agac Yapisi (Binary Search - O(log N)) Arama Suresi: " << moduleTimes[4] << " ms\n";

		if (moduleTimes[4] < moduleTimes[0]) {
			std::cout << ">> SONUC: Binary Search (Agac) daha hizli sonuc verdi!\n";
		}
		else {
			std::cout << ">> SONUC: Su an veri seti kucuk oldugu icin Linear Search hizli gorunebilir, ancak kayit sayisi arttikca Binary Search kesinlikle daha performansli olacaktir.\n";
		}
	}
	else {
		std::cout << "Karsilastirma yapabilmek icin lutfen once [4] ile normal arama ve [24] veya [26] ile agacta arama yapiniz.\n";
	}

	std::cout << "\n[Agac (Tree) vs Hash Tablosu Karsilastirmasi]\n";


	if (moduleTimes[5] > 0 && moduleTimes[4] > 0) {
		if (moduleTimes[5] < moduleTimes[4]) {
			std::cout << ">> Oneri: Hash Tablosu (Modul 6) Agactan daha hizli. Nokta atisi aramalar (O(1)) icin Hash tercih edilmeli.\n";
		}
		else {
			std::cout << ">> Oneri: Agac yapisi (Modul 5) daha hizli veya Hash tablosunda cok fazla collision (carpisma) var.\n";
		}
	}
	else {
		std::cout << "Hash vs Agac karsilastirmasi icin lutfen Modul 6'da (Secim 30) islem yapiniz.\n";
	}
}

// [M8-3] Modul calisma sureleri: Her modul icin toplam islem suresini ms cinsinden listeler
void PerfomansAnaliz::showExecutionTimes() {
	std::cout << "\n--- Modul Bazli Islem Sureleri (ms) ---\n";
	for (int i = 0; i < 8; i++) {
		std::cout << "Modul " << i + 1 << ": " << moduleTimes[i] << " ms\n";
	}
}


// [M8-4] Ortalama islem suresi: Tum modullerin toplam suresinin ortalamasini hesaplar
void PerfomansAnaliz::calculateAverageTimes() {
	double total = 0;
	for (int i = 0; i < 8; i++) total += moduleTimes[i];
	std::cout << "Sistem Ortalama Islem Suresi: " << total / 8.0 << " ms\n";
}


// =====================================================
// DESTRUCTOR'LAR - Bellek Yonetimi
// Her nesne yikildığında dinamik belleği serbest bırakır
// =====================================================


// M2 yikicisi: Dairesel log listesindeki tum dugum bellegini serbest birakir
Operationlog::~Operationlog() {
	if (!head) {
		return;

	}
	lognode* current = head->next;
	while (current != head) {
		lognode* temp = current;
		current = current->next;
		delete temp;
	}
	delete head;
	head = nullptr;
}

// M1 yikicisi: Bagli listedeki tum hasta bellegini serbest birakir
registration::~registration() {
	patient* current = head;
	while (current != nullptr) {
		patient* temp = current;
		current = current->next;
		delete temp;
	}
	head = nullptr;
}


// M4 yikicisi: Dairesel kuyrukdaki tum talep dugum bellegini serbest birakir
requestQueue::~requestQueue() {
	if (front == nullptr) {
		return;
	}

	requestNode* current = front;
	do {
		requestNode* temp = current;
		current = current->next;
		delete temp;
	} while (current != front);

	front = rear = nullptr;
}


// M3 yikicisi: Stack'teki tum dugum bellegini serbest birakir
undostack::~undostack() {
	while (top != nullptr) {
		stacknode* temp = top;
		top = top->next;
		delete temp;
	}
}

// M5 yikicisi: BST'nin tum dugum bellegini ozyinelemeli olarak serbest birakir
Treemodule::~Treemodule() {
	destroyTree(root);
}


// M6 yikicisi: Hash tablosundaki tum zincir dugum bellegini serbest birakir
Hashmodule::~Hashmodule() {
	for (int i = 0; i < Table_size; i++) {
		Hashnode* current = table[i];
		while (current != nullptr) {
			Hashnode* temp = current;
			current = current->next;
			delete temp;
		}
	}
}

// M8 yikicisi: Son erisim dizisinin dinamik bellegini serbest birakir
PerfomansAnaliz::~PerfomansAnaliz() {
	delete[] lastAccessed;
}