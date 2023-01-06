#include "BeamBackend/BeamBackendTestCallbacks.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Misc/AutomationTest.h"
#include "Serialization/BeamCsvUtils.h"


BEGIN_DEFINE_SPEC(FBeamCsvUtilsSpec, "BeamableUnreal.BeamCsvUtils", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
END_DEFINE_SPEC(FBeamCsvUtilsSpec)


void FBeamCsvUtilsSpec::Define()
{
	Describe("FBeamCsvUtils - Parsing", [this]()
	{
		// Get a condensed string so we can easily compare with the condensed string we generate.
		const FString WithHeaderCsv = TEXT(
			R"(KeyField,Field1,Field2,Field3
0,100,a,100
1,101,b,101
2,102,c,102)");
		const FString WithoutHeaderCsv = TEXT(
			R"(0,100,a,100
1,101,b,101
2,102,c,102)");

		It("should parse the data correctly from the CSV (with header)", [this, WithoutHeaderCsv, WithHeaderCsv]()
		{
			UDataTable* Table = NewObject<UDataTable>();

			const FString Csv = WithHeaderCsv;
			UBeamCsvUtils::ParseIntoDataTable(Table, FBeamMockGetRequestCSVResponseRow::StaticStruct(), FBeamMockGetRequestCSVResponseRow::KeyField, Csv);

			TestTrue("Added Row with Key 0", Table->GetRowMap().Contains(FName(TEXT("0"))));
			TestTrue("Added Row with Key 1", Table->GetRowMap().Contains(FName(TEXT("1"))));
			TestTrue("Added Row with Key 2", Table->GetRowMap().Contains(FName(TEXT("2"))));
			
			FBeamMockGetRequestCSVResponseRow Row0, Row1, Row2;
			Row0 = *Table->FindRow<FBeamMockGetRequestCSVResponseRow>(FName(TEXT("0")), TEXT(""));
			Row1 = *Table->FindRow<FBeamMockGetRequestCSVResponseRow>(FName(TEXT("1")), TEXT(""));
			Row2 = *Table->FindRow<FBeamMockGetRequestCSVResponseRow>(FName(TEXT("2")), TEXT(""));			

			TestEqual("Row 0 - Field1 parsed correctly", Row0.Field1, 100);
			TestEqual("Row 0 - Field2 parsed correctly", Row0.Field2, TEXT("a"));
			TestEqual("Row 0 - Field3 parsed correctly", Row0.Field3, 100);

			TestEqual("Row 1 - Field1 parsed correctly", Row1.Field1, 101);
			TestEqual("Row 1 - Field2 parsed correctly", Row1.Field2, TEXT("b"));
			TestEqual("Row 1 - Field3 parsed correctly", Row1.Field3, 101);
			
			TestEqual("Row 2 - Field1 parsed correctly", Row2.Field1, 102);
			TestEqual("Row 2 - Field2 parsed correctly", Row2.Field2, TEXT("c"));
			TestEqual("Row 2 - Field3 parsed correctly", Row2.Field3, 102);
		});
		
		It("should add the header row correctly to a header-less csv", [this, WithoutHeaderCsv, WithHeaderCsv]()
		{			
			FString Csv = WithoutHeaderCsv;
			UBeamCsvUtils::AddHeaderRow(Csv, FBeamMockGetRequestCSVResponseRow::HeaderFields);

			TestEqual("Added header correctly", Csv, WithHeaderCsv);
		});
		
	});
}
