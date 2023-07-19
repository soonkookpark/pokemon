#pragma once
#include "DataTable.h"
class StringTable : public DataTable
{
	/*string id를 넘기면 id에 매칭되어있는 문자열을 return 해주기*/
protected:
	/*id와 문자열을 담을 컨테이너, unorderd map이 여러개 존재하는 vector*/
	std::vector<std::unordered_map<std::string, std::string>> tables;

public:
	StringTable() : DataTable(DataTable::Ids::String), tables((int)Languages::COUNT) {}
	virtual ~StringTable() override { Release(); }

	virtual bool Load() override;
	virtual void Release() override;

	const std::string& Get(const std::string& id, Languages lang) const;
	const std::string& Get(const std::string& id) const //variables에 저장된 기본 언어를 lang으로 사용함
	{
		return Get(id, Variables::CurrentLang);
	}
	const std::wstring GetUni(const std::string& id, Languages lang);


};
