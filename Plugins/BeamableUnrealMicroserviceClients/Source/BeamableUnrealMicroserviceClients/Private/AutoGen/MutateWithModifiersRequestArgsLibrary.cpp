
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateWithModifiersRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMutateWithModifiersRequestArgsLibrary::MutateWithModifiersRequestArgsToJsonString(const UMutateWithModifiersRequestArgs* Serializable, const bool Pretty)
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

UMutateWithModifiersRequestArgs* UMutateWithModifiersRequestArgsLibrary::Make(FString PlantItemContentId, int64 PlantItemInstanceId, TArray<FString> ModifierContentIds, UObject* Outer)
{
	auto Serializable = NewObject<UMutateWithModifiersRequestArgs>(Outer);
	Serializable->PlantItemContentId = PlantItemContentId;
	Serializable->PlantItemInstanceId = PlantItemInstanceId;
	Serializable->ModifierContentIds = ModifierContentIds;
	
	return Serializable;
}

void UMutateWithModifiersRequestArgsLibrary::Break(const UMutateWithModifiersRequestArgs* Serializable, FString& PlantItemContentId, int64& PlantItemInstanceId, TArray<FString>& ModifierContentIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlantItemContentId = Serializable->PlantItemContentId;
		PlantItemInstanceId = Serializable->PlantItemInstanceId;
		ModifierContentIds = Serializable->ModifierContentIds;
	}
		
}

