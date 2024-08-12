
#include "AutoGen/ClientManifestResponse.h"
#include "AutoGen/Rows/ClientContentInfoTableRow.h"


void UClientManifestResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	CsvData = NewObject<UDataTable>(RequestData);

	

	// Generate this only if the CSV will not contain the header row
	UBeamCsvUtils::AddHeaderRow(ResponseContent, FClientContentInfoTableRow::HeaderFields);
	
	// Generate this always.
	UBeamCsvUtils::ParseIntoDataTable(CsvData,
	                                  FClientContentInfoTableRow::StaticStruct(),
	                                  FClientContentInfoTableRow::KeyField,
	                                  ResponseContent);

	UBeamCsvUtils::StoreNameAsColumn<FClientContentInfoTableRow>(CsvData, FClientContentInfoTableRow::KeyField);
}

