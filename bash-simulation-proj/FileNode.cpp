#include"pch.h"
#include"FileNode.h"

FileNode::FileNode()
{
	name = "New Dir";
	content = "";
	isFile = false;
}

FileNode::FileNode(std::string& name)
{
	this->name = name;
	this->content = "";
	isFile = false;
}

FileNode::FileNode(std::string name, bool _isFile, std::string _content)
{
	this->name = name;
	isFile = true;
	content = _content;
}

FileNode::FileNode(bool _isFile)
{
	name = "New File";
	isFile = true;
	content = "";
}

FileNode * FileNode::findDir(const std::string entry)//При попадение на файл със същото име, ще върне файла, 
{                                                    //няма опасност от грешки тъй като се работи без повтаряеми файлове
	FileNode* tmp = child;
	std::string newEntr = entry + "/";

	while (tmp != nullptr && tmp->name != entry) {
		tmp = tmp->nextSibling;
	}
	return tmp;
}

FileNode * FileNode::lastSib()
{
	FileNode* sib = child, *retSib = nullptr; // функцията връща retSib като последният валиден елемент, тъй като използва sib като индикатор за nullptr

	while (sib != nullptr)//пази се последната стойност на валиден пойнтер и със sib се обхожда, докато не попадне на nullptr
	{						//всяка итерация запазва последната валидна стойност
		retSib = sib;
		sib = sib->nextSibling;
	}

	return retSib;
}

//Използвайки функциите find и lastSib() съответната директория бива добавена към текущата, като към подаденото име се добавя в края "/",
//за да се различава визуално
void FileNode::addDir(std::string dirName)
{
	if (findDir(dirName)) {
		std::cout << "Directory already exists!\n";
	}
	else {

		if (child == nullptr) {
			child = new FileNode(dirName.append("/"));
			child->parent = this;
		}

		else {
			lastSib()->nextSibling = new FileNode(dirName.append("/"));
			lastSib()->parent = this;
		}
	}
}
//намира даден файл по име, използва същата логика като findDir функцията, тъй като се счита че в базата данни няма файлове с повтарящи се имена
//Програмата позволява да има 2 типа FileNode с еднакви имена пр.( a/ ; a.txt)
FileNode * FileNode::findFile(const std::string entry)
{
	std::string newEntr = entry;
	FileNode* tmp = child;
	if (entry.length() > 4 && entry.substr(entry.length() - 4) == ".txt") {
	}
	else {
		newEntr = entry + ".txt";
	}

	while (tmp != nullptr && tmp->name != newEntr) {
		tmp = tmp->nextSibling;
	}
	return tmp;
}

//функцията извежда файловете и директориите, съдържащи се в дадената директория
//Обхождането започва от child пойнтер-а, след което се итерира по nextSibling пойнтер-а, докато достигне невъзможност за продължение (a.k.a nullptr)
void FileNode::printDir() const
{
	if (child != nullptr) {
		std::cout << child->name;
		std::cout << " ";
		if (child->nextSibling != nullptr) {
			FileNode* tmp = child->nextSibling; //временен указател, чрез който се итерира
			std::cout << " ";
			while (tmp != nullptr) {
				std::cout << tmp->name << " ";
				tmp = tmp->nextSibling;
			}
		}
	}
	std::cout << std::endl;
}

FileNode * FileNode::destroy(const std::string entry)
{
	FileNode* tmp = findDir(entry);
	if (tmp->child == nullptr && tmp->nextSibling == nullptr) {
		delete tmp;
		tmp = nullptr;
	}
	return tmp;
}

//добавя файл, като ако намери файла, презаписва съдържанието му със празен стринг
void FileNode::addFile(std::string entry)
{
	//std::string newEnt = entry;
	if (findFile(entry)) {
		findFile(entry)->content = "";
	}
	else {

		if (child == nullptr) {
			child = new FileNode(entry.append(".txt"), true, ""); //файловете няма нужда да носят пойнтер към parent, тъй като не могат
																//да се избират като директории
			//child->parent = this;
		}
		else {
			lastSib()->nextSibling = new FileNode(entry.append(".txt"), true, "");
			//lastSib()->parent = this;
		}
	}
}

//извежда съдържанието на файл, след като провери съществуването му
void FileNode::printText(std::string entry)
{
	//std::string newEnt = entry;
	if (!findFile(entry)) {
		std::cout << "File doesn't exist\n";
		return;
	}

	std::cout << findFile(entry)->content << std::endl;
}


