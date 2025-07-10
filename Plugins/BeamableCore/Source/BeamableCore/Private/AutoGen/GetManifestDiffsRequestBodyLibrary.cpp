
#include "BeamableCore/Public/AutoGen/GetManifestDiffsRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UGetManifestDiffsRequestBodyLibrary::GetManifestDiffsRequestBodyToJsonString(const UGetManifestDiffsRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UGetManifestDiffsRequestBody* UGetManifestDiffsRequestBodyLibrary::Make(FBeamContentManifestId ManifestId, FOptionalString FromUid, FOptionalString ToUid, FOptionalInt32 Offset, FOptionalInt64 FromDate, FOptionalInt64 ToDate, FOptionalInt32 Limit, UObject* Outer)
{
	auto Serializable = NewObject<UGetManifestDiffsRequestBody>(Outer);
	Serializable->ManifestId = ManifestId;
	Serializable->FromUid = FromUid;
	Serializable->ToUid = ToUid;
	Serializable->Offset = Offset;
	Serializable->FromDate = FromDate;
	Serializable->ToDate = ToDate;
	Serializable->Limit = Limit;
	
	return Serializable;
}

void UGetManifestDiffsRequestBodyLibrary::Break(const UGetManifestDiffsRequestBody* Serializable, FBeamContentManifestId& ManifestId, FOptionalString& FromUid, FOptionalString& ToUid, FOptionalInt32& Offset, FOptionalInt64& FromDate, FOptionalInt64& ToDate, FOptionalInt32& Limit)
{
	ManifestId = Serializable->ManifestId;
	FromUid = Serializable->FromUid;
	ToUid = Serializable->ToUid;
	Offset = Serializable->Offset;
	FromDate = Serializable->FromDate;
	ToDate = Serializable->ToDate;
	Limit = Serializable->Limit;
		
}

