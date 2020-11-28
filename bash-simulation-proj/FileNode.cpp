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

FileNode * FileNode::findDir(const std::string entry)//��� ��������� �� ���� ��� ������ ���, �� ����� �����, 
{                                                    //���� �������� �� ������ ��� ���� �� ������ ��� ���������� �������
	FileNode* tmp = child;
	std::string newEntr = entry + "/";

	while (tmp != nullptr && tmp->name != entry) {
		tmp = tmp->nextSibling;
	}
	return tmp;
}

FileNode * FileNode::lastSib()
{
	FileNode* sib = child, *retSib = nullptr; // ��������� ����� retSib ���� ���������� ������� �������, ��� ���� �������� sib ���� ��������� �� nullptr

	while (sib != nullptr)//���� �� ���������� �������� �� ������� ������� � ��� sib �� �������, ������ �� ������� �� nullptr
	{						//����� �������� ������� ���������� ������� ��������
		retSib = sib;
		sib = sib->nextSibling;
	}

	return retSib;
}

//����������� ��������� find � lastSib() ����������� ���������� ���� �������� ��� ��������, ���� ��� ���������� ��� �� ������ � ���� "/",
//�� �� �� ��������� ��������
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
//������ ����� ���� �� ���, �������� ������ ������ ���� findDir ���������, ��� ���� �� ����� �� � ������ ����� ���� ������� � ��������� �� �����
//���������� ��������� �� ��� 2 ���� FileNode � ������� ����� ��.( a/ ; a.txt)
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

//��������� ������� ��������� � ������������, ��������� �� � �������� ����������
//����������� ������� �� child �������-�, ���� ����� �� ������� �� nextSibling �������-�, ������ �������� ������������ �� ����������� (a.k.a nullptr)
void FileNode::printDir() const
{
	if (child != nullptr) {
		std::cout << child->name;
		std::cout << " ";
		if (child->nextSibling != nullptr) {
			FileNode* tmp = child->nextSibling; //�������� ��������, ���� ����� �� �������
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

//������ ����, ���� ��� ������ �����, ���������� ������������ �� ��� ������ ������
void FileNode::addFile(std::string entry)
{
	//std::string newEnt = entry;
	if (findFile(entry)) {
		findFile(entry)->content = "";
	}
	else {

		if (child == nullptr) {
			child = new FileNode(entry.append(".txt"), true, ""); //��������� ���� ����� �� ����� ������� ��� parent, ��� ���� �� �����
																//�� �� ������� ���� ����������
			//child->parent = this;
		}
		else {
			lastSib()->nextSibling = new FileNode(entry.append(".txt"), true, "");
			//lastSib()->parent = this;
		}
	}
}

//������� ������������ �� ����, ���� ���� ������� �������������� ��
void FileNode::printText(std::string entry)
{
	//std::string newEnt = entry;
	if (!findFile(entry)) {
		std::cout << "File doesn't exist\n";
		return;
	}

	std::cout << findFile(entry)->content << std::endl;
}


