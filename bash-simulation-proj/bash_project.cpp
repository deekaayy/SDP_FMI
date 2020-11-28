#include "pch.h"
#include "FileNode.h"
#include <iostream>
#include <fstream>

void traverseTree(FileNode* root)
{
	if (root == nullptr)
		return;

	while (root)
	{
		std::cout << " " << root->name;
		if (root->nextSibling)
			traverseTree(root->nextSibling);
		root = root->child;
	}
}

int main()
{

	std::string root = "root";
	FileNode* currNode = new FileNode(root); // има default-ен root node 
	char command[8]; //no command is going to be longer than this
	std::string fileName;//example 
	std::string path = currNode->name + "/";//инициализация на path стринг-а
	while (1) {
			std::cout << "[user@localhost " << path << "]$";

			std::cin >> command;

			if (!strcmp(command, "mkdir")) { //чрез тази команда се създава нова директория, ако няма съществуваща
				std::cin >> fileName;

				currNode->addDir(fileName);
			}

			else if (!strcmp(command, "pwd")) { //извежда текущият path към дадената директория
				std::cout << path << std::endl;
			}

			else if (!strcmp(command, "ls")) { //извежда съдържанието на текущата директория
				currNode->printDir();
			}

			else if (!strcmp(command, "cat")) { //извежда съдържанието на даден файл, ако съществува
				std::cin >> fileName;
				currNode->printText(fileName);
			}

			/*else if (!strcmp(command, "rmdir")) {
				std::cin >> fileName;
				currNode->destroy(fileName);
			}*/

			else if (!strcmp(command, "append")) { //добавя стринг към съдържанието на даден файл, ако съществува
				std::cin >> fileName;
				if (!currNode->findFile(fileName)) {
					currNode->addFile(fileName);
					continue;
				}
				std::cin.ignore();
				std::string content;
				std::getline(std::cin, content);
				currNode->appendToFile(fileName, content);
			}

			else if (!strcmp(command, "write")) { //създава файл; ако вече съществува такъв, му нулира съдържанието
				std::cin >> fileName;
				currNode->addFile(fileName);
			}

			else if (!strcmp(command, "cd")) { //команда за смяна на директория, може да се ходи напред и назад, стига да е валидно, 
				std::cin >> fileName;          //тук е единствената употреба на parent pointer-a
				if (fileName == "..") {
					if (currNode->parent != nullptr) {
						currNode = currNode->parent;
						continue;
					}
				}
				if (!currNode->findDir(fileName)) {
					std::cout << "No such directory exists...\n";
					continue;
				}
				FileNode* newdir = currNode->findDir(fileName); //лека модификация на текущият path
				currNode = newdir;
				path.append(fileName);
			}
			
	}

}
