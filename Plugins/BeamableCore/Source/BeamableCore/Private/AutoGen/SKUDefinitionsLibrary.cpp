
#include "BeamableCore/Public/AutoGen/SKUDefinitionsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USKUDefinitionsLibrary::SKUDefinitionsToJsonString(const USKUDefinitions* Serializable, const bool Pretty)
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

USKUDefinitions* USKUDefinitionsLibrary::Make(int64 Version, int64 Created, TArray<USKU*> Definitions, UObject* Outer)
{
	auto Serializable = NewObject<USKUDefinitions>(Outer);
	Serializable->Version = Version;
	Serializable->Created = Created;
	Serializable->Definitions = Definitions;
	
	return Serializable;
}

void USKUDefinitionsLibrary::Break(const USKUDefinitions* Serializable, int64& Version, int64& Created, TArray<USKU*>& Definitions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Version = Serializable->Version;
		Created = Serializable->Created;
		Definitions = Serializable->Definitions;
	}
		
}

