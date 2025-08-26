
#include "BeamableCore/Public/AutoGen/PromotableLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPromotableLibrary::PromotableToJsonString(const UPromotable* Serializable, const bool Pretty)
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

UPromotable* UPromotableLibrary::Make(FString Checksum, int64 CreatedAt, UObject* Outer)
{
	auto Serializable = NewObject<UPromotable>(Outer);
	Serializable->Checksum = Checksum;
	Serializable->CreatedAt = CreatedAt;
	
	return Serializable;
}

void UPromotableLibrary::Break(const UPromotable* Serializable, FString& Checksum, int64& CreatedAt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Checksum = Serializable->Checksum;
		CreatedAt = Serializable->CreatedAt;
	}
		
}

