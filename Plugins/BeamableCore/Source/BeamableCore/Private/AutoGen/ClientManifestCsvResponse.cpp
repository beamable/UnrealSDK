
#include "AutoGen/ClientManifestCsvResponse.h"
#include "AutoGen/Rows/ClientContentInfoTableRow.h"


void UClientManifestCsvResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	CsvData = NewObject<UDataTable>(RequestData);

	
	// Change the response content to add a key, This should be a utility function and only be code-gen'ed if the OApi spec does not specify a key column.
	// TODO: This is a hard-code change to handle the fact that the Array representation inside the CSV that we get from the back-end is not compatible with the Unreal CSV parser.
	// TODO: we need this fixed at the backend.
	auto IntCursor = 0;
	do
	{
		IntCursor = ResponseContent.Find(TEXT("\n"), ESearchCase::IgnoreCase, ESearchDir::FromStart, IntCursor);		
		if (IntCursor)
		{
			const auto Len = ResponseContent.Len();
			auto Line = ResponseContent.LeftChop(Len - (IntCursor - 1));
			if (const auto PrevLineBreak = Line.Find(TEXT("\n"), ESearchCase::IgnoreCase, ESearchDir::FromEnd, IntCursor - 1))
				Line.RightChopInline(PrevLineBreak);

			auto MutableLine = Line;
			auto SkipColumnCount = 0;
			while (SkipColumnCount < 4)
			{
				MutableLine.RightChopInline(MutableLine.Find(",") + 1);
				SkipColumnCount += 1;
			}

			const auto ReplaceKeyInLine = MutableLine;
			MutableLine.InsertAt(0, "\"(\"\"");
			IntCursor += 4;
			MutableLine.Append("\"\")\"");
			IntCursor += 4;
			auto SplitIdx = MutableLine.Find(";", ESearchCase::IgnoreCase, ESearchDir::FromStart, 0);
			while (SplitIdx != INDEX_NONE)
			{
				MutableLine.InsertAt(SplitIdx + 1, "\"\"");
				MutableLine.InsertAt(SplitIdx, "\"\"");

				IntCursor += 4;
				SplitIdx = MutableLine.Find(";", ESearchCase::IgnoreCase, ESearchDir::FromStart, SplitIdx + 3); // We add two here so that we skipp the '\"' we just added as well
			}
			MutableLine.ReplaceCharInline(';', ',');
			MutableLine = Line.Replace(*ReplaceKeyInLine, *MutableLine);
			ResponseContent.ReplaceInline(*Line, *MutableLine);

			IntCursor += 1; // For the skipped character
		}
	}
	while (IntCursor != INDEX_NONE && IntCursor < ResponseContent.Len());

	// Generate this only if the CSV will not contain the header row
	UBeamCsvUtils::AddHeaderRow(ResponseContent, FClientContentInfoTableRow::HeaderFields);
	
	// Generate this always.
	UBeamCsvUtils::ParseIntoDataTable(CsvData,
	                                  FClientContentInfoTableRow::StaticStruct(),
	                                  FClientContentInfoTableRow::KeyField,
	                                  ResponseContent);

	UBeamCsvUtils::StoreNameAsColumn<FClientContentInfoTableRow>(CsvData, FClientContentInfoTableRow::KeyField);
}

