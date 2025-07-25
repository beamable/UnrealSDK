
#include "BeamableCore/Public/AutoGen/PANamespaceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPANamespaceLibrary::PANamespaceToJsonString(const UPANamespace* Serializable, const bool Pretty)
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

UPANamespace* UPANamespaceLibrary::Make(FString Namespace, FString Type, UObject* Outer)
{
	auto Serializable = NewObject<UPANamespace>(Outer);
	Serializable->Namespace = Namespace;
	Serializable->Type = Type;
	
	return Serializable;
}

void UPANamespaceLibrary::Break(const UPANamespace* Serializable, FString& Namespace, FString& Type)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Namespace = Serializable->Namespace;
		Type = Serializable->Type;
	}
		
}

