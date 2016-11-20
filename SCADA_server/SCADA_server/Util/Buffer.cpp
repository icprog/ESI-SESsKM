#include "Buffer.h"

#include "stdafx.h"
#include "Buffer.h"


void Buffer::expand()
{
	EnterCriticalSection(&this->cs);

	char* newData;
	int newSize = 0;

	newSize = this->size * 2;
	newData = new char[sizeof(char)*newSize + 1];
	memset(newData, 0, newSize);
	if (this->pushIdx < this->popIdx) { // ako je push manji od pop indeksa, onda je data iz dva dela pa radimo 2 mem kopija
		int rest = this->size - this->popIdx;
		memcpy(newData, this->data + this->popIdx, rest); //kopiraj kraj starog bufera u novi 
		memcpy(newData + rest, this->data, this->pushIdx); //nastavi na novi data onaj data sa pocetka starog
	}
	else {
		memcpy(newData, this->data + this->popIdx, this->count);
	}

	//kada povecamo moramo da premestimo podatke sa kraja starog buffer-a na pocetak novog buffer-a
	this->data = newData;
	this->size = newSize;
	this->pushIdx = this->count;
	this->popIdx = 0;

	LeaveCriticalSection(&this->cs);
}

void Buffer::shrink()
{
	EnterCriticalSection(&this->cs);
	int rest = this->size - this->popIdx;
	double fullness = (double)this->count / this->size;

	// ako je bafer popunjen manje od jedne cetvrtine smanji ga za pola
	if (fullness <= 0.25) {
		char *newData ;
		int newSize = 0;

		// za slucaj da bafer nije bio povecavan uvek za 2 puta
		if (this->size % 2 == 0)
			newSize = this->size / 2;
		else
			newSize = this->size / 2 + 2;

		newData = new char[sizeof(char)*newSize + 1];
		memset(newData, 0, newSize);

		if (this->pushIdx < this->popIdx) { //ako je push manji od pop indeksa, onda je data iz dva dela pa radimo 2 mem kopija
			int rest = this->size - this->popIdx;
			memcpy(newData, this->data + this->popIdx, rest); //kopiraj kraj starog na pocetak novog
			memcpy(newData + rest, this->data, this->pushIdx); //pomeri pocetak starog na nastavak novog
		}
		else { //iz jednog dela, kopiraj stari u novi
			memcpy(newData, this->data + this->popIdx, this->count);
		}

		this->data = newData;
		this->size = newSize;
		this->pushIdx = this->count;
		this->popIdx = 0;

		LeaveCriticalSection(&this->cs);
	}

}

int Buffer::push(char * data, int sizeOfData)
{
	EnterCriticalSection(&this->cs);

	/*short sizeOfData = 0;
	if (type == 0) {
		sizeOfData = *(short *)(data + 16);
		sizeOfData = ntohs(sizeOfData) + 18;
	}*/

	// ako je bafer vec pun count == size, radi prosirivanje, ali prvo utvrdi za koliko puta
	// ili ako je velicina podataka veca od velicine ostatka slobodnog prostora u baferu
	if ((this->count == this->size) || ((this->size - this->count) < sizeOfData)) {
		if (sizeOfData > this->size * 2) {
			for (int i = 0; i < sizeOfData / this->size + 1; i++)
				expand();
		}
		else {
			expand();
		}
	}

	int rest = this->size - this->pushIdx;
	if (sizeOfData > rest) {
		int j = 0;
		for (int i = this->pushIdx; i < this->pushIdx + rest; i++) {
			this->data[i] = data[j];
			j++;
		}
		j = 0;
		for (int i = 0; i < sizeOfData - rest; i++) {
			this->data[i] = data[j];
			j++;
		}
		this->pushIdx = sizeOfData - rest;
		this->count += sizeOfData;
	}
	else {
		int j = 0;
		for (int i = this->pushIdx; i < this->pushIdx + sizeOfData; i++) {
			this->data[i] = data[j];
			j++;
		}
		this->count += sizeOfData;
		this->pushIdx += sizeOfData;
	}

	////////ispis bafera
	printf("\nSadrzaj bafera: ");
	for (int i = 0; i < this->size; i++) {
		printf("%c", this->data[i]);
	}
	printf("\nOstatak: \n");
	printf("PopIdx: %d\n", this->popIdx);
	printf("PushIdx: %d\n", this->pushIdx);
	printf("Count: %d\n", this->count);
	printf("Size: %d\n", this->size);
	////////
	LeaveCriticalSection(&this->cs);

	return 0;
}

int Buffer::pop(char * data, int velicina)
{
	EnterCriticalSection(&this->cs);

	/*short velicina = -1;
	if (type == 0) {
		velicina = *(short *)(this->data + 16);
		velicina = ntohs(velicina) + 18;
	}
	else {
		velicina = *((int*)(this->data + popIdx));
	}*/

	shrink();

	if (this->count == 0) {
		return 0;
	}

	int rest = this->size - this->popIdx;
	//prvi slucaj da je data negde u sredini i onda je pomeramo na pocetak
	if (this->popIdx < this->pushIdx || rest-velicina > 0) {
		int j = 0;
		for (int i = this->popIdx; i < this->popIdx+velicina; i++) {
			data[j] = this->data[i];
			this->data[i] = 0;
			j++;
		}
		memset(this->data + this->popIdx, 0, velicina);
		this->popIdx += velicina;
	}
	else {
		//iz dva dela, prvo kopiraj kraj data na pocetak, pa onda sa pocetka pomeri
		int j = 0;
		for (int i = this->popIdx; i < this->popIdx + rest; i++) {
			data[j] = this->data[i];
			this->data[i] = 0;
			j++;
		}
		j = 0;
		for (int i = 0; i < velicina - rest; i++) {
			data[j] = this->data[i];
			this->data[i] = 0;
			j++;
		}

		this->popIdx = velicina - rest;	
	}
	this->count -= velicina;

	//////////ispis bafera
	printf("\nSadrzaj bafera: ");
	for (int i = 0; i < this->size; i++) {
		printf("%c", this->data[i]);
	}
	printf("\nOstatak: \n");
	printf("PopIdx: %d\n", this->popIdx);
	printf("PushIdx: %d\n", this->pushIdx);
	printf("Count: %d\n", this->count);
	printf("Size: %d\n", this->size);
	///////////

	LeaveCriticalSection(&this->cs);
	return 0;
}

Buffer::~Buffer()
{
	delete name, name = 0;
	delete data, data = 0;
	DeleteCriticalSection(&this->cs);
}
