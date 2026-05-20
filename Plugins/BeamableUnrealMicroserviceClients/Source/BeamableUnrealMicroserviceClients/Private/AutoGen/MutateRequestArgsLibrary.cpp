
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMutateRequestArgsLibrary::MutateRequestArgsToJsonString(const UMutateRequestArgs* Serializable, const bool Pretty)
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

UMutateRequestArgs* UMutateRequestArgsLibrary::Make(TArray<UMutationInput*> Inputs, UObject* Outer)
{
	auto Serializable = NewObject<UMutateRequestArgs>(Outer);
	Serializable->Inputs = Inputs;
	
	return Serializable;
}

void UMutateRequestArgsLibrary::Break(const UMutateRequestArgs* Serializable, TArray<UMutationInput*>& Inputs)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Inputs = Serializable->Inputs;
	}
		
}

