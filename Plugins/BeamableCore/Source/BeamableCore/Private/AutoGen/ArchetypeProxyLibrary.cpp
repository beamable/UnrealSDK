
#include "BeamableCore/Public/AutoGen/ArchetypeProxyLibrary.h"

#include "CoreMinimal.h"


FString UArchetypeProxyLibrary::ArchetypeProxyToJsonString(const UArchetypeProxy* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UArchetypeProxy* UArchetypeProxyLibrary::Make(FString Service, FString Namespace, UObject* Outer)
{
	auto Serializable = NewObject<UArchetypeProxy>(Outer);
	Serializable->Service = Service;
	Serializable->Namespace = Namespace;
	
	return Serializable;
}

void UArchetypeProxyLibrary::Break(const UArchetypeProxy* Serializable, FString& Service, FString& Namespace)
{
	Service = Serializable->Service;
	Namespace = Serializable->Namespace;
		
}

