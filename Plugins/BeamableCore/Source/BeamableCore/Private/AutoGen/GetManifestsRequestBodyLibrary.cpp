
#include "BeamableCore/Public/AutoGen/GetManifestsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetManifestsRequestBodyLibrary::GetManifestsRequestBodyToJsonString(const UGetManifestsRequestBody* Serializable, const bool Pretty)
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

UGetManifestsRequestBody* UGetManifestsRequestBodyLibrary::Make(FOptionalBool bArchived, FOptionalInt32 Limit, FOptionalInt32 Offset, UObject* Outer)
{
	auto Serializable = NewObject<UGetManifestsRequestBody>(Outer);
	Serializable->bArchived = bArchived;
	Serializable->Limit = Limit;
	Serializable->Offset = Offset;
	
	return Serializable;
}

void UGetManifestsRequestBodyLibrary::Break(const UGetManifestsRequestBody* Serializable, FOptionalBool& bArchived, FOptionalInt32& Limit, FOptionalInt32& Offset)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bArchived = Serializable->bArchived;
		Limit = Serializable->Limit;
		Offset = Serializable->Offset;
	}
		
}

