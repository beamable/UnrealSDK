// Fill out your copyright notice in the Description page of Project Settings.


#include "Serialization/BeamCsvUtils.h"
#include "Engine/DataTable.h"
#include "Serialization/Csv/CsvParser.h"
#include "UObject/UnrealTypePrivate.h"

void UBeamCsvUtils::AddHeaderRow(FString& Csv, const TArray<FString> HeaderNames)
{
	// We find the end of the first line
	const auto EndOfFirstLine = Csv.Find(TEXT("\n"));
	const auto FirstLine = Csv.LeftChop(EndOfFirstLine);

	// We look between the document start and the end of the first line to see if we have all header names we expect.
	auto bHasAllFields = true;
	for (const auto& HeaderName : HeaderNames)
		bHasAllFields &= FirstLine.Contains(HeaderName, ESearchCase::IgnoreCase, ESearchDir::FromStart);

	// We ensure that this is never called with a CSV that already has a header.
	ensureAlwaysMsgf(!bHasAllFields, TEXT("The given CSV already has a header. FIRST_LINE=%s, CSV=\n%s"), *FirstLine, *Csv);

	// Then, we insert a row to function as the header
	Csv.InsertAt(0, FString::Join(HeaderNames, TEXT(",")) + TEXT("\n"));
}

void UBeamCsvUtils::AddAutoGenKeyField(FString& Csv)
{
	// Change the response content to add a key, This should be a utility function and only be code-gen'ed if the OApi spec does not specify a key column. 
	auto IntCursor = 0;
	int64 AutoIncrement = -1;
	do
	{
		IntCursor = Csv.Find(TEXT("\n"), ESearchCase::IgnoreCase, ESearchDir::FromStart, IntCursor);
		if (IntCursor)
		{
			const auto FixUp = AutoIncrement < 0 ? TEXT("__AutoGenKey__,") : FString::Printf(TEXT("%lld,"), AutoIncrement);
			Csv.InsertAt(IntCursor + 1, FixUp);
			IntCursor += 1 + FixUp.Len();
			AutoIncrement += 1;
		}
	}
	while (IntCursor != INDEX_NONE);
}

void UBeamCsvUtils::ParseIntoDataTable(UDataTable*& Table, UScriptStruct* StaticStruct, const FString& KeyField, const FString& Csv)
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UBeamCsvUtils.ParseIntoDataTable"), STATID_ParseIntoDataTable, STATGROUP_BeamUtils)
	
	Table->RowStruct = StaticStruct;
	Table->ImportKeyField = KeyField;
	Table->CreateTableFromCSVString(Csv);
}
