#include "BeamBackend/BeamBackendTestCallbacks.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Misc/AutomationTest.h"
#include "Serialization/BeamCsvUtils.h"


BEGIN_DEFINE_SPEC(FBeamCsvUtilsSpec, "BeamableUnreal.BeamCsvUtils", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext)
END_DEFINE_SPEC(FBeamCsvUtilsSpec)


void FBeamCsvUtilsSpec::Define()
{
	Describe("FBeamCsvUtils - Parsing", [this]()
	{
		// Get a condensed string so we can easily compare with the condensed string we generate.
		const FString WithHeaderCsv = TEXT(
			R"(Field4,Field1,Field2,Field3,Field5
0,100,a,100,BEAM_guild
1,101,b,101,BEAM_subgroup
2,102,c,102,BEAM_guild)");
		const FString WithoutHeaderCsv = TEXT(
			R"(0,100,a,100,BEAM_guild
1,101,b,101,BEAM_subgroup
2,102,c,102,BEAM_guild)");

		It("should parse the data correctly from the CSV (with header & turn key column into RowNames)", [this, WithoutHeaderCsv, WithHeaderCsv]()
		{
			UDataTable* Table = NewObject<UDataTable>();

			const FString Csv = WithHeaderCsv;
			UBeamCsvUtils::ParseIntoDataTable(Table, FBeamMockGetRequestCSVResponseRow::StaticStruct(), FBeamMockGetRequestCSVResponseRow::KeyField, Csv);

			TestTrue("Added Row with Key 0", Table->GetRowMap().Contains(FName(TEXT("0"))));
			TestTrue("Added Row with Key 1", Table->GetRowMap().Contains(FName(TEXT("1"))));
			TestTrue("Added Row with Key 2", Table->GetRowMap().Contains(FName(TEXT("2"))));

			const auto Row0 = *Table->FindRow<FBeamMockGetRequestCSVResponseRow>(FName(TEXT("0")), TEXT(""));
			const auto Row1 = *Table->FindRow<FBeamMockGetRequestCSVResponseRow>(FName(TEXT("1")), TEXT(""));
			const auto Row2 = *Table->FindRow<FBeamMockGetRequestCSVResponseRow>(FName(TEXT("2")), TEXT(""));

			TestEqual<FName>("Row 0 - RowName parsed correctly", Table->GetRowNames()[0], TEXT("0"));
			TestEqual("Row 0 - Field1 parsed correctly", Row0.Field1, 100);
			TestEqual("Row 0 - Field2 parsed correctly", Row0.Field2, TEXT("a"));
			TestEqual("Row 0 - Field3 parsed correctly", Row0.Field3, 100);
			TestNotEqual<FString>("Row 0 - Field4 parsed correctly", Row0.Field4, TEXT("0"));
			TestEqual<EBeamGroupType>("Row 0 - Field5 parsed correctly", Row0.Field5, EBeamGroupType::BEAM_guild);

			TestEqual<FName>("Row 1 - RowName parsed correctly", Table->GetRowNames()[1], TEXT("1"));
			TestEqual("Row 1 - Field1 parsed correctly", Row1.Field1, 101);
			TestEqual("Row 1 - Field2 parsed correctly", Row1.Field2, TEXT("b"));
			TestEqual("Row 1 - Field3 parsed correctly", Row1.Field3, 101);
			TestNotEqual<FString>("Row 1 - Field4 parsed correctly", Row1.Field4, TEXT("1"));
			TestEqual<EBeamGroupType>("Row 1 - Field5 parsed correctly", Row1.Field5, EBeamGroupType::BEAM_subgroup);

			TestEqual<FName>("Row 2 - RowName parsed correctly", Table->GetRowNames()[2], TEXT("2"));
			TestEqual("Row 2 - Field1 parsed correctly", Row2.Field1, 102);
			TestEqual("Row 2 - Field2 parsed correctly", Row2.Field2, TEXT("c"));
			TestEqual("Row 2 - Field3 parsed correctly", Row2.Field3, 102);
			TestNotEqual<FString>("Row 2 - Field4 parsed correctly", Row2.Field4, TEXT("2"));
			TestEqual<EBeamGroupType>("Row 2 - Field5 parsed correctly", Row2.Field5, EBeamGroupType::BEAM_guild);
		});

		It("should parse the data correctly from the CSV (with header & turn key column into RowNames & keep key as field)", [this, WithoutHeaderCsv, WithHeaderCsv]()
		{
			UDataTable* Table = NewObject<UDataTable>();

			const FString Csv = WithHeaderCsv;
			UBeamCsvUtils::ParseIntoDataTable(Table, FBeamMockGetRequestCSVResponseRow::StaticStruct(), FBeamMockGetRequestCSVResponseRow::KeyField, Csv);
			UBeamCsvUtils::StoreNameAsColumn<FBeamMockGetRequestCSVResponseRow>(Table, FBeamMockGetRequestCSVResponseRow::KeyField);

			TestTrue("Added Row with Key 0", Table->GetRowMap().Contains(FName(TEXT("0"))));
			TestTrue("Added Row with Key 1", Table->GetRowMap().Contains(FName(TEXT("1"))));
			TestTrue("Added Row with Key 2", Table->GetRowMap().Contains(FName(TEXT("2"))));

			const auto Row0 = *Table->FindRow<FBeamMockGetRequestCSVResponseRow>(FName(TEXT("0")), TEXT(""));
			const auto Row1 = *Table->FindRow<FBeamMockGetRequestCSVResponseRow>(FName(TEXT("1")), TEXT(""));
			const auto Row2 = *Table->FindRow<FBeamMockGetRequestCSVResponseRow>(FName(TEXT("2")), TEXT(""));

			TestEqual<FName>("Row 0 - RowName parsed correctly", Table->GetRowNames()[0], TEXT("0"));
			TestEqual("Row 0 - Field1 parsed correctly", Row0.Field1, 100);
			TestEqual("Row 0 - Field2 parsed correctly", Row0.Field2, TEXT("a"));
			TestEqual("Row 0 - Field3 parsed correctly", Row0.Field3, 100);
			TestEqual<FString>("Row 0 - Field4 parsed correctly", Row0.Field4, TEXT("0"));

			TestEqual<FName>("Row 1 - RowName parsed correctly", Table->GetRowNames()[1], TEXT("1"));
			TestEqual("Row 1 - Field1 parsed correctly", Row1.Field1, 101);
			TestEqual("Row 1 - Field2 parsed correctly", Row1.Field2, TEXT("b"));
			TestEqual("Row 1 - Field3 parsed correctly", Row1.Field3, 101);
			TestEqual<FString>("Row 1 - Field4 parsed correctly", Row1.Field4, TEXT("1"));

			TestEqual<FName>("Row 2 - RowName parsed correctly", Table->GetRowNames()[2], TEXT("2"));
			TestEqual("Row 2 - Field1 parsed correctly", Row2.Field1, 102);
			TestEqual("Row 2 - Field2 parsed correctly", Row2.Field2, TEXT("c"));
			TestEqual("Row 2 - Field3 parsed correctly", Row2.Field3, 102);
			TestEqual<FString>("Row 2 - Field4 parsed correctly", Row2.Field4, TEXT("2"));
		});

		It("stress test csv parser - 100000", [this, WithoutHeaderCsv, WithHeaderCsv]()
		{
			UDataTable* Table = NewObject<UDataTable>();

			FString Csv = TEXT(R"(Field4,Field1,Field2,Field3,Field5)");
			Csv.Reserve(100000 * 9 + Csv.Len());

			for (auto i = 0; i < 100000; i++)
				Csv.Appendf(TEXT("\n%d,0,0,0,0"), i);

			UBeamCsvUtils::ParseIntoDataTable(Table, FBeamMockGetRequestCSVResponseRow::StaticStruct(), FBeamMockGetRequestCSVResponseRow::KeyField, Csv);
			UBeamCsvUtils::StoreNameAsColumn<FBeamMockGetRequestCSVResponseRow>(Table, FBeamMockGetRequestCSVResponseRow::KeyField);

			TestTrue("Parsed all lines", Table->GetRowNames().Num() == 100000);
		});

		It("should add the header row correctly to a header-less csv", [this, WithoutHeaderCsv, WithHeaderCsv]()
		{
			FString Csv = WithoutHeaderCsv;
			UBeamCsvUtils::AddHeaderRow(Csv, FBeamMockGetRequestCSVResponseRow::HeaderFields);

			TestEqual("Added header correctly", Csv, WithHeaderCsv);
		});
	});
}
