
#include "stdafx.h"
#include "Buffer.h"

void Buffer::expand()
{
	char* newData = nullptr;		//new buffer
	int newSize;		//new buffer size

	newSize = this->size * 2;		//new size is 2*size

	newData = new char[newSize + 1];
	if (this->pushIdx < this->popIdx)	 //ako je push manji od pop idx, onda je data iz 2 dela pa treba 2 memcpy
	{
		int rest = this->size - this->popIdx;

		//memcpy(newData, buffer->data + buffer->popIdx, rest); //kopiraj kraj starog bufera u novi 
		for (int i = 0; i < rest; i++)		//kopiraj kraj starog u novi 
		{
			newData[i] = this->data[i + this->popIdx];
		}

		//memcpy(newData + rest, buffer->data, buffer->pushIdx); //nastavi na novi data onaj data sa pocetka starog
		for (int i = 0; i < this->pushIdx; i++)	//nastavi na novi data onaj data sa pocetka starog
		{
			newData[i + rest] = this->data[i];
		}
	}
	else
	{
		//memcpy(newData, buffer->data + buffer->popIdx, buffer->count);
		for (int i = 0; i < this->count; i++)
		{
			newData[i] = this->data[i + this->popIdx];
		}
	}


	this->data = newData;
	this->size = newSize;
	this->pushIdx = this->count;
	this->popIdx = 0;
}

int Buffer::push(char * data, int type)
{
	EnterCriticalSection(&this->cs);
	short sizeOfData = 0;
	if(type == 0){
		sizeOfData = *(short *)(data + 16);
		sizeOfData = ntohs(sizeOfData)+18;
	}

	// ako je bafer vec pun count == size, radi prosirivanje, ali prvo utvrdi za koliko puta
	// ili ako je velicina podataka veca od velicine ostatka slobodnog prostora u baferu
	if ((this->count >= this->size) || ((this->size - this->count) < sizeOfData)) {
		if (sizeOfData > this->size * 2) {
			expand();
		}
		else
			expand();
			printf("EXPAND");

	}

	for (int i = 0; i < sizeOfData; i++) {
		this->data[this->pushIdx] = data[i];
		this->pushIdx++;

		if (this->pushIdx == this->size)
			this->pushIdx = 0;
	}

	this->count += sizeOfData;


	/*debug output*/
	cout << "\nSadrzaj bafera: ";
	for (int i = 0; i < this->size; i++) {
		cout << this->data[i];
	}
	cout << "\nOstatak: \n";
	cout << "PopIdx:" << this->popIdx << endl;
	cout << "PushIdx:" << this->pushIdx << endl;
	cout << "Count:" << this->count << endl;
	cout << "Size: " << this->size << endl;
	/*end of debut output*/

	LeaveCriticalSection(&this->cs);

	return 0;
}

