#pragma once
#include<iostream>
#include<string>

//������� � ����� ��� left child right sibling, ������ �� ���-����� ������������ ��������� �� ��� database 
//FileNode ���� ������������ �� ���� ��������, �� ����� ������������ ���� pointer to parent, ������ ��������, 
//����� �������� ���� � ���� ��� ���������� � ����������, ��� � ����

struct FileNode {
	std::string name; //��� �� �����/����������
	std::string content;// ���������� ���� �� ����, ������������ ����
	bool isFile = false;// ��������� ����� FileNode ���� � ���������� ��� ����, false - ����������, true - ����
	FileNode* parent = nullptr;// ������� ��� ����������� ����������, �������� �� ������ �� "����" �� ������������
	FileNode* child = nullptr;// ���������� ������� ��� ������� ���������� / ����
	FileNode* nextSibling = nullptr;// ������� ��� ���������� ���������� / ����
	FileNode();
	FileNode(std::string& name);// ���� ����������� ������� ����������
	FileNode(std::string name, bool _isFile, std::string _content); //���� ����������� ������� ����
	FileNode(bool _isFile);
	
	virtual ~FileNode() {};

	FileNode* findDir(const std::string entry);//������ ���������� �� ���

	FileNode* lastSib();//������ ���������� ������� �� �������� ����������, ����� nextSibling == nullptr; ��������� ����� ���������� ������� �������
						//��� ����� �� ���� "�������" ����������

	void addDir(std::string dirName);//������ ����������, ��� �� ���������� ������; ��� ����������, �� ������� ��������� �� ������ 

	void printDir() const;// ������� ������������ �� ����������

	FileNode* destroy(const std::string entry);

	FileNode* findFile(const std::string entry);//������ ���� �� ���
	void addFile(std::string entry);// ������ ������� ���� ��� ������ ����������, ���� �� default ������ � ������

	void printText(std::string entry); //������� ������������ �� ����� ������� ����
	void appendToFile(std::string entry, std::string text) {
			findFile(entry)->content.append(text);
	} // ��� ���� ������� ����, ������ ��� ������������ �� ����� �����
};

