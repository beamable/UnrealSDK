
#include "BeamableCore/Public/AutoGen/MetadataPairLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMetadataPairLibrary::MetadataPairToJsonString(const UMetadataPair* Serializable, const bool Pretty)
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

UMetadataPair* UMetadataPairLibrary::Make(FString Key, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<UMetadataPair>(Outer);
	Serializable->Key = Key;
	Serializable->Value = Value;
	
	return Serializable;
}

void UMetadataPairLibrary::Break(const UMetadataPair* Serializable, FString& Key, FString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Key = Serializable->Key;
		Value = Serializable->Value;
	}
		
}

