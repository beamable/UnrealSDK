
#include "BeamableCore/Public/AutoGen/DisbandRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDisbandRequestBodyLibrary::DisbandRequestBodyToJsonString(const UDisbandRequestBody* Serializable, const bool Pretty)
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

UDisbandRequestBody* UDisbandRequestBodyLibrary::Make(FOptionalInt64 SubGroup, UObject* Outer)
{
	auto Serializable = NewObject<UDisbandRequestBody>(Outer);
	Serializable->SubGroup = SubGroup;
	
	return Serializable;
}

void UDisbandRequestBodyLibrary::Break(const UDisbandRequestBody* Serializable, FOptionalInt64& SubGroup)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SubGroup = Serializable->SubGroup;
	}
		
}

