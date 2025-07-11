
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MyCoolNotificationLibrary.h"

#include "CoreMinimal.h"


FString UMyCoolNotificationLibrary::MyCoolNotificationToJsonString(const UMyCoolNotification* Serializable, const bool Pretty)
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

UMyCoolNotification* UMyCoolNotificationLibrary::Make(FString FieldA, FString FieldB, UObject* Outer)
{
	auto Serializable = NewObject<UMyCoolNotification>(Outer);
	Serializable->FieldA = FieldA;
	Serializable->FieldB = FieldB;
	
	return Serializable;
}

void UMyCoolNotificationLibrary::Break(const UMyCoolNotification* Serializable, FString& FieldA, FString& FieldB)
{
	FieldA = Serializable->FieldA;
	FieldB = Serializable->FieldB;
		
}