int Buffer::pop(char * data, int type)
{
	//short velicina = *((short *)this->data + 2);
	short velicina = -1;
	if (type == 0) {
		//sizeOfData = *(short *)((char *)((short *)data + 6) + 1);
		
		velicina = *(short *)(this->data + 16);
		velicina = ntohs(velicina) + 18;
	}
	else {
		velicina = *((int*)(this->data + popIdx));
	}
	
	if (this->count == 0) {
		return false;
	}

	for (int i = 0; i < velicina; i++) {

		data[i] = this->data[this->popIdx];

		this->popIdx++;

		if (this->popIdx == this->size) {
			this->popIdx = 0;
		}
	}

	this->count -= velicina;

	//debug ispis
	cout << "\nSadrzaj bafera: ";
	for (int i = 0; i < this->size; i++) {
		cout << this->data[i];
	}
	cout << "\nOstatak: \n";
	cout << "PopIdx: " << this->popIdx << endl;
	cout << "PushIdx: " << this->pushIdx << endl;
	cout << "Count: " << this->count << endl;
	cout << "Size: " << this->size << endl;
	//kraj debug ispisa

	/*EnterCriticalSection(&this->cs);

	short velicina = *((short *)this->data + 2);

	if (this->count == 0) {
		return 0;
	}

	//prvi slucaj da je data negde u sredini i onda je pomeramo na pocetak
	if (this->popIdx < this->pushIdx) {
		//memcpy(data, buffer->data + buffer->popIdx, velicina); //kopiraj data na pocetak buffer-a
		for (int i = 0; i < velicina; i++) {
			data[i] = this->data[i + this->popIdx];
		}
		//memset(buffer->data + buffer->popIdx, 0, velicina);
		for (int i = 0; i < velicina; i++) {
			this->data[i + this->popIdx] = 0;
		}
		this->popIdx += velicina;
	}
	else {
		//iz dva dela, prvo kopiraj kraj data na pocetak, pa onda sa pocetka pomeri
		int rest = this->size - this->popIdx;
		//memcpy(data, buffer->data + buffer->popIdx, rest);
		for (int i = 0; i < rest; i++) {
			data[i] = this->data[i + this->popIdx];
		}
		//memcpy(data, buffer->data, velicina - rest);
		for (int i = 0; i < velicina - rest; i++) {
			data[i] = this->data[i];
		}
		//memset(buffer->data + buffer->popIdx, 0, rest);
		for (int i = 0; i < rest; i++) {
			this->data[i + this->popIdx] = 0;
		}
		//memset(buffer->data, 0, velicina - rest);
		for (int i = 0; i < velicina - rest; i++) {
			this->data[i] = 0;
		}

		this->popIdx = velicina - rest;
	}

	this->count -= velicina;


	cout << "\nSadrzaj bafera: ";
	for (int i = 0; i < this->size; i++) {
		cout << this->data[i];
	}
	cout << "\nOstatak: \n";
	cout << "PopIdx: " << this->popIdx << endl;
	cout << "PushIdx: " << this->pushIdx << endl;
	cout << "Count: " << this->count << endl;
	cout << "Size: " << this->size << endl;


	LeaveCriticalSection(&this->cs);
	return 0;
	*/
}

void Buffer::shrink()
{
	EnterCriticalSection(&this->cs);
	double fullness = this->count / this->size;

	// ako je bafer popunjen manje od jedne cetvrtine smanji ga za pola
	if (fullness <= 0.25) {
		char *newData;
		int newSize = 0;

		// za slucaj da bafer nije bio povecavan uvek za 2 puta
		if (this->size % 2 == 0)
			newSize = this->size / 2;
		else
			newSize = this->size / 2 + 2;

		// malloc new array
		newData = (char *)malloc(sizeof(char) * newSize);      // allocate 50 ints


															   // prepisi podatke
		for (int i = 0; i < this->count; i++) {
			// ako je pokazivac na prvi za citanje ujedno i poslednja lokacija, postavi ga na 0
			if (this->popIdx == this->size)
				this->popIdx = 0;

			newData[i] = this->data[i];
		}

		this->data = newData;
		this->size = newSize;
		this->pushIdx = this->count;
		this->popIdx = 0;
	}

		LeaveCriticalSection(&this->cs);
}


/*void Buffer::createBuffer(char * name, int bufferLength, CRITICAL_SECTION * cs)
{
EnterCriticalSection(cs);
Buffer buffer;
buffer.name = name;
buffer.count = 0;
buffer.size = bufferLength;
buffer.popIdx = 0;
buffer.pushIdx = 0;
buffer.data = new char[bufferLength + 1]; //maloc
CRITICAL_SECTION bufferCS;
InitializeCriticalSection(&bufferCS);
buffer.cs = bufferCS;
LeaveCriticalSection(cs);
}*/

Buffer::~Buffer()
{
	delete name, name = 0;
	delete data, data = 0;
	DeleteCriticalSection(&this->cs);
}
