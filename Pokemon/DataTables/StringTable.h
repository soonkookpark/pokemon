#pragma once
#include "DataTable.h"
class StringTable : public DataTable
{
	/*string id�� �ѱ�� id�� ��Ī�Ǿ��ִ� ���ڿ��� return ���ֱ�*/
protected:
	/*id�� ���ڿ��� ���� �����̳�, unorderd map�� ������ �����ϴ� vector*/
	std::vector<std::unordered_map<std::string, std::string>> tables;

public:
	StringTable() : DataTable(DataTable::Ids::String), tables((int)Languages::COUNT) {}
	virtual ~StringTable() override { Release(); }

	virtual bool Load() override;
	virtual void Release() override;

	const std::string& Get(const std::string& id, Languages lang) const;
	const std::string& Get(const std::string& id) const //variables�� ����� �⺻ �� lang���� �����
	{
		return Get(id, Variables::CurrentLang);
	}
	const std::wstring GetUni(const std::string& id, Languages lang);


};
