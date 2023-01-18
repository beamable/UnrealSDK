
#include "AutoGen/Rows/ClientContentInfoTableRow.h"

const FString FClientContentInfoTableRow::KeyField = GET_MEMBER_NAME_STRING_CHECKED(FClientContentInfoTableRow, ContentId);
const TArray<FString> FClientContentInfoTableRow::HeaderFields = {
	GET_MEMBER_NAME_STRING_CHECKED(FClientContentInfoTableRow, Type),
	KeyField,
	GET_MEMBER_NAME_STRING_CHECKED(FClientContentInfoTableRow, Version),
	GET_MEMBER_NAME_STRING_CHECKED(FClientContentInfoTableRow, Uri),
	GET_MEMBER_NAME_STRING_CHECKED(FClientContentInfoTableRow, Tags)	
};

