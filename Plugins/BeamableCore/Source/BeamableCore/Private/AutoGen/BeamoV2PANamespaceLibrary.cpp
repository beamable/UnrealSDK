
#include "BeamableCore/Public/AutoGen/BeamoV2PANamespaceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2PANamespaceLibrary::BeamoV2PANamespaceToJsonString(const UBeamoV2PANamespace* Serializable, const bool Pretty)
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

UBeamoV2PANamespace* UBeamoV2PANamespaceLibrary::Make(FString Namespace, FString Type, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2PANamespace>(Outer);
	Serializable->Namespace = Namespace;
	Serializable->Type = Type;
	
	return Serializable;
}

void UBeamoV2PANamespaceLibrary::Break(const UBeamoV2PANamespace* Serializable, FString& Namespace, FString& Type)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Namespace = Serializable->Namespace;
		Type = Serializable->Type;
	}
		
}

