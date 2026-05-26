
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateWithModifiersResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMutateWithModifiersResultLibrary::MutateWithModifiersResultToJsonString(const UMutateWithModifiersResult* Serializable, const bool Pretty)
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

UMutateWithModifiersResult* UMutateWithModifiersResultLibrary::Make(bool bSuccess, FString Message, TMap<FString, FString> NewProperties, UObject* Outer)
{
	auto Serializable = NewObject<UMutateWithModifiersResult>(Outer);
	Serializable->bSuccess = bSuccess;
	Serializable->Message = Message;
	Serializable->NewProperties = NewProperties;
	
	return Serializable;
}

void UMutateWithModifiersResultLibrary::Break(const UMutateWithModifiersResult* Serializable, bool& bSuccess, FString& Message, TMap<FString, FString>& NewProperties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSuccess = Serializable->bSuccess;
		Message = Serializable->Message;
		NewProperties = Serializable->NewProperties;
	}
		
}

