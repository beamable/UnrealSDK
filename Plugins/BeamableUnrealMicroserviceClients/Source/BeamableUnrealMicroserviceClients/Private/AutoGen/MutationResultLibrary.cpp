
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutationResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMutationResultLibrary::MutationResultToJsonString(const UMutationResult* Serializable, const bool Pretty)
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

UMutationResult* UMutationResultLibrary::Make(bool bSuccess, FString Message, TArray<UMutationOutput*> Outputs, UObject* Outer)
{
	auto Serializable = NewObject<UMutationResult>(Outer);
	Serializable->bSuccess = bSuccess;
	Serializable->Message = Message;
	Serializable->Outputs = Outputs;
	
	return Serializable;
}

void UMutationResultLibrary::Break(const UMutationResult* Serializable, bool& bSuccess, FString& Message, TArray<UMutationOutput*>& Outputs)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSuccess = Serializable->bSuccess;
		Message = Serializable->Message;
		Outputs = Serializable->Outputs;
	}
		
}

