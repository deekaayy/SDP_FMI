#pragma once
#include<iostream>
#include<string>

//Избрано е дърво тип left child right sibling, защото то най-добре представлява структура от тип database 
//FileNode имат стандартните за типа елементи, но носят допълнителни като pointer to parent, булева стойност, 
//която определя дали е файл или директория и съдържание, ако е файл

struct FileNode {
	std::string name; //име на файла/директория
	std::string content;// съдържание само на файл, директорията няма
	bool isFile = false;// индикатор даден FileNode дали е директория или файл, false - директория, true - файл
	FileNode* parent = nullptr;// пойнтър към предходната директория, използва се когато се "ходи" по директориите
	FileNode* child = nullptr;// стандартен пойнтър към първата директория / файл
	FileNode* nextSibling = nullptr;// пойнтър към следващата директория / файл
	FileNode();
	FileNode(std::string& name);// този конструктор създава директория
	FileNode(std::string name, bool _isFile, std::string _content); //този конструктор създава файл
	FileNode(bool _isFile);
	
	virtual ~FileNode() {};

	FileNode* findDir(const std::string entry);//намира директория по име

	FileNode* lastSib();//намира последният елемент на дадената директория, чийто nextSibling == nullptr; функцията връща последният валиден елемент
						//към който ще бъде "закачен" следващият

	void addDir(std::string dirName);//добавя директория, ако не съществува такава; ако съществува, се извежда съобщение за грешка 

	void printDir() const;// извежда съдържанието на директория

	FileNode* destroy(const std::string entry);

	FileNode* findFile(const std::string entry);//намира файл по име
	void addFile(std::string entry);// добавя текстов файл към дадена директория, като по default файлът е празен

	void printText(std::string entry); //извежда съдържанието на даден текстов файл
	void appendToFile(std::string entry, std::string text) {
			findFile(entry)->content.append(text);
	} // при вече намерен файл, добавя към съдържанието му даден текст
};

