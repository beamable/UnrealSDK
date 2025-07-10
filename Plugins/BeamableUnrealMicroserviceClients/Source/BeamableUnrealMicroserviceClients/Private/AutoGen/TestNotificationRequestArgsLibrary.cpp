
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/TestNotificationRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UTestNotificationRequestArgsLibrary::TestNotificationRequestArgsToJsonString(const UTestNotificationRequestArgs* Serializable, const bool Pretty)
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

UTestNotificationRequestArgs* UTestNotificationRequestArgsLibrary::Make(FString A, FString B, UObject* Outer)
{
	auto Serializable = NewObject<UTestNotificationRequestArgs>(Outer);
	Serializable->A = A;
	Serializable->B = B;
	
	return Serializable;
}

void UTestNotificationRequestArgsLibrary::Break(const UTestNotificationRequestArgs* Serializable, FString& A, FString& B)
{
	A = Serializable->A;
	B = Serializable->B;
		
}

